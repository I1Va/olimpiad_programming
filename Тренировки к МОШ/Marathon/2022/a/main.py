t = int(input())

for _ in range(t):
    n = int(input())
    a = list(map(int,input().split()))
    used = 1
    cur = [0]
    num = 1
    ans = []
    for i in range(n - 2, -1, -1):
        idx = 0
        next = []
        for j in range(a[i] - used):
            ans.append([cur[idx], num])
            next.append(num)
            num += 1
            idx = (idx + 1) % len(cur)
        cur = next
        used = a[i]
    print(a[0])
    for x in ans:
        print(*x)
    print()
