### MineSweeper

Trying to reproduce classic MineSweeper on the command line.

So far essential function have been completed.

---

### How to build?



`$ make init`

`$ make`

`$ make clean`

Then will auto generate a executable file `minesweeper.exe` and click it.

---

### How to play?

- When click and open `minesweeper.exe`, you are
required to input two parameters to initialize a game

|parameters|meaning|
|---|---|
|method|`0`: customized method; `1`: default method|
|mine|for method `0`: three integer are required, which mean row, line, mines respectively; for method `1`: there are three levels of `0`, `1`, `2`|

- When you start a game:

|operation|meaning|
|---|---|
|1|click|
|2|mark flag|
|3|mark question|
|q|quit|
|w / k / up arrow|up move cursor|
|a / h / left arrow|left move cursor|
|s / j / down arrow|down move cursor|
|d / l / right arrow|right move cursor|
|z|hint|

---

### My to-do list

- [x] Basic functions
- [x] Hint functions
- [x] Simple user interface
- [ ] More beautiful UI
- [ ] History functions
- [ ] Scoreboard
