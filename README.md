# devbg_hsm_demo

The repository contains the code examples from the DEV.BG talk on Hierarchical State Machines held on 27/Sep/2023. Please note that this is demo code and is not fully tested.

| Folder | Description |
|---|---|
| hsm | Simple HSM engine implementation in C11 |
| hsmgen | Python code generator for HSM based on YAML HSM description |
| test | Engine unit test written with Unity Framework (also available in the folder)
| hsm_demo | CMake-based example project demonstrating how the engine is used |

## hsmgen

* You need Python 3+ to use this code.
* Additional required packages:
  * PyYAML: `pip install PyYAML`
  * Jinja: `pip install Jinja2`
  * Rich: `pip install rich`

## hsm_demo

The generated SM code is in the `hsm_demo/time_bomb` folder. In a Windows environment, you can run `gen.bat` to re-generate the code and merge the existing implementation with the one in the folder. This is needed when you make changes to the `time_bomb.yaml` description of the SM. Then you can just implement any newly generated handlers and rebuild the project to see the HSM tracing its execution.