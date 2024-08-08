s = input().split()
d = {}
for x in s:
    if x[0] == "#" and x.count("#") == 1 and len(x) >= 2:
        if x not in d:
            d[x] = 0
        d[x] += 1
print(len(d))
for key, value in d.items():
    print(key, value)