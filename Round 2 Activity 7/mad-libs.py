def main():
    with open("story.txt", "r") as file:
        story = file.read()
        parts = story.split('<')
        placeholders = set()
        info = {}
        for i in range(1, len(parts)):
            placeholder = parts[i].split('>')[0] # store 0th index of list returned
            placeholders.add(f"<{placeholder}>")
        for part_of_speech in placeholders:
            word = input(f"Enter a word for {part_of_speech}: ")
            info[part_of_speech] = word
            story = story.replace(part_of_speech, info[part_of_speech])

    with open("story.txt", "w") as file:
        file.write(story) 

if __name__ == "__main__":
    main()