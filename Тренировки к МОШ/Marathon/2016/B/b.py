def parse(s):
    res = []
    n = len(s)
    s = s + "   "
    buf = ""
    i = 0
    while i < n:
        temp = s[i] + s[i + 1]
        state = False
        if temp == ", ":
            j = i + 2
            while s[j].isdigit():
                temp += s[j]
                state = True
                j += 1
            if (s[j] + s[j + 1]) == ". ":
                res.append(buf)
                # print(f"add, buf = {buf}, temp = {temp}")
                buf = ""
                i += 2
            else:
                state = False
        if not state:
            buf += s[i]
            i += 1
    if len(buf):
        res.append(buf)
    return res
        
n = int(input())
d = {}
for i in range(n):
    s = input()
    for x in parse(s):
        if x not in d:
            d[x] = 0
        d[x] += 1

print(len(d))
for key, value in d.items():
    print(key)
    print(value)
