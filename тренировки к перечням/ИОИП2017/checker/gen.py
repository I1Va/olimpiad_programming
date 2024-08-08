from random import *
# a = [i for i in range(100000)]
# shuffle(a)
# a = a[:(g + r + b)]

maxn = 10
g, r, b = randrange(1, maxn), randrange(1, maxn), randrange(1, maxn)

print(g, r, b)
pool = [randrange(100, 1000) for i in range(100)]
shuffle(pool)
print(*[pool[randrange(10)] for i in range(g)])
print(*[pool[randrange(10)] for i in range(r)])
print(*[pool[randrange(10)] for i in range(b)])