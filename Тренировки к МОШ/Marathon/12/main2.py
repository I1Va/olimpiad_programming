def get(s):
    p = 1
    for x in s:
        if x == "1":
            p *= 0.6
        else:
            p *= 0.4
    return p

for mask in range(0, 8):
    s = bin(mask)[2:]
    s = "0" * (3 - len(s)) + s
    print(s, get(s))

