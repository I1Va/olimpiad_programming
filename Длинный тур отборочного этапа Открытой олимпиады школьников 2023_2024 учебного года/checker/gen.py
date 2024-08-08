from random import *

n = randrange(1, 3)
print(n)
n = 2 ** n
a = [randrange(1, 10) for i in range(n)]
print(*a)
m = randrange(1, 4)
print(m)
for i in range(m):
    t = randrange(1, 3)
    v = -1
    l, r, k = randrange(0, n), randrange(0, n), randrange(0, n)
    if (t == 1):
        v = randrange(1, 10)
        print(t, l, r, k, v)
    else:
        print(t, l, r, k)
    