def info(a):
    xor = [0] * n
    for i in range(n):
        res = 0
        for j in range(n):
            if i == j:
                continue
            res ^= a[j]
        xor[i] = res

    xor1 = [0] * n
    for i in range(n):
        res = 0
        for j in range(n):
            res ^= a[j]
        xor1[i] = res

    xor2 = xor1.copy()
    for i in range(n):
        xor2[i] = xor1[i] ^ a[i]

    print(a)
    print(xor)
    print(xor1)
    print(xor2)

def f(a):
    res = 0
    for x in a:
        res ^= x
    return res

a = [2, 4, 2, 5, 7]
print(f(a))
n = len(a)


