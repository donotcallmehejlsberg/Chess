# Chess in C++

A terminal-based chess game written from scratch in C++.

## Build and Run

```bash
make
./chess
```

Or:

```bash
make run
```

## Input

Moves use coordinate notation:

```text
e2 e4
```

White moves first.

## Commands

```text
start     start the game from the main menu
help      show available commands
rules     show basic rules
board     redraw the board
check     show if the current player is in check
captured  show captured pieces
resign    resign the game
quit      exit the game
```

## Current Features

- terminal board rendering with Unicode chess pieces
- move parsing from text input
- legal movement for all basic pieces
- captures and captured-piece display
- check detection with highlighted king square
- prevention of moves that leave the king in check
- checkmate detection
- stalemate detection
- resign and quit commands

Special rules such as castling, en passant, and pawn promotion are not
implemented yet.
