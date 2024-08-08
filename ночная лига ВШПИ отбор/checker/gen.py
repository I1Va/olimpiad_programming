from random import *

q = 1
n = randrange(1, 10)
s = randrange(1, 10)
print(q, n, s)
for i in range(s):
    x, y = randrange(1, n + 1), randrange(1, n + 1)
    r = randrange(1, 7)
    t = randrange(0, r)
    print(x, y, r, t)

print(0, 0)
print(0, 0)