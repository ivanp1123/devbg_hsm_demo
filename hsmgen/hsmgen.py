from os import get_terminal_size
from re import S
from typing import Any
import yaml
from jinja2 import *
from rich import print
from rich import inspect
from rich.tree import Tree
import argparse
import os
import hsmgen_automerge

class sm:
    SPECIAL_NAME_PREFIX: str = "__"
    SPECIAL_HISTORY_NAME_PREFIX = f"{SPECIAL_NAME_PREFIX}history_"
    SPECIAL_TRANSITION_STATE_SELF = f"{SPECIAL_NAME_PREFIX}self"
    trans_map: dict[str, bool] = {}
    # counter which gets incremented on duplicated transition names and is
    # appended to the name of the transition to make it unique
    trans_cntr = 1

    def __init__(self, sm_config: dict):
        self.attributes: dict = {}
        self.states_list: list[sm_state] = []
        self.attributes: dict = {}
        self.events_list = None
        self.sm_config = sm_config

        self.name = f"{sm_config[0]}"

        for sm_state_config in sm_config[1]["states"]:
            state: sm_state = sm_state.parse_state(
                self, self.name, sm_state_config)
            self.states_list.append(state)

        self.attributes = sm_config[1]["attributes"]

    def get_all_states(self) -> list["sm_state"]:
        all_states = []

        for state in self.states_list:
            all_states.append(state)
            all_states.extend(sm.get_all_substates(state))

        return all_states

    @staticmethod
    def get_all_substates(state: "sm_state") -> list["sm_state"]:
        all_substates = []

        if state.is_composite():
            for substate in state.get_substates():
                if substate.is_composite():
                    all_substates.extend(sm.get_all_substates(substate))

                all_substates.append(substate)

        return all_substates

    def get_states(self) -> list["sm_state"]:
        return self.states_list

    def get_state_obj_by_name(self, state_name: str) -> "sm_state":
        for state in self.get_states():
            if state.get_name() == state_name:
                return state

        return None

    def get_attributes(self) -> dict:
        return self.attributes

    def get_events(self) -> list[str]:
        if self.events_list == None:
            self.events_list: list[str] = []

            for state in self.get_all_states():
                for trans in state.get_trans_list():
                    if not trans.is_trans_event_special():
                        trans_event = trans.get_printable_event_name()

                        if trans_event != None:
                            if not trans_event in self.events_list:
                                self.events_list.append(trans_event)

        return self.events_list

    def get_guards(self) -> list[str]:
        guard_list = []

        for state in self.get_all_states():
            for trans in state.get_trans_list():
                guard = trans.get_printable_guard_name(state.name)

                if (guard != "") and (not guard in guard_list):
                    guard_list.append(guard)

        return guard_list

    def get_actions(self) -> list[str]:
        action_list = []

        for state in self.get_all_states():
            for trans in state.get_trans_list():
                action = trans.get_printable_action_name(state.name)

                if (action != "") and (not action in action_list):
                    action_list.append(action)

        return action_list

    def check_unique_state_names(self) -> tuple[bool, str]:
        state_dict = {}
        res = [True, ""]

        for state in self.get_all_states():
            if not state.name in state_dict:
                state_dict[state.name] = True
            else:
                res = [
                    False, f'"{state.name}" is used to name more than one state']
                break

        return res

    def check_unsupported_attributes(self) -> tuple[bool, str]:
        res = [True, ""]
        valid_attr_list = ["initial", "on_entry", "on_exit"]

        for state in self.get_all_states():
            for attr in state.get_attributes().keys():
                if not attr in valid_attr_list:
                    res = [
                        False, f'Invalid attribute "{attr}" specified for state "{state.name}"']
                    break

        return res

    def check_history_transitions(self) -> tuple[bool, str]:
        res = [True, ""]
        HISTORY_STATE_TRANS_PREFIX = "__history_"

        for state in self.get_all_states():
            for trans in state.get_trans_list():
                if trans.target_state.startswith(HISTORY_STATE_TRANS_PREFIX):
                    target = self.get_state_obj_by_name(
                        trans.target_state.removeprefix(HISTORY_STATE_TRANS_PREFIX))

                    if not target.is_composite():
                        res = [
                            False, f'History state transition not possible for simple state "{target.name}"']
                        break
        return res

    def validate_sm_def(self) -> bool:
        res = True

        check_list: dict[str, function] = {
            "state unique names": self.check_unique_state_names,
            "valid attributes": self.check_unsupported_attributes,
            "history state transitions only for composite states": self.check_history_transitions
        }

        print(f'[bold]{self.name}[/bold] validation...')

        # - enforce unique state names
        for descr, check_func in check_list.items():
            res = check_func()
            if res[0]:
                print(f':heavy_check_mark: {descr}')
            else:
                print(f':heavy_exclamation_mark: {descr}')
                print(f'\t{res[1]}')
                break

        return res


