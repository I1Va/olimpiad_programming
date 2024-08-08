t = int(input())
for _ in range(t):
    n = int(input())
    a = list(map(int, input().split()))
    a = [[a[i], i] for i in range(n * 2)]
    a.sort(key = lambda x: -x[0])
    ans = 0
    p = []
    for i in range(1, 2 * n, 2):
        ans += int(str(a[i - 1][0]) + str(a[i][0]))
        p.append([a[i - 1][1] + 1, a[i][1] + 1])
    print(ans)
    for x in p:
        print(*x)
    print()

