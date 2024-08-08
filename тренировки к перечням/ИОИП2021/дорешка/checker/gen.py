from random import *
a = [chr(i) for i in range(ord("a"), ord("d") + 1)]
maxn = 3
maxl = 5
n = randrange(1, maxn)
m = randrange(1, maxn)
print(n, m)
for i in range(n):
    l = randrange(1, maxl)
    print("".join([a[randrange(len(a))] for i in range(l)]))
for i in range(m):
    print(randrange(1, maxn))

print(1)
l = randrange(1, maxl)
print("".join([a[randrange(len(a))] for i in range(l)]))