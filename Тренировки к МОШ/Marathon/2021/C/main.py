q = int(input())

for _ in range(q):
    n = int(input())
    a = list(map(int, input().split()))
    a = [[a[i], i] for i in range(n)]
    a.sort(key= lambda x: x[0])
    pool = []
    for x in a:
        if x[0] == 1:
            pool.append(x)
        else:
            