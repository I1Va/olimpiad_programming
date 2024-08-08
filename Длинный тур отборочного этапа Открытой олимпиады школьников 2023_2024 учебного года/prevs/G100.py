n, A, B = map(int, input().split())
t = list(map(int, input().split()))
def comp1(x):
    global n, A, B
    s = 0
    for i in range(n):
        l = -1
        r = x + 1
        while r - l > 1:
            m = (l + r) // 2
            if m * A + (x - m) * B > t[i]:
                r = m
            else:
                l = m
        s += r
    return s <= x

def solve1():
    global n, A, B
    l = -1
    r = 10 ** 9
    while r - l > 1:
        m = (l + r) // 2
        if comp1(m):
            r = m
        else:
            l = m
    print(r)

def comp2(x):
    global n, A, B
    cur = B * x
    s = 0
    for i in range(n):
        if t[i] >= cur:
            return False
        if (cur - t[i]) % (B - A) == 0:
            s -= 1
        s += (cur - t[i]) // (B - A)
    return s >= x

def solve2():
    global n, A, B
    l = -1
    r = 10 ** 9
    while r - l > 1:
        m = (l + r) // 2
        if comp2(m):
            r = m
        else:
            l = m
    print(r)

if A > B:
    solve1()
elif A < B:
    solve2()
else:
    mx = max(t)
    if mx < 0:
        print(0)
    else:
        if mx % B == 0:
            print(mx // B + 1)
        else:
            print((mx + B - 1) // B)