a = [10, 11, 14, 16, 19, 23, 29, 39, 58, 117]
w = 117
for x in a:
    c = w // x
    print(w % x, w % c)