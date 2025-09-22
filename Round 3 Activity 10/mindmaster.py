import random
from colorama import Fore, Back, Style, init
init(autoreset=True)

def main():
    coins = 0
    guesses = {}
    allowed_colors = ["R", "G", "B"]
    pattern = random_colors(allowed_colors, 4)
    # print(pattern) ## for debugging
    print(Fore.CYAN + "🔐 Pattern generated! Try to guess it (or type QUIT to exit).")
    while True:
        user_input = input("Enter your guess (4 colors from R, G, B): ").strip().upper()
        if user_input == "QUIT":
            print(Fore.CYAN + f"Game ended. The pattern was {pattern}. You earned {coins} coins.")
            if guesses:
                review_history(guesses)
            break

        if any(ch not in allowed_colors for ch in user_input) or len(user_input) != 4:
            print(Fore.RED + "❌ Invalid input. Make sure to use exactly 4 characters from R, G, B.")
            continue


        if user_input in guesses:
            print(Fore.YELLOW + "🔁 Already guessed that. Try another guess.")
            print_stats(guesses, user_input)
            continue

        result = match_pattern(user_input, pattern)
        guesses[user_input] = result
        coins += guesses[user_input]["coins"]
        
        # immediate feedback displauy for the current guess
        print(Fore.YELLOW + f"GUESS: {user_input}")
        print(f"Correct Positions: {result['correct_position']}")
        print(f"Correct Colors, Wrong Positions: {result['wrong_position_correct_color']}")
        print(f"Coins Earned This Guess: {result['coins']}")
        print(f"Total Coins: {coins}")
        print("------------------------------------------\n")

        if user_input == pattern:
            result = match_pattern(user_input, pattern)
            guesses[user_input] = result
            coins += guesses[user_input]["coins"]
            print(Fore.GREEN + Style.BRIGHT + f"🎉 Congrats! You cracked the pattern: {pattern} in {len(guesses)} attempts.")
            print(f"You earned {coins} coins!")
            review_history(guesses)
            break

#generates random color pattern
def random_colors(allowed_colors, n):
    return ''.join(random.choice(allowed_colors) for _ in range(n))

#matches guess and pattern
def match_pattern(user_input, pattern):
    coins = 0
    correct_pos = 0
    correct_color_wrong_pos = 0
    for user, bot in zip(user_input, pattern):
        if user == bot:
            coins += 2
            correct_pos += 1
        elif user in pattern:
                coins += 1
                correct_color_wrong_pos += 1
    return {"correct_position": correct_pos, "wrong_position_correct_color": correct_color_wrong_pos, "coins": coins}

#shows history
def review_history(guesses):
    print("Do you want to view your guess history? (y/n) ")
    yes_no = input().strip().lower()
    if yes_no == 'y':
        print_stats(guesses)

#prints complete stats
def print_stats(guess_dict, key = None):
    print()
    if not key:
        print(Fore.MAGENTA + Style.BRIGHT + Back.WHITE + "-------------- STATS --------------")
        for guess, stats in guess_dict.items():
            print(Fore.YELLOW + f"GUESS: {guess}")
            print(f"Correct Positions: {stats['correct_position']}")
            print(f"Wrong Positions Correct Colors: {stats['wrong_position_correct_color']}")
            print(f"Coins: {stats['coins']}")
    else:
        print("------------------------------------------\n")
        stats = guess_dict[key]
        print(Fore.YELLOW + f"GUESS: {key}")
        print(f"Correct Positions: {stats['correct_position']}")
        print(f"Wrong Positions Correct Colors: {stats['wrong_position_correct_color']}")
        print(f"Coins: {stats['coins']}")
    
    print("------------------------------------------\n")

if __name__ == "__main__":
    main()