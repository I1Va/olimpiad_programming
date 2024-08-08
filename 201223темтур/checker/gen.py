from random import randrange

n = randrange(1, 5)
print(n)
print(*[randrange(-5, 5) for i in range(n)])