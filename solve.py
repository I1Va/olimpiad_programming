t = int(input())

inf = 1e18
for q in range(t):
    n = int(input())
    s1 = str(input()).split()
    s2 = str(input()).split()

    for i in range(n):
        if s2[i] == 'n':
            s2[i] = [-inf, i]
        else:
            s2[i] = [int(s2[i]), i]        
    for i in range(n):
        if s1[i] == 'n':
            s1[i] = [inf, i]
        else:
            s1[i] = [int(s1[i]), i]

    s1.sort()
    s2.sort()

    uk = n - 1
    ans = [0 for _ in range(n)]

    fr = 0
    for i in range(len(s2) - 1, -1, -1):
        if s1[uk][0] >= s2[i][0]:
            ans[s1[uk][1]] = s2[i][1] + 1
            uk -= 1
        else:
            ans[s1[fr][1]] = s2[i][1] + 1
            fr += 1
    
    print(f"{' '.join([str(x) for x in ans])}")
