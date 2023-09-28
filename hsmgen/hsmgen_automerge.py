from rich import print
from jinja2 import Environment, BaseLoader
import os
import sys


class hsm_file:
    START_PREFIX = "// USER_CODE_START::"
    END_PREFIX = "// USER_CODE_END::"

    def __init__(self, file_name: str):
        self.file_name = file_name
        # dictionary containing individual source objects
        self.source_objects_dict: dict[str] = {}
        self.jinja_template_lines: list[str] = []

        self.parse()

    def parse(self):
        print(f'trying to parse {self.file_name}...', end="")

        if os.path.exists(self.file_name):
            self.jinja_template_lines = []

            f = open(self.file_name, "r")
            lines = f.readlines()
            f.close()

            obj_name: str = ""
            in_obj_section: bool = False

            for line in lines:
                stripped_line = line.strip()

                if stripped_line.startswith(hsm_file.END_PREFIX):
                    self.jinja_template_lines.append(line)
                    in_obj_section = False
                elif in_obj_section:
                    self.source_objects_dict[obj_name] = self.source_objects_dict[obj_name] + line
                elif stripped_line.startswith(hsm_file.START_PREFIX):
                    obj_name = stripped_line.removeprefix(
                        hsm_file.START_PREFIX).strip()
                    self.source_objects_dict[obj_name] = ""
                    in_obj_section = True

                    self.jinja_template_lines.append(line)
                    self.jinja_template_lines.append(
                        "{{ source_obj_dict[\"" + obj_name + "\"] }}")
                else:
                    self.jinja_template_lines.append(line)

            print(" [green]success[/green]")
        else:
            print(
                f' [red]missing[/red]')
            sys.exit(1)

    def add_removed_object_as_comment(self, obj_name: str, obj_content: str) -> None:
        self.jinja_template_lines.append("\n")
        self.jinja_template_lines.append(f'/* object removed: "{obj_name}"\n')
        self.jinja_template_lines.append(f'>>>> CODE START"\n')

        obj_lines = obj_content.splitlines()

        for line in obj_lines:
            self.jinja_template_lines.append(f'\t{line}\n')

        self.jinja_template_lines.append(f'<<<< CODE END"\n')
        self.jinja_template_lines.append("*/ \n")

    def render_template(self) -> str:
        rtemplate = Environment(loader=BaseLoader).from_string(
            "".join(self.jinja_template_lines))
        # "source_obj_dict" arg name shall be the same as the one used in the
        # jinja template above
        return rtemplate.render(source_obj_dict=self.source_objects_dict)

    def update_obj(self, obj_name: str, new_obj_content: str) -> bool:
        res = False

        if obj_name in self.source_objects_dict.keys():
            self.source_objects_dict[obj_name] = new_obj_content
            res = True

        return res

    def get_objects(self) -> dict[str]:
        return self.source_objects_dict


class hsm_merger:
    def __init__(self, existing_file: str, new_file: str, target_file: str):
        self.existing_file = existing_file
        self.new_file = new_file
        self.target_file = target_file

    def merge(self):
        existing_file_obj = hsm_file(self.existing_file)
        new_file_obj = hsm_file(self.new_file)

        print("performing in-memory merge...")
        # perform merge
        for obj, obj_content in existing_file_obj.get_objects().items():
            if new_file_obj.update_obj(obj, obj_content):
                print(f':heavy_check_mark: object "{obj}" merged')
            else:
                print(
                    f':heavy_exclamation_mark: "{obj}" not found in {self.new_file} -> merged at EOF as commented code')
                new_file_obj.add_removed_object_as_comment(obj, obj_content)

        # produce merged output file...
        try:
            target_file_hnd = open(self.target_file, "w")
            target_file_hnd.writelines(new_file_obj.render_template())
            target_file_hnd.close()

            print(
                f':heavy_check_mark: [green]merged output written to {self.target_file}![/green]')
        except:
            print(
                f':heavy_exclamation_mark: error writing to {self.target_file}')


if __name__ == "__main__":
    merger_inst = hsm_merger(
        "test_sm_config_user_fakes.c", "test_sm_config_user.c", "test_sm_config_user_merged.c")

    merger_inst.merge()
