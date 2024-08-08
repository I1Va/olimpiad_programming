from random import randrange

while 1:
    n = 6
    m = 5
    edges = []
    for i in range(m):
        v = randrange(1, n + 1)
        u = randrange(1, n + 1)
        t = randrange(1, 9)
        edges.append([v, u, t])
    a = [[] for i in range(n)]
    state = True
    for x in edges:
        if (x[2] in a[x[0] - 1]):
            state = False
            break
        a[x[0] - 1].append(x[2])

        if (x[2] in a[x[1] - 1]):
            state = False
            break
        a[x[1] - 1].append(x[2])
    if state:
        print(n, m)
        for x in edges:
            print(*x)
        exit(0)