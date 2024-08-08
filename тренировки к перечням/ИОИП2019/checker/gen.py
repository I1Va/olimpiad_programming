from random import *
q = [1]

n = randrange(1, 11)
unused = [i for i in range(2, n + 1)]

print(n)
for i in range(n - 1):
    cur = q[randrange(len(q))]
    ver = unused[randrange(len(unused))]
    print(*[[cur, ver], [ver, cur]][randrange(2)])
    unused.pop(unused.index(ver))
    q.append(ver)

