n, c = map(int, input().split())
a = list(map(int, input().split()))
b = [0] * (n - c + 1)
b[0] = sum(a[:c])

for i in range(1, n - c + 1):
    b[i] = b[i - 1] + a[i + c - 1] - a[i - 1]

p = [0] * (n - c + 1)
s = [0] * (n - c + 1)

for i in range(c, n - c + 1):
    p[i] = max(p[i - 1], b[i - c])

for i in range(n - 2 * c, -1, -1):
    s[i] = max(s[i + 1], b[i + c])

minc = 7548975698756987

for i in range(n - c + 1):
    minc = min(minc, max(p[i], s[i]))

print(minc)