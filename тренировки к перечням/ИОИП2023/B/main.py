a, b, t = map(int, input().split())

def chet_cnt_a(x):
    global t
    c0 = t // 2
    q = c0 // (x // 2)
    return (c0 - x // 2 + c0 - q * x // 2) * q // 2

def nech_cnt_a(x):
    global t
    c1 = (t + 1) // 2
    q = (c1 - x // 2) // x
    return (c1 - x // 2 + c1 - x // 2 - (q - 1) * x) * q // 2

def chet_cnt_b(x):
    global t
    c1 = (t + 1) // 2
    q = c1 // (x // 2)
    return (c1 - x // 2 + c1 - q * x // 2) * q // 2

def nech_cnt_b(x):
    global t
    c0 = t // 2
    q = (c0 - x // 2) // x
    return (c0 - x // 2 + c0 - x // 2 - (q - 1) * x) * q // 2

def get(a, b):
    global t
    c1 = (t + 1) // 2
    c0 = t // 2
    print(c0, c1)
    res = t
    if a == 1:
        res += (1 + t // 2) * t // 2
    elif (a % 2 == 0):
        res += chet_cnt_a(a)
    else:
        print(chet_cnt_a(2 * a), nech_cnt_a(a))
        res += chet_cnt_a(2 * a)
        res += nech_cnt_a(a)
    if (b == 1):
        res += (1 + (t - 1) // 2) * (t - 1) // 2
    if (b % 2 == 0):
        res += chet_cnt_b(b)
    else:
        res += chet_cnt_b(2 * b)
        res += nech_cnt_b(b)
    return res

print(get(a, b))
#print(get(a, b), get(b, a))

