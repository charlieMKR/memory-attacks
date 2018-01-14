The goal of this repo is to educate myself on memory attacks.

### Useful stuff: GCC flags

- `-fno-stack-protector`: No stack canaries
- `-m32`: Compile 32 bit executable
- `-O0`: Dissable optimizations
- `-ggdb`: Produce debugging information for use by GDB

### Useful stuff: GDB commands

- `list`
- `p/x varname`
- `x/20x address`: for examining the stack use address=$esp 
- `b function_name`: breakpoint at function_name
- `info locals/registers/variables`

### Other notes
- If you are on linux, 64 bits, install `gcc-multilib`
- GDB cheatsheet: [http://www.yolinux.com/TUTORIALS/GDB-Commands.html](http://www.yolinux.com/TUTORIALS/GDB-Commands.html)
- Inject shellcode: `echo $(python -c 'print("\x66\x6f\x6f")') | ./nameofbinary.o`
- Attach gdb to process: `sudo gdb -p $(pgrep nameofbinary)`