class sm_transition:
    def __init__(self, sm_instance: sm, parent_state: str, trans_record: dict):
        self.sm_instance = sm_instance
        self.parent_state = parent_state
        self.target_state: str = list(trans_record)[0]
        self.is_transition_to_self = False

        if self.is_history_state_transition():
            self.history_target_state = self.target_state.removeprefix(
                sm.SPECIAL_HISTORY_NAME_PREFIX
            )
        else:
            self.history_target_state = ""

        self.trans_data: list[dict] = trans_record[self.target_state]

        if self.target_state.startswith(sm.SPECIAL_TRANSITION_STATE_SELF):
            self.is_transition_to_self = True
            self.target_state.removeprefix(sm.SPECIAL_NAME_PREFIX)

        self.trans_generated_name = f'tran_{self.parent_state}_ev_{self.get_printable_event_name()}_{self.target_state}'

        if not self.trans_generated_name in sm.trans_map:
            sm.trans_map[self.trans_generated_name] = True
        else:
            # modify name to be unique
            self.trans_generated_name += f'_{ sm.trans_cntr }'
            sm.trans_cntr += 1

    def get_trans_event(self) -> str:
        for trans_entry in self.trans_data:
            if "event" in trans_entry:
                return trans_entry["event"]

    def is_history_state_transition(self):
        return self.target_state.startswith(sm.SPECIAL_HISTORY_NAME_PREFIX)

    def is_transition_to_self(self):
        return self.is_transition_to_self

    def is_trans_event_special(self) -> bool:
        trans_evt = self.get_trans_event()

        # special (or built-in) events have a sm.SPECIAL_NAME_PREFIX, e.g. periodic
        return trans_evt.startswith(sm.SPECIAL_NAME_PREFIX)

    def get_printable_event_name(self) -> str:
        event_name = self.get_trans_event().replace(sm.SPECIAL_NAME_PREFIX, "")
        return "" if event_name == None else event_name

    def get_trans_guard(self) -> str:
        for trans_entry in self.trans_data:
            if "guard" in trans_entry:
                return trans_entry["guard"]

    def get_printable_guard_name(self, outgoing_state: str = "") -> str:
        guard = self.get_trans_guard()

        if guard != None:
            if guard.startswith(sm.SPECIAL_NAME_PREFIX) and outgoing_state != "":
                if guard.removeprefix(sm.SPECIAL_NAME_PREFIX) == "auto":
                    guard = f'{outgoing_state}_{self.get_printable_event_name()}_{self.target_state}'
        else:
            guard = ""

        return guard

    def get_trans_action(self) -> str:
        for trans_entry in self.trans_data:
            if "action" in trans_entry:
                return trans_entry["action"]

    def get_printable_action_name(self, outgoing_state: str = "") -> str:
        action_name = self.get_trans_action()

        if action_name != None:
            if action_name.startswith(sm.SPECIAL_NAME_PREFIX) and outgoing_state != "":
                if action_name.removeprefix(sm.SPECIAL_NAME_PREFIX) == "auto":
                    action_name = f'{outgoing_state}_{self.get_printable_event_name()}_{self.target_state}'
        else:
            action_name = ""

        return action_name

    def __repr__(self):
        return f'{self.get_printable_event_name()} [{self.get_printable_guard_name()}] / {self.get_printable_action_name()} => {self.parent_state}]'


