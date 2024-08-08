n = int(input())
a = list(map(int, input().split()))

def f(P):
    global sz, sim, x
    res = 0
    for i in range(sz):
        res += P ** i * sim[i]
    return res - x


for x in a:
    # print(x)
    sim = [int(w) for w in str(x)]
    sz = len(str(x))
    ans = []
    for P in range(-10 ** 3, 10 ** 3):
        if not f(P):
            ans.append(P)
    print(len(ans))
    print(*ans)