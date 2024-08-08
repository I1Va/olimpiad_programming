def upd():
    global a
    n = len(a)
    m = [a[:n // 2], a[n // 2:]]
    idx = [0, 0]
    t = 0
    res = []
    for i in range(n):
        res.append(m[t][idx[t]])
        idx[t] += 1
        t = (t + 1) % 2
    a = res
    
sz = 64
a = [i for i in range(0, sz)]
st = a
print(f"{0}:{a[:10]}...")
for i in range(1, 10):
    upd()
    print(f"{i}:{a[:10]}...")
print()
# idx = 1
# upd()
# while st != a:
#     print(a)
#     upd()
#     idx += 1
# print(idx)
# print(f"{idx}:{a}")