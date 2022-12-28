from cs50 import get_string

text = get_string("Text: ")

# function to get number of letters


def count_letters(texto):
    counLetters = 0
    for i in range(len(texto)):
        if (texto[i].isalpha()):
            counLetters += 1
    return counLetters

# function to get number of words


def count_word(texto):
    counWord = 1
    for i in range(len(texto)):
        if (texto[i] == " "):
            counWord += 1
    return counWord

# function to get number of sentences


def count_sentences(texto):
    counSentence = 0
    for i in range(len(texto)):
        if texto[i] == "." or texto[i] == "!" or texto[i] == "?":
            counSentence += 1
    return counSentence


# assign values to variables
l = count_letters(text)

w = count_word(text)

s = count_sentences(text)


# formula to get L and S
L = 100 * (l / w)

S = 100 * (s / w)

# getting index
clindex = round((0.0588 * L) - (0.296 * S) - 15.8)

# Print "Grade X" if X > 16, print "Grade 16+".
if clindex < 1:
    print("Before Grade 1")
elif clindex > 16:
    print("Grade 16+")
else:
    print(f"Grade {clindex}")