class sm_state:
    def __init__(self, sm_instance: sm, parent: str, state_descriptor: dict):
        self.sm_instance = sm_instance
        self.parent = parent
        self.name: str = list(state_descriptor)[0]
        self.transitions_list: sm_transition = []
        # a map of existing transitions in order to avoid duplication of names
        self.trans_map: dict = {}
        self.is_composite_state: bool = False
        self.substates: list[sm_state] = []
        self.attributes: dict = {}

    def get_name(self) -> str:
        return self.name

    def get_trans_list(self) -> list[sm_transition]:
        return self.transitions_list

    def has_transitions(self) -> bool:
        return len(self.transitions_list) > 0

    def is_composite(self) -> bool:
        return self.is_composite_state

    def get_substates(self) -> list["sm_state"]:
        return self.substates

    def get_attributes(self) -> dict:
        return self.attributes

    def supports_bool_attr(self, attr_name: str) -> bool:
        has_attr = self.has_attr(attr_name)

        return (has_attr and self.get_attr_value(attr_name)) or not has_attr

    def has_attr(self, attr_name: str) -> bool:
        return attr_name in self.attributes.keys()

    def get_attr_value(self, attr_name: str) -> any:
        if attr_name in self.attributes.keys():
            return self.attributes[attr_name]
        else:
            return False

    def get_initial_state(self) -> "sm_state":
        if self.is_composite_state:
            return self.sm_instance.get_state_obj_by_name(self.attributes["initial"])
        else:
            return self

    def has_history_state(self) -> bool:
        history_state_available = False

        for trans in self.get_trans_list():
            if trans.is_history_state_transition():
                history_state_available = True
                break

        return history_state_available

    def parse_state(sm_instance: sm, parent: str, state_descriptor: dict) -> "sm_state":
        state: sm_state = sm_state(sm_instance, parent, state_descriptor)

        for state_name, state_value in state_descriptor.items():
            for category_name in state_value.keys():
                if category_name == "states":
                    state.is_composite_state = True
                    for substate in state_value["states"]:
                        state.get_substates().append(
                            sm_state.parse_state(
                                sm_instance, state.name, substate)
                        )
                elif category_name == "transitions":
                    for trans in state_value[category_name]:

                        state.get_trans_list().append(sm_transition(sm_instance, state_name, trans))
                elif category_name == "attributes":
                    state.attributes = state_descriptor[list(state_descriptor)[0]][
                        "attributes"
                    ]

        return state


class sm_renderer_base:
    def __init__(self, sm_instance: sm):
        self.sm_instance = sm_instance
        self.attributes = sm_instance.attributes
        self.states_list = sm_instance.states_list

    def render_action(self, file_name: str) -> None:
        pass

    def render(self, file_name: str) -> None:
        if file_name == "":
            print("[bold red] Emtpy file name provided!")
        else:
            print(f"rendering to file => {file_name}...", end=" ")

            self.render_action(file_name)

            print(f"[bold green] ok")

    def write_to_file(self, file_name: str, lines: list[str]) -> None:
        dir = os.path.dirname(file_name)

        if not os.path.exists(dir):
            os.mkdir(dir)

        f = open(file=file_name, mode="w", encoding="utf-8")
        f.writelines(lines)
        f.close()


