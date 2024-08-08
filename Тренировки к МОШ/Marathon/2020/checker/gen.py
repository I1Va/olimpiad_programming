from random import *
print(1)
n = randrange(1, 10)
alp = [1, 2, 3, 4, 5, "n"]

a = [alp[randrange(len(alp))] for i in range(n)]
b = [alp[randrange(len(alp))] for i in range(n)]
print(n)
print(*a)
print(*b)