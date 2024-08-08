from random import randrange

n = 6
m = 4

print(n, m)
print(*[randrange(2) for i in range(n)])
for i in range(m):
    t = randrange(1, 3)
    l = randrange(1, n + 1)
    r = randrange(l, n + 1)
    print(t, l, r)