class sm_renderer_plantuml(sm_renderer_base):
    def __init__(self, sm_instance: sm):
        super().__init__(sm_instance)
        self.output_lines: list[str] = []

    def append_to_out(self, line: str) -> None:
        self.output_lines.append(
            f'{line}\n' if line != None else "")

    def format_puml_transition(self, state: sm_state, trans: sm_transition) -> str:
        target_state: str = ""
        linestyle: str = ""

        if trans.is_history_state_transition():
            target_state = f'{trans.history_target_state}[H]'
        elif trans.is_transition_to_self:
            # in this case, trans.target_state will contain "self" but it has to be
            # replaced with the actual state name "self" refers to...
            target_state = trans.parent_state
            linestyle = "[dotted,#blue]"
        else:
            target_state = trans.target_state

        trans_event_name: str = trans.get_trans_event()

        guard_cond: str = f'[{trans.get_trans_guard()}]' if trans.get_trans_guard(
        ) else ""

        action: str = f'/ {trans.get_trans_action()}' if trans.get_trans_action() else ""

        res: str = f'{state.name} -{linestyle}-> {target_state}: <b>{trans_event_name}</b> {guard_cond}\\n{action}'

        return res

    def format_forward_state_decls(self, sm_state_config: dict) -> str:
        res: str = ""

        # sm_state_config is actually a dictionary provided by the YAML parser
        # the root node contains two elements in a list, hence the check here;
        # when  format_forward_state_decls() is called recursively it gets
        # passed a state YAML descriptor which contains only one dictionary
        # with a single key named after the state
        if len(sm_state_config) == 2:
            if "states" in sm_state_config[1].keys():
                state_config = sm_state_config[1]['states']

                for state_value in state_config:
                    state_name = list(state_value)[0]

                    res = res + f'state {state_name}'

                    if "states" in state_value[state_name]:
                        res = res + ' {\n'

                        for substate in state_value[state_name]["states"]:
                            res = res + \
                                self.format_forward_state_decls(
                                    substate)

                        res = res + '\n}'

                    res = res + '\n'
            else:
                res = res + f'state {sm_state_config[1]}\n'
        else:
            if "states" in sm_state_config[list(sm_state_config)[0]]:
                state_config = sm_state_config[list(
                    sm_state_config)[0]]['states']

                res = res + f'state {list(sm_state_config)[0]} {{\n'

                for state_value in state_config:
                    state_name = list(state_value)[0]

                    res = res + f'state {state_name}'

                    if "states" in state_value[state_name]:
                        res = res + ' {\n'

                        for substate in state_value[state_name]["states"]:
                            res = res + \
                                self.format_forward_state_decls(
                                    substate)

                        res = res + '\n}'
                    res = res + '\n'

                res = res + '\n}\n'
            else:
                res = res + \
                    f'state {list(sm_state_config)[0]}\n'

        return res

    def get_trans_description(self, from_state: sm_state, trans: sm_transition):
        return f'{from_state.get_name()} => {trans}'

    def render_action(self, file_name: str) -> None:

        res = self.format_forward_state_decls(self.sm_instance.sm_config)

        self.append_to_out("@startuml")

        self.append_to_out(f"title <b>{self.sm_instance.name}")
        self.append_to_out(
            f"[*] --> {self.sm_instance.attributes['initial']}")

        self.append_to_out(res)

        processed_transitions_dict: dict[str] = {}

        for state in self.sm_instance.get_all_states():
            if state.is_composite():
                self.append_to_out(f'state {state.name} {{')
                self.append_to_out(
                    f"[*] --> {state.attributes['initial']}")

                for trans in state.get_trans_list():
                    if not self.get_trans_description(state, trans) in processed_transitions_dict.keys():
                        self.append_to_out(
                            self.format_puml_transition(state, trans))
                        processed_transitions_dict[self.get_trans_description(
                            state, trans)] = 1

                for substate in state.get_substates():
                    for trans in substate.get_trans_list():
                        if not self.get_trans_description(substate, trans) in processed_transitions_dict.keys():
                            self.append_to_out(
                                f'{self.format_puml_transition(substate, trans)}')
                            processed_transitions_dict[self.get_trans_description(
                                substate, trans)] = 1

                self.append_to_out("}")
            else:
                for trans in state.get_trans_list():
                    if not self.get_trans_description(state, trans) in processed_transitions_dict.keys():
                        self.append_to_out(
                            self.format_puml_transition(state, trans))
                        processed_transitions_dict[self.get_trans_description(
                            state, trans)] = 1

        self.append_to_out("@enduml")

        super().write_to_file(file_name, self.output_lines)


