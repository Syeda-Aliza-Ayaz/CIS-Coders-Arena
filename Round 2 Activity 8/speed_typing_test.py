import pyfiglet
import time
import sys
import random

def main():
    banner = pyfiglet.figlet_format("Speed Typing Test", font = "ANSI_Shadow")
    print(banner)

    print("You will have 60 seconds to type as many lines as you can.")
    
    #fetching data from file
    file_content = []
    with open("text.txt", "r") as file:
        for line in file:
            file_content.append(line.strip())
    
    #test starts
    random_lines = random.sample(file_content, len(file_content))
    permission = input("Press Enter whenever you are ready!")
    no_of_lines = 0
    words_given = 0
    words_typed = 0 #since wpm = total words typed / minutes elapsed, and it is calculated for 1 minute
    correct_chars = 0
    total_chars = 0
    if permission == "":
        start = time.time()
        for line in random_lines:
            elapsed = time.time() - start
            time_left = 60 - elapsed
            if elapsed >= 60:
                break
            print(f"Type the following text as fast as you can:\n{line}")
            no_of_lines += 1
            total_chars += len(str(line))
            char_list = list(line)
            words_given += len(str(line).split())
            if time_left > 0:
                print(f"\nTime left: {time_left:.0f} seconds")
            prompt = input("Start typing below:\n")
            words_typed += len(prompt.split())
            for char_line, char_prompt in zip(char_list, prompt):
                if char_line == char_prompt:
                    correct_chars += 1
        result = pyfiglet.figlet_format("Results", font = "big")
        print(result)
        if total_chars > 0:
            accuracy_percentage = (correct_chars / total_chars) * 100
        else:
            accuracy_percentage = 0
        print(f"Lines given: {no_of_lines}")
        print(f"Words given: {words_given}")
        print(f"Words typed: {words_typed}")
        print(f"Your WPM (Words Per Minute): {(words_typed / elapsed) * 60:.2f}")
        print(f"Accuracy: {accuracy_percentage:.2f}%")
    else:
        sys.exit("Invalid input. Try again!")

if __name__ == "__main__":
    main()
