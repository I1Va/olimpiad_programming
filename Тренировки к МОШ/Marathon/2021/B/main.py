from sys import setrecursionlimit
setrecursionlimit(10**6)
def dfs(v):
    global color, cur, g
    color[v] = cur
    for u in g[v]:
        if not color[u]:
            dfs(u)


q = int(input())
for _ in range(q):
    s1 = input().split()
    s2 = input().split()
    d = {}
    n = 0
    for word in s1:
        if word not in d:
            d[word] = n
            n += 1
    for word in s2:
        if word not in d:
            d[word] = n
            n += 1
    g = [[] for i in range(n)]
    for i in range(len(s1)):
        g[d[s1[i]]].append(d[s2[i]])
        g[d[s2[i]]].append(d[s1[i]])
    color = [0] * n
    cur = 1
    for i in range(n):
        if not color[i]:
            dfs(i)
            cur += 1
    grp = [0] * cur
    for i in range(n):
        grp[color[i]] += 1
    grp.sort()
    ans = []
    for x in grp:
        if x > 1:
            ans.append(x)
    print(len(ans))
    print(*ans)
    print()


