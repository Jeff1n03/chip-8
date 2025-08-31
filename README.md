# Prerequisites
- a POSIX-compliant system
- `git`
- `make`
- `gcc` (C11 compatible)
    > Note that `gcc` is a symbolic link to `clang` **on macOS**. This is **not** an issue as long as `clang` is C11 compatible.
- [SDL2 **with developer files**](https://wiki.libsdl.org/SDL2/Installation)
    > For whatever reason, installation instructions using `brew` or `port` **on macOS** are not present. In a terminal emulator, **run either** `brew install sdl2` **or** `sudo port install libsdl2` depending on your package manager of choice.
# Installation
## macOS and Linux
**In a terminal emulator**, run
```
git clone https://github.com/Jeff1n03/chip-8.git
cd chip-8/ && make && sudo make install && cd ../
rm -rf chip-8/
```
## Windows
[Install WSL](https://learn.microsoft.com/en-us/windows/wsl/install), install **Prerequisites**, and follow installation instructions for **macOS and Linux**.
