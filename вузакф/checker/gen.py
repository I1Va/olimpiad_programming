from random import *

n, m = randrange(2, 10), randrange(2, 10)
print(n, m)
k = randrange(1, 10)
print(k)
for i in range(k):
    x, y = 0, 0
    while (1):
        x, y = randrange(1, n + 1), randrange(1, m + 1)
        if (x == 1 and y == 1) or (x == n and y == m):
            continue
        break
    print(x, y)
