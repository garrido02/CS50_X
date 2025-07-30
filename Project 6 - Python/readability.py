from cs50 import get_string
import string
import re


def main():

    # promp user for text and then take punctuation out
    text = get_string("Text: ")
    filtered_text = text.translate(str.maketrans('', '', string.punctuation))

    # create a function to count words and filter punctuation
    words = text.split()
    filtered_words = filtered_text.split()

    # count words
    word_count = count_word(words)

    # create function to count letters, i will assume each word of the filtered list and count their length
    letter_count = count_letter(filtered_words)

    # create a function to count sentences, i will assume each word and if they have punct then its 1 sentence
    sentence_count = count_sentence(words)

    # grade counter
    l = letter_count / word_count * 100
    s = sentence_count / word_count * 100
    grade = round(0.0588 * l - 0.296 * s - 15.8)

    if grade >= 16:
        print("Grade 16+")
    elif grade < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {grade}")


def count_word(words):
    word_count = len(words)
    return word_count


def count_letter(filtered_words):
    letter_count = 0
    for i in filtered_words:
        letter_count += len(i)
    return letter_count


def count_sentence(words):
    # define the punctuation that separate sentences
    punct = ["!", "?", "."]

    # implement counter
    sentence_count = 0
    for i in words:
        if any(char in i for char in punct):
            sentence_count += 1
    return sentence_count


main()