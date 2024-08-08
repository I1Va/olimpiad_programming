from random import *

while (1):
    a = randrange(1, 100)
    b = randrange(a + 1, 110)
    c = randrange(2, 100)
    if (a % c == 0 or b % c == 0):
        continue
    print(a, b, c)
    exit(0)
