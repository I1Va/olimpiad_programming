q = int(input())

def f(a, p, b, n):
    a1 = [0] * n
    #print("a: ", a)
    #print("b: ", b)
    for i in range(n):
        a1[p[i] - 1] = a[i]
    c = 0
    #print(a1)
    #print(b)
    for i in range(n):
        if a1[i] == 'n' or b[i][0] == 'n':
            continue
        if int(a1[i]) < int(b[i][0]):
            c += 1
    return c

for _ in range(q):
    n = int(input())
    a1 = input().split()
    a = [0] * n
    for i in range(n):
        if a1[i] == 'n':
            a[i] = [10**9, i]
        else:
            a[i] = [int(a1[i]), i]
    b1 = input().split()
    b = [0] * n
    for i in range(n):
        if b1[i] == 'n':
            b[i] = [-10**9, i]
        else:
            b[i] = [int(b1[i]), i]
    
    a.sort(key = lambda x : -x[0])
    b.sort(key = lambda x: -x[0])
    ai = 0
    bi = 0
    ans = [0] * n
    pool = []
    #print(a)
    #print(b)
    while ai < n and bi < n:
        #print(ai, bi)
        if b[bi][0] > a[ai][0]:
            
            pool.append(b[bi][1])
            bi += 1
        else:
            #print(f"pair: {a[ai]}, {b[bi]}")
            ans[a[ai][1]] = b[bi][1] + 1
            bi += 1
            ai += 1
        #print(ai, bi)
        #print()
    pi = 0
    while ai < n:
        ans[a[ai][1]] = pool[pi] + 1
        pi += 1
        ai += 1
    
    print(*ans)
    #print(f(a1, ans, b1, n))