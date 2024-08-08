from random import *

n = randrange(1, 70)
k = randrange(1, 70)
print(n, k)
print(*[randrange(1, 10000) for i in range(n)])