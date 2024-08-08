from random import *

n, q = randrange(2, 10), 1

print(n, q)
for i in range(n):
    print(randrange(-n, n + 1), randrange(-n, n + 1))

for i in range(q):
    print(randrange(1, n + 1), randrange(1, n))

