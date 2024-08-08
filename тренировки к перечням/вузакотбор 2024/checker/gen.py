from random import *

n, q = randrange(1, 10), randrange(1, 2)

print(n, q)
for i in range(q):
    x = randrange(1, n + 1)
    d = randrange(0, n - 1 + 1)
    print(x, d)