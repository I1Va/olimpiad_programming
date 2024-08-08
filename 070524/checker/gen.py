from random import randrange

n = randrange(3, 10)
k = randrange(1, n // 3 + 1)
a = [randrange(1, 10) for i in range(n)]
print(n, k)
print(*a)