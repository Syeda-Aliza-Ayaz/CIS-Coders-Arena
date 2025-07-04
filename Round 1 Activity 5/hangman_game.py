import random # this library has random generation and choice functions

## word bank
wordBank = [
    "tiger", "dolphin", "elephant", "kangaroo", "panda",
    "banana", "pineapple", "cherry", "mango", "strawberry",
    "canada", "brazil", "egypt", "germany", "japan",
    "guitar", "rainbow", "cupcake", "wizard", "unicorn",
    "computer", "python", "notebook", "adventure", "astronaut"
]

## random word from list
word = random.choice(wordBank)
# print(word)

## length of word
wordLength = len(word)

## guessed letters, initially all are marked as '_'
guessed_letters = []
for i in range(wordLength):
    guessed_letters.append("_")

## used and repeated letters
used_letters = []

## score
score = 0

## game starts
print("------------------ 🕹️  WELCOME TO HANGMAN ------------------")
print("Guess the word letter by letter")
while "_" in guessed_letters:
    print("Word:", end=" ")
    for item in guessed_letters:
        print(item + " ", end="")
    print("\nScore:", score)
    
    letter = input("Enter a single letter: ")
    
    #if letter is a digit
    if not letter.isalpha():
        print("‼️  Invalid Input! Please enter a letter.")
        continue

    # letter's length is more than 1  
    elif len(letter) != 1:
        print("‼️  Invalid Input! Please enter only one letter.")
        continue
    
    # Repeated letter
    elif letter in used_letters:
        print("❗  Repeated Letter!")
        score -= 1
        continue
    
    used_letters.append(letter)
    
    if letter in word:
        score += 1
        for i in range(wordLength):
            if word[i] == letter:
                guessed_letters[i] = letter
        print("✔️  Correct guess!")
    else:
        score -= 1
        print("❌  Wrong guess!")

print(f"🎉 You guessed the word: {word} with a score of {score}!")



