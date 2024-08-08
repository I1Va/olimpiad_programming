a, b, n, m = map(int, input().split())

# y = 0

if m % 2 == 0 and n == m // 2:
    print(n, 0)
    exit(0)
if b - 2 * a != 0 and (m - 2 * n) % (b - 2 * a) == 0:
    y = (m - 2 * n) // (b - 2 * a)
    x = n - y * a
    if x >= 0 and y >= 0:
        print(x, y)
        exit(0)

if n % a == 0 and m % b == 0 and n // a == m // b:
    print(0, n // a)
    exit(0)

print(-1)