<h1>Simple Shell v2</h1>
<h2>Cause I fucked up in the previous one</h2>
<h3>Now with extra stuff!!</h3>

<h2>Description:</h2>

So this is my second attempt at making my own shell based on the ![Simple xv6 Shell](https://pdos.csail.mit.edu/6.828/2019/labs/sh.html) by MIT.

<h2>Basic flow:</h2>

- 1 - Primpt prompt.
- 2 - Reads line from standard input.
- 3 - Parses it.
- 4 - Execute (Repeat).

<h2>Execution examples:</h2>

- Options: `$ pgrm -r -i /usr/filename `[not implemented]
- I/O redirections: `$ pgrm < in > out `[not implemented]
- Pipes: `$ pgrm1 | pgrm2 | pgrm3 `[not implemented]
- Sequencing: `$ pgrm1 ; pgrm2 ; pgrm3 [not implemented]
- Background: `$ pgrm &` [not implemented]
- Grouping: `$ (pgrm1 & pgrm2) | pgrm3` [not implemented]

<h2>Built-in Commands:</h2>

- `$ cd path`
- `exit`
- `printenv`

<h2>Will not implement</h3>

Due to my skill gap and my tendency to vibe code, I will excuse myself of further driving me insane by not implementing these advanced functionalities:

- Variables.
- Conditional control.
- Built-in commands like; pwd, pushd, popd, history.
- Line editing & arrow navigation to previous inputs.
