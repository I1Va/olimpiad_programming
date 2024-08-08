from math import gcd

n, m, k = map(int, input().split())
a = input()
b = input()
c = input()
#print(f'{a}.{b}({c})')

def get(up, down):
    x = down // gcd(up, down)
    #print("x = ", x)
    a = set()
    while (x > 1):
        for i in range(2, x + 1):
            if x % i == 0:
                x //= i
                a.add(i)
                break
    a = list(a)
    #print("a = ", a)
    ans = 1
    for w in a:
        ans *= w
    return ans

if (len(c) == 0 or c == "0"):
    up = int(a + b)
    down = 10 ** m
else:
    up = int(a + b + c) - int(a + b)
    down = 10 ** (m + k) - 10 ** m
#print(up, down)
print(get(up, down) % (10 ** 9 + 7))

