n = int(input())
a, b = map(int, input().split())
l = abs(a - b) - 1
l = min(l, n - 2 - l)
if (a == b):
    print(n // 2)
    exit(0)

t1 = n - l - 2
t2 = (n + l - 1) // 2
t3 = (2 * n - l - 2) // 3
print(min([t1, t2, t3]))