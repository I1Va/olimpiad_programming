from random import *

n = randrange(1, 10)
q = randrange(0, n)
a = [0] * n
a[0] = randrange(40, 100)
for i in range(1, q + 1):
    a[i] = a[i - 1] - randrange(1, 3)
for i in range(q + 1, n):
    a[i] = a[i - 1] + randrange(1, 3) 

print(n)
#print("q = ", q)
print(*a)