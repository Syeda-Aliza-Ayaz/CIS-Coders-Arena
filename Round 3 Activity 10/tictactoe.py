"""
         0   1   2 ---> (position-1)%3
----------------------------------------------         
    0    1 | 2 | 3       ->     [0][0] | [0][1] | [0][2]
    1    4 | 5 | 6       ->     [1][0] | [1][1] | [1][2]
    2    7 | 8 | 9       ->     [2][0] | [2][1] | [2][2]
row: (position-1)//3
"""
from colorama import Fore, Back, Style, init
init(autoreset=True)

def main():
    board = [[" " for _ in range(3)] for _ in range(3)]
    used_positions = set()
    user_X = []
    user_O = []

    print("""
The board positions are as follows:
 1 | 2 | 3
---+---+---
 4 | 5 | 6
---+---+---
 7 | 8 | 9
    """)

    current_player = "X"

    while True:
        try:
            print_board(board)
            pos = int(input(f"Player {current_player}, choose a position (1-9): "))

            if pos < 1 or pos > 9:
                print(Fore.RED + "❌ Position must be between 1 and 9.")
                continue

            if pos in used_positions:
                print(Fore.RED + "❌ That position is already taken.")
                continue

            row, col = get_coordinates(pos)
            board[row][col] = current_player
            used_positions.add(pos)

            if current_player == "X":
                user_X.append(pos)
                if win_condition(user_X):
                    print_board(board)
                    print(Fore.GREEN + "🎉 Player X wins!")
                    break
                current_player = "O"
            else:
                user_O.append(pos)
                if win_condition(user_O):
                    print_board(board)
                    print(Fore.GREEN + "🎉 Player O wins!")
                    break
                current_player = "X"

            if len(used_positions) == 9:
                print_board(board)
                print(Fore.BLUE + "🤝 It's a draw!")
                break

        except ValueError:
            print(Fore.RED + "❌ Invalid input. Please enter a number between 1 and 9.")

def print_board(board):
    print(Fore.MAGENTA + "\nCurrent board:")
    for i in range(3):
        print(f" {board[i][0]} | {board[i][1]} | {board[i][2]} ")
        if i < 2:
            print("---+---+---")

def win_condition(player_board):
    winning_conditions = [
        [1, 2, 3], [4, 5, 6], [7, 8, 9],
        [1, 4, 7], [2, 5, 8], [3, 6, 9],
        [1, 5, 9], [3, 5, 7]
    ]
    for combo in winning_conditions:
        if all(pos in player_board for pos in combo):
            return True
    return False

def get_coordinates(pos):
    return (pos - 1) // 3, (pos - 1) % 3

if __name__ == "__main__":
    main()
