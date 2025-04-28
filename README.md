<h1>Simple Shell v2</h1>
Cause I fucked up in the previous one <br>
Now with extra stuff!!

<h2>Description:</h2>

So this is my second attempt at making my own shell based on the [Simple xv6 shell](https://pdos.csail.mit.edu/6.828/2019/labs/sh.html) by MIT. <br>
Will use `8===D` as my prompt to avoid confusion with the real shell as mentioned in the project description.

<h2>Basic flow:</h2>

1. Print prompt to standard output.
2. Reads line from standard input.
3. Parses it.
4. Execute (Repeat).

<h2>Execution examples:</h2>

- Options: `8===D pgrm -r -i /usr/filename ` **[not implemented]**
- I/O redirections: `8===D pgrm < in > out ` **[not implemented]**
- Pipes: `8===D pgrm1 | pgrm2 | pgrm3 ` **[not implemented]**
- Sequencing: `8===D pgrm1 ; pgrm2 ; pgrm3` **[not implemented]**
- Background: `8===D pgrm &` **[not implemented]**
- Grouping: `8===D (pgrm1 & pgrm2) | pgrm3` **[not implemented]**

<h2>Built-in Commands:</h2>

- `cd path`
- `exit`
- `printenv`

<h2>Will not implement</h3>

Due to my skill gap and my tendency to vibe code, I will excuse myself from further driving me insane by not implementing these advanced functionalities:

- Variables.
- Conditional control.
- Built-in commands like; pwd, pushd, popd, history.
- Line editing & arrow navigation to previous inputs.
