from random import randrange
n = randrange(300, 1000)
a = [['.' for j in range(n)] for i in range(n)]

i = randrange(n)
j = randrange(n)

for c in range(100):
    i = randrange(2, n - 2)
    j = randrange(2, n - 2)
    a[i][j] = 'I'
    a[i - 1][j] = a[i - 1][j - 1] = a[i - 1][j + 1] = a[i][j - 1] = a[i][j + 1] = 'B'
a[i][j] = 'X'
print(n, n)
for x in a:
    print("".join(x))