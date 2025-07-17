import random
import pyfiglet 

def main():
    #printing stuff
    banner = pyfiglet.figlet_format("Digital Root Game!")
    print(banner)
    print("Welcome to the Digital Root Challenge 🧮")
    print("Test your number sense, guess the digital roots, and spot special numbers!\n")
    
    #Game logic
    score = 0 #score of the user
    for rounds in range(1, 4): #tracks rounds
        number = play_game(rounds) #random number between specified range
        print(f"Round {rounds}")
        print(f"Number: {number}")
        try:
            user_digital_root = int(input("What will be the digital root? "))
            digital_root_calulated = calculate_digital_root(number) #returns a list of steps
            if digital_root_calulated[-1] == user_digital_root:
                print("Voila! +5 points\n")
                score += 5
            else:
                print("Oops! That's incorrect. Try again next time.\n")
            show_digital_root_ladder(digital_root_calulated)
            print()
            special_number = input("Is this a special number? (y/n): ")
            if not special_number.isalpha():
                raise ValueError
            if is_special_number(number) and special_number.lower() == 'y':
                print("Voila! +3 bonus points\n")
                score += 3
            elif not is_special_number(number) and special_number.lower() == 'n':
                print("Voila! +3 bonus points\n")
                score += 3
            else:
                print("Oops! That's incorrect. Try again next time.\n")
        except ValueError:
            print("Invalid input! Please enter a valid input. Restarting this round...\n")
            continue
    print("Game Over!")
    print(f"Your final score is: {score}/24")




def play_game(rounds):
        if rounds == 1:
            return random.randint(100, 199) # number between 100 and 199 inclusive
        if rounds == 2:
            return random.randint(200, 299) # number between 200 and 299 inclusive
        if rounds == 3:
            return random.randint(300, 399) # number between 300 and 399 inclusive

def calculate_digital_root(number):
    digital_root_ladder = [number]
    while not number < 10:
        sum = 0
        temp_num = number
        while temp_num != 0:
            sum += temp_num % 10
            temp_num //= 10 #for int division
        number = sum
        digital_root_ladder.append(number)
    return digital_root_ladder


def show_digital_root_ladder(ladder):
    print("Here's how the digital root is calculated:")
    for i in range(1, len(ladder)):
        print(f"{ladder[i - 1]} -> {ladder[i]}")
    return


def is_special_number(number):
    palindrome = is_palindrome(number)
    sum_product = is_sum_equal_product(number)
    return palindrome or sum_product

def is_palindrome(number):
    return str(number) == str(number)[::-1] #[start from end because step is -ve, go till beginning, go backwards]


def is_sum_equal_product(number):
    sum = 0
    product = 1
    for digit in str(number):
        digit = int(digit)
        sum += digit
        product *= digit
    return product == sum


if __name__ == "__main__":
    main()