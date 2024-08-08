from random import *

n = randrange(4, 6)
m = randrange(3, 6)

print(n, m)
print(*[randrange(1, n + 1) for i in range(m)])
b = [i for i in range(1, n + 1)]
shuffle(b)
print(*b)