def get(x):
    res = 0
    p = []
    while x > 1:
       
        state = True
        for i in range(2, int(x ** 0.5) + 1):
            if x % i == 0:
                state = False
                p.append(i)
                p.append(x // i)
                x //= i
                break
        if state:
            p.append(x)
            break
    return p

print(get(1402520910))