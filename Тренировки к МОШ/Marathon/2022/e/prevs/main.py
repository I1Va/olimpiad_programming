t = int(input())
for _ in range(t):
    n = int(input())
    a = list(map(int, input().split()))
    a = [[a[i], i] for i in range(n * 2)]
    a.sort(key = lambda x: -x[0])
    lens = []
    for x in a:
        lens.append([len(str(x[0]))] + x)
    #print(lens)
    used = [False] * (2 * n)
    ans = 0
    p = []
    for i in range(2 * n):
        if used[a[i][1]]:
            continue
        used[a[i][1]] = True
        # Найдем самое длинное число с наименьшим значением
        mx_l = 0
        mn_val = 0
        idx = -1
        for x in lens:
            if used[x[2]]:
                continue
            if x[0] > mx_l or (x[0] == mx_l and x[1] < mn_val):
                mx_l = x[0]
                mn_val = x[1]
                idx = x[2]
        used[idx] = True
        ans += int(str(a[i][0]) + str(mn_val))
        p.append([a[i][1] + 1, idx + 1])
        #print(list(map(int, used)), p[-1])
    print(ans)
    for x in p:
        print(*x)

        

