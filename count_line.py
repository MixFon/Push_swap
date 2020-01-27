#!/usr/bin/python3

m = input()
count = 0
while m != '\0':
    try:
        m = input()
    except EOFError:
        print(count)
        exit()
    if m == "pb" or m == 'pa' or m == 'ra' or m == 'rb' or m == 'rr' or m == 'rra' or m == 'rrb' or m == 'rrr'or m == 'sa' or m == 'sb' or m == 'ss':
        count += 1
        print(m)
       # print(count)
