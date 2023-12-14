# Terminal-based Chess Game
## Board printed in Display waiting for user input to move:
- b - black, w - white
- K - King
- Q - Queen
- B - Bishop
- N - Knight
- R - Rook
- P - Pawn

        ---------------------------
          a  b  c  d  e  f  g  h
         |--|--|--|--|--|--|--|--|
        8|bR|bN|bB|bQ|bK|bB|bN|bR|8
        7|bP|bP|bP|bP|bP|bP|bP|bP|7
        6|__|__|__|__|__|__|__|__|6
        5|__|__|__|__|__|__|__|__|5
        4|__|__|__|__|__|__|__|__|4
        3|__|__|__|__|__|__|__|__|3
        2|wP|wP|wP|wP|wP|wP|wP|wP|2
        1|wR|wN|wB|wQ|wK|wB|wN|wR|1
         |--|--|--|--|--|--|--|--|
          a  b  c  d  e  f  g  h

        ---------------------------
        White move: <User Input>

## Program detection:
- Check
  - After a move, if it puts opponent's King under check, the program prints "Check".

        ___________________________
        |          Check          |
        ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
- Checkmate
  - If a checkmate is indicated, the program prints "Checkmate".

        ___________________________
        |        Checkmate        |
        ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
- Stalemate
  - If a stalemate is indicated, the program prints "Stalemate".

        ___________________________
        |        Stalemate        |
        ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾

## User input format:
- Accepts input of the form "FileRank FileRank".
  - The first "FileRank" indicates the coordinates of the piece to be moved, and the second indicates where to move it to.
  - For example, moving white Pawn e2 => e3: 

        ---------------------------
        White move: e2 e3

- Castling move
  - Using where the king begins and ends. 
  - For example, move white King e1 => g1, and white Rook h1 => f1:

        ---------------------------
        White move: e1 g1

- Pawn Promotion
  - Append the piece to be promoted after the move with a space.
  - If no promotion is indicated, assumes it promote to a **Queen**.
  - For example, moves white Pawn p7 => p8, and promote it to a Knight:

        ---------------------------
        White move: g7 g8 N

## Ending the game:
- Resign:
  - A player can resign by entering "resign".
  - For example, white player resigns:

        ---------------------------
        White move: resign
- Draw:
  - Offer a draw by appending "draw?" to the end of an otherwise regular move.
  - For example:

        ---------------------------
        White move: e1 g1draw?

  - The draw can be acceped by the other player entering only "draw" on the next move.
        
        ---------------------------
        Black move: draw
- At the end of the game:
  - The program will prints out "White wins", "Black wins", or "draw".

        ___________________________
        |         White wins       |
        ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
        ___________________________
        |         Black wins       |
        ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
        ___________________________
        |           draw           |
        ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
