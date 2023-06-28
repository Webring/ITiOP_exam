from random import choices, shuffle

NUMBER_OF_WORDS = 100
WORDS_LEN = 6

ALPHABET = "abcdefghijklmnopqrstuvwxyz"

words = ["".join(choices(ALPHABET, k=WORDS_LEN)) for _ in range(NUMBER_OF_WORDS)]

with open("words.txt", mode="w", encoding="utf-8") as file:
    print(*words, sep="\n", end="", file=file)

words.sort()

with open("words_sorted.txt", mode="w", encoding="utf-8") as file:
    print(*words, sep="\n", end="\n", file=file)