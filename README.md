# Build Dependencies
- a POSIX-compliant system (macOS, Linux, BSD, etc.)
    > **Windows users**, [install WSL](https://learn.microsoft.com/en-us/windows/wsl/install).
- `git`
- `make`
- `gcc` (supports C11)
    > **macOS users**, note that `gcc` is a symbolic link to `clang`. This is **not an issue** as long as `clang` supports C11.
- [SDL2 **with developer files**](https://wiki.libsdl.org/SDL2/Installation)
    > **macOS users**, for whatever reason, installation instructions using `brew` or `port` are not present. In a terminal emulator, **run either** `brew install sdl2` **or** `sudo port install libsdl2` depending on your package manager of choice.
# Build Instructions
**In a terminal emulator**, run
```
git clone https://github.com/Jeff1n03/chip-8.git
cd chip-8/ && make && sudo make install && cd ../
rm -rf chip-8/
```
