txt = input("Text: ")

sentences = 0
letters = 0
words = 1

for lttr in txt:
    if (lttr == "!" or lttr == "." or lttr == "?"):
        sentences += 1

    if (lttr.isalpha()):
        letters += 1

    if (lttr == " "):
        words += 1

lettersperwords = letters*(100/words)
sentencesperwords = sentences*(100/words);

gradelvl = round((0.0588 * lettersperwords) - (0.296 * sentencesperwords) - 15.8)

if (gradelvl < 1):
    print("Before Grade 1");
elif (gradelvl >= 16):
    print("Grade 16+");
else:
    print("Grade " + str(gradelvl));