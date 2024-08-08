def fact(x):
    res = []
    while (x > 1):
        for i in range(2, x + 1):
            state = False
            while x % i == 0:
                x //= i
                state = True
            if state:
                res.append(i)
    return res

t = int(input())
for _ in range(t):
    a, b = map(int, input().split())
    cur = fact(a)
    for x in cur:
        c = 0
        while x * c < b:
