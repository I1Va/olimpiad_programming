from random import *

n = randrange(5, 7)
a = [randrange(1, 4) for i in range(n)]
print(n)
print(*a)
m = 3
print(m)

for i in range(m):
    c = ["?", "!"][randrange(2)]
    if c == "!":
        pos, val = randrange(1, n + 1), randrange(1, 4)
        print(c, pos, val)
    else:
        l = randrange(1, n + 1)
        r = randrange(l, n + 1)
        t = randrange(1, 3)
        print(c, l, r, t)