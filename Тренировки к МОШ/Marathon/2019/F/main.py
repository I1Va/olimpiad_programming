q = int(input())

used = {}
coms = ""
ans = []

def get(x):
    res = ""
    while x != 1:
        if x % 2 == 0:
            res += "0"
        else:
            res += "1"
        x //= 2
    return res[::-1]
def rec(v, idx):
    global used, coms, ans
    if v not in used:
        used[v] = True
    if idx == len(coms):
        ans.append(v)
        return
    if coms[idx] == 'D':
        if v * 2 not in used:
            rec(v * 2, idx + 1)
        else:
            rec(v * 2 + 1, idx + 1)
    else:
        ans.append(v)
        if v % 2 == 0:
            rec(v + 1, idx + 1)
        else:
            while v % 2 != 0:
                v //= 2
            rec(v + 1, idx + 1)
for _ in range(q):
    used = {}
    coms = ""
    coms = input()
    ans = []
    rec(1, 0)
    #print(ans)
    print(len(ans))
    for x in ans:
        print(get(x))
    print()
    