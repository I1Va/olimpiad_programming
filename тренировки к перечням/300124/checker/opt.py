
n = 70
A, B, R = 0, 0, 0
def solve1():
    global A, B, R, n
    a, b, r = A, B, R
    d = a - b
    while 1:
        cur = d
        idx = -1
        for i in range(n, -1, -1):
            if (((a >> i) & 1) == ((b >> i) & 1)):
                continue
            if ((1 << i) > r):
                continue
            if (((a >> i) & 1) == 0):
                if (abs(d + 2 * (1 << i)) <= abs(cur)):
                    cur = d + 2 * (1 << i)
                    idx = i
            else:
                if (abs(d - 2 * (1 << i)) <= abs(cur)):
                    cur = d - 2 * (1 << i)
                    idx = i
        if (idx == -1):
            break
        
        a ^= (1 << idx)
        r -= (1 << idx)
        d = cur
    return abs(d)

def solve2():
    global A, B, R, n
    a, b, r = A, B, R

    d = a - b
    state = False
    while 1:
        cur = d
        idx = -1
        for i in range(n, -1, -1):
            if (((a >> i) & 1) == ((b >> i) & 1)):
                continue
            if ((1 << i) > r):
                continue
            if not state:
                state = True
                continue

            if (((a >> i) & 1) == 0):
                if (abs(d + 2 * (1 << i)) <= abs(cur)):
                    cur = d + 2 * (1 << i)
                    idx = i
            else:
                if (abs(d - 2 * (1 << i)) <= abs(cur)):
                    cur = d - 2 * (1 << i)
                    idx = i
        if (idx == -1):
            break
        
        a ^= (1 << idx)
        r -= (1 << idx)
        d = cur
    return abs(d)


t = int(input())
for i in range(t):
    A, B, R = map(int, input().split())
    print(min(solve1(), solve2()))