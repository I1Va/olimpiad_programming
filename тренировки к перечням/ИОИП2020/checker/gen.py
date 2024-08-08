from random import *

n = randrange(1, 10)
print(n)
print(*[randrange(1, 20) for i in range(n)])