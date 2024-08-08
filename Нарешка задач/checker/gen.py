from random import *
n = randrange(1, 10)
k = randrange(1, n + 1)
print(1)
print(n, k)
a = [randrange(-10, 10) for i in range(n)]
a[k - 1] = randrange(0, 10)
print(*a)