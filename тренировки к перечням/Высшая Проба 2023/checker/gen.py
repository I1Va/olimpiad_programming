from random import *
print(1)
n = randrange(1, 5)
print(n)
a = [randrange(1, 10) for i in range(n)]
b = [randrange(a[i], 11) for i in range(n)]
print(*a)
print(*b)