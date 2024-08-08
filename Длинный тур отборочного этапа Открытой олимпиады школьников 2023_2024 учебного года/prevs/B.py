
def find_m(l, r, idx):
    for i in range(l, r):
        if ((i >> idx) & 1):
            
def split(l, r, k):
    print(k, bin(k)[2:])
    a = [i for i in range(l, r)]
    for i in range(len(a)):
        a[i] ^= k
    print(a)
    a.sort()
    print(a)
    pool = []
    left = a[0]
    right = a[0]
    
    for i in range(1, len(a)):
        if a[i] == right + 1:
            right = a[i]
        else:
            pool.append([left, right])
            left = a[i]
            right = a[i]
    if left != right:
        pool.append([left, right])
    
    return pool

def f(l, r, idx):
    global k, a
    if idx < 0:
        return [l, r]
    if not((k >> idx) & 1):
        return f(l, r, idx - 1)
    m = r
    m = find_m(l, r, idx)
    # for i in range(l, r):
    #     if i >= (1 << idx):
    #         m = i
    #         break

    print(f"[{l}:{m}) [{m}, {r}) -> [{l + (1 << idx)}:{m + (1 << idx)}) [{m - (1 << idx)}, {r - (1 << idx)})")
    if (m == r):
        return f(l + (1 << idx), m + (1 << idx), idx - 1)
    return [f(l + (1 << idx), m + (1 << idx), idx - 1), f(m - (1 << idx), r - (1 << idx), idx - 1)]

left = 0
right = 16
k = 4
print(f(left, right, 20))
print()
print(split(left, right, k))

