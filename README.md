## Introduction 

`InternalHack` is a DLL hack for the game, [Ni No Kuni] by Nanami#6283. `InternalHack` has to be injected into the game's process. From there it creates a console, givning the user options to activate hack or deactivate the hack. 

Currently, the hack only changes a player's AtkSpeed This can easily be extended.

Console options once injected into a game:



## Operation system, project, etc.

- IDE: Visual Studio 2022 (x64 project).
- OS: Windows 10, version 1909.

## Setup

1. Compile the source code
2. Run it one time - a folder and a `config.ini` file should be created on your desktop.
3. Navigate to `Desktop/Hack/config.ini`.
4. Fill in info about the offsets to the AtkSpeed value (currently `Attack Speed=0x0636F5C8, 0x0, 0x20, 0x804`)

## References

- [Guided hacking](https://guidedhacking.com/threads/finddmaaddy-c-multilevel-pointer-function.6292/) (pointer chain function)
