n = int(input())
x, y = map(int, input().split())
a = abs(x - y) - 1
a = min(a, n - 2 - a)
if (x == y):
    print(n // 2)
    exit(0)

t1 = n - a - 2
t2 = (n + a - 1) // 2
t3 = (2 * n - a - 2) // 3
print(min([t1, t2, t3]))

