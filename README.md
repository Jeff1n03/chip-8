# Prerequisites
To build this program, the **developer version** of SDL2 is needed.
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
1. [Clone](https://docs.github.com/en/repositories/creating-and-managing-repositories/cloning-a-repository) this repository
2. `cd chip-8`
3. `make`
4. `sudo make install`
5. `cd ..
    rm -rf chip-8`
## Windows
[Set up WSL](https://learn.microsoft.com/en-us/windows/wsl/install), and follow the above instructions.
