<h1>Simple Shell v2</h1>

<h2>Description:</h2>

So this is my second attempt at making my own shell based on the [Simple xv6 shell](https://pdos.csail.mit.edu/6.828/2019/labs/sh.html) by MIT. <br>
Will use `8===D` as my prompt to avoid confusion with the real shell as mentioned in the project description.

<h2>Basic flow:</h2>

1. Print prompt to standard output.
2. Reads line from standard input.
3. Parses command.
4. Executes it (Repeat).

<h2>Execution examples:</h2>

- Options: `8===D pgrm -r -i /usr/filename `
- I/O redirections: `8===D pgrm < in > out ` **[69% implemented]**
- Pipes: `8===D pgrm1 | pgrm2 | pgrm3 ` **[not implemented]**
- Sequencing: `8===D pgrm1 ; pgrm2 ; pgrm3` **[not implemented]**
- Background: `8===D pgrm &` **[not implemented]**
- Grouping: `8===D (pgrm1 & pgrm2) | pgrm3` **[not implemented]**

<h2>Built-in Commands:</h2>

- `exit`
- `env`

<h2>Will not implement</h3>

Due to my skill gap and my tendency to vibe code, I will excuse myself from further driving me insane by not implementing these advanced functionalities:

- Variables.
- Conditional control.
- Built-in commands like; pwd, pushd, popd, history.
- Line editing & arrow navigation to previous inputs.

<h2>Installation: </h2>

You can run this terminal in your own local shell if you're running linux, but for testing purposes and to make use of `user/ulib.c` libaries inside xv6, further implementation will move my source shell file to the specified path `user/shell.c`.

<h3> Building and running xv6 </h3>

To build xv6 on an x86 ELF machine (like Linux or FreeBSD), run
"make". On non-x86 or non-ELF machines (like OS X, even on x86), you
will need to install a cross-compiler gcc suite capable of producing
x86 ELF binaries (see https://pdos.csail.mit.edu/6.828/).
Then run "make TOOLPREFIX=i386-jos-elf-". Now install the QEMU PC
simulator and run "make qemu".

<h3> Running my shell </h3>

<h4> Running locally</h4>

- Navigate to the location of the shell's source file (`shell`).
- Run it with `./shell`.
- Once you see the prompt (`8===D`) you can input a command and the shell will run in interactive mode.
- Alternatively you can pass commands as arguments using pipes, e.g `echo "ls -a" | ./shell`.

<h4>Running in xv6 **[not implemented]**</h4>

- Copy main shell compiler to `xv6 OS/user/` and rename it to `sh.c` this is to make it compatible with xv6: `cp shell.c "xv6 OS/user/sh.c"`.
- Same with utils and header: `cp utils/print_prompt.c utils/getcmd.c main.h "xv6 OS/user/"`.
- Clean previous builds: `make clean`.
- Build xv6: `make`.
- Run xv6 in QEMU: `make qemu`.

\*<i>Current implementation is not fully compatible with xv6.</i>
