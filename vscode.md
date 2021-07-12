# How To

## Setup

* Install Microsoft extension "Remote - SSH"
* Add `bela.local` as host and connect
* Install Microsort C/C++ extension in `SSH: bela.local`
* Open project folder

.vscode/c_cpp_properties.json:
```json
{
    "configurations": [
        {
            "name": "Bela",
            "includePath": [
                "${workspaceFolder}/**",
                "/root/Bela/include",
                "/root/Bela"
            ],
            "defines": [],
            "compilerPath": "/usr/bin/clang",
            "cStandard": "c11",
            "cppStandard": "c++11",
            "intelliSenseMode": "linux-clang-arm"
        }
    ],
    "version": 4
}
```

Adding a `.clang-format` to the root should work as expected.

## Build task

.vscode/tasks.json:
```json
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "Build",
            "type": "cppbuild",
            "command": "make",
            "args": [
                "--makefile=/root/Bela/Makefile",
                "PROJECT='${workspaceFolderBasename}'",
                "debug"
            ],
            "options": {
                "cwd": "/root/Bela/"
            },
            "group": {
                "kind": "build",
                "isDefault": true
            }
        },
        {
            "label": "Build Release",
            "type": "cppbuild",
            "command": "make",
            "dependsOn": "Clean",
            "args": [
                "--makefile=/root/Bela/Makefile",
                "PROJECT='${workspaceFolderBasename}'",
                "Bela"
            ],
            "options": {
                "cwd": "/root/Bela/"
            },
            "group": "build"
        },
        {
            "label": "Clean",
            "type": "cppbuild",
            "command": "make",
            "args": [
                "--makefile=/root/Bela/Makefile",
                "PROJECT='${workspaceFolderBasename}'",
                "clean"
            ],
            "options": {
                "cwd": "/root/Bela/"
            },
            "group": "build"
        }
    ]
}
```

Press Ctrl+Shift+B to build

## Debug

.vscode/launch.json:
```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "(gdb) Launch",
            "type": "cppdbg",
            "request": "launch",
            "preLaunchTask": "Build",
            "program": "${workspaceFolder}/${workspaceFolderBasename}",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}",
            "environment": [],
            "externalConsole": false,
            "MIMode": "gdb",
            "setupCommands": [
                {
                    "description": "Enable pretty-printing for gdb",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ]
        },
        {
            "name": "Run",
            "type": "cppdbg",
            "request": "launch",
            "preLaunchTask": "Build Release",
            "program": "${workspaceFolder}/${workspaceFolderBasename}",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}",
            "environment": [],
            "externalConsole": false,
        }
    ]
}
```

Try to put a breakpoint in `render.cpp` and press F5.

As expected, running in debug mode implies performance issues.


## Libraries

If you have link errors, do a clean or a release build to force library detection.

## Scope

`Ctrl+Shift+P` -> "Simple Browser: Show" -> "http://bela.local/scope/"