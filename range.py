#!/usr/bin/python3
import random

num = int(input("Введите правую границу последовательности\n"))

for n in range(num):
    print(random.randrange(0, 1000, 3), end=' ')
