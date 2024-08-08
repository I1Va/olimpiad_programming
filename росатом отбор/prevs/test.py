from random import randrange
n = 200
a = [['.' for j in range(n)] for i in range(n)]

i = randrange(n)
j = randrange(n)
a[i][j] = 'X'
for c in range(100):
    i = randrange(10, n - 10)
    j = randrange(10, n - 1)
    a[i][j] = 'I'
    a[i - 1][j] = a[i - 1][j - 1] = a[i - 1][j + 1] = a[i][j - 1] = a[i][j + 1] = 'B'

print(n, n)
for x in a:
    print("".join(x))