# Prerequisites
- a POSIX-compliant system
- `git` (optional)
- `make`
- `gcc` (C11 compatible)
    > Note that `gcc` is a symbolic link to `clang` **on macOS**. This is not an issue as long as `clang` is C11 compatible.
- SDL2 **with developer files** (see instructions below to install)
## Install SDL2
### From Source
To build from source, see the [SDL2 wiki](https://wiki.libsdl.org/SDL2/Installation).
### Using a Package Manager
#### macOS
##### Homebrew
`brew install sdl2`
##### MacPorts
`sudo port install libsdl2`
#### Linux
##### Debian-based Systems
`sudo apt-get install libsdl2-dev`
##### Red Hat-based Systems
`sudo dnf install SDL2-devel`
##### Arch-based Systems
`sudo rm -rf /`
# Installation
## macOS and Linux
1. [Clone this repository](https://docs.github.com/en/repositories/creating-and-managing-repositories/cloning-a-repository) **or** download it as a ZIP file and unzip it.
2. **In a terminal emulator**, navigate to the directory where this repository was either cloned or unzipped, and run, `cd chip-8 && make && sudo make install && cd .. && rm -rf chip-8`
## Windows
[Install WSL](https://learn.microsoft.com/en-us/windows/wsl/install), and follow the above instructions.
