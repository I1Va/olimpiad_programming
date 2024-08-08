
def simp(x):
    c = 0
    for i in range(1, x + 1):
        if x % i == 0:
            c += 1
    return c == 2

def sq(x):
    return int(x ** 0.5) ** 2 == x


sz = 100
sieve = [True] * sz
a = [i for i in range(1, sz)]

b = []
for x in a:
    if not simp(x) and not sq(x):
        b.append(x)
print(b)