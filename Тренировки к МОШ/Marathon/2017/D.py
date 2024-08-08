q, n = map(int, input().split())
for _ in range(q):
    s = input()
    s = s.split("|")
    for i in range(len(s)):
        s[i] = s[i].replace("&", "")
        s[i] = s[i].replace("v", "")
        s[i] = s[i].split()
    used = [False] * n
    c = 0
    for x in s:
        for y in x:
            i = -1
            if y[0] == "!":
                i = int(y[1:]) - 1
            else:
                i = int(y) - 1
            used[i] = True
    for x in used:
        if not x:
            c += 1  
    #print(s)
    used = [False] * n
    ans = (1 << (len(s))) * (1 << c) 
    print(ans)
            