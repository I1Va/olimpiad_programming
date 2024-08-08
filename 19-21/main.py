from functools import lru_cache
from sys import setrecursionlimit
setrecursionlimit(10 ** 3)
#dp = [["*"] * 100 for i in range(100)]

# + 1
# * 2
@lru_cache(None)
def f(a, b):
    if (a + b >= 59):
        return 0
    t = [f(a + 1, b), f(a * 2, b), f(a, b + 1), f(a, b * 2)]
    n = [i for i in t if t <= 0]
    if n:
        return -max(n) + 1
    else:
        return -max(t)

for i in range(0, 100):
    if f(5, i) == 2:
        print(i)