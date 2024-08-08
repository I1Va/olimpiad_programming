from random import randrange, shuffle

n = randrange(2, 8)
m = randrange(1, n + 1)
a = [i for i in range(1, n + 1)]
shuffle(a)
a = a[:m]
a.sort()
print(n, m)
print(*a)