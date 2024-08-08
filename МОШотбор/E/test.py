with open("e2.txt", "r") as f:
    t = f.readline()
    word = f.readline()
    dig = f.readline()
    d = {}
    print(f"word_len: {len(word)}, dig_len: {len(dig)}")
    for x in word:
        if x not in d:
            d[x] = 0
        d[x] += 1
    for key, value in d.items():
        print(f"{key}:{value}")