class sm_renderer_jinja(sm_renderer_base):
    def __init__(self, sm_instance: sm, searchpath: str, template_name: str):
        super().__init__(sm_instance)

        templateLoader = FileSystemLoader(searchpath=searchpath)
        templateEnv = Environment(loader=templateLoader)
        self.template = templateEnv.get_template(template_name)

    def render_action(self, file_name: str) -> None:
        outputText = self.template.render(
            sm=self.sm_instance,
            attributes=self.attributes,
            states=self.sm_instance.get_all_states(),
            root_states=self.sm_instance.get_states(),
        )

        super().write_to_file(file_name, [outputText])

if __name__ == "__main__":
    print("YAML model2code generator\n\n")

    argparser = argparse.ArgumentParser(description="")
    argparser.add_argument(
        "--conf",
        type=str,
        help="A list of YAML HSM configuration files to parse",
        required=True,
        nargs="+",
    )

    argparser.add_argument(
        "--outpath",
        type=str,
        help="A path where generated files will be output",
        required=False,
        default=os.getcwd(),
    )

    argparser.add_argument(
        "--templatepath",
        type=str,
        help="The path where the source code templates are stored",
        required=False,
        default=os.getcwd(),
    )

    args = argparser.parse_args()

    for cfg_file in args.conf:
        stream = open(cfg_file, "r", encoding="utf-8")
        dictionary = yaml.load(stream, Loader=yaml.FullLoader)

        sm_list: list[sm] = []

        for sm_config in dictionary.items():
            sm_list.append(sm(sm_config))

        print(f"{len(sm_list)} SM(s) found in YAML configuration:")

        sm_tree = Tree("State machines")
        for sm_entry in sm_list:
            sm_tree.add(sm_entry.name)

        print(sm_tree)

        print('\n')

        for sm_instance in sm_list:
            if sm_instance.validate_sm_def():
                for sm_instance in sm_list:
                    sm_inst_name = sm_instance.name.lower()

                    sm_renderer_plantuml(sm_instance).render(os.path.join(
                        args.outpath, f'{sm_inst_name}.puml'))

                    render_dict: dict[str] = {}
                    # render_dict elements are tuples (<file name>, <merge flag if file already exists>)
                    # render_dict["sm.puml.j2"] = f"{sm_inst_name}.puml"
                    render_dict["hsm_config.c.j2"] = (
                        f"{sm_inst_name}_config.c", False)
                    render_dict["hsm_config_user.c.j2"] = (
                        f"{sm_inst_name}_config_user.c", True)
                    render_dict["hsm_config_user.h.j2"] = (
                        f"{sm_inst_name}_config_user.h", True)
                    render_dict["hsm_user.h.j2"] = (
                        f"{sm_inst_name}_user.h", False)

                    for key, value in render_dict.items():
                        gen_file_path = os.path.join(args.outpath, value[0])
                        merge_if_file_exists = value[1]

                        if (merge_if_file_exists) and (os.path.exists(gen_file_path)):
                            print(
                                f'attempting to merge "{gen_file_path}"...')

                            tmp_new_file_name = f'{gen_file_path}.tmp'

                            # generate to a temporary file to use for the subsequent merge
                            sm_renderer_jinja(sm_instance, args.templatepath, key).render(
                                tmp_new_file_name)

                            # perform merge
                            merger = hsmgen_automerge.hsm_merger(
                                gen_file_path, tmp_new_file_name, gen_file_path)
                            merger.merge()

                            # remove temporary file
                            if os.path.exists(tmp_new_file_name):
                                os.remove(tmp_new_file_name)
                        else:
                            sm_renderer_jinja(sm_instance, args.templatepath, key).render(
                                gen_file_path
                            )
            else:
                print(
                    f'Code generation for "{sm_instance.name}" interrupted due to errors.')
