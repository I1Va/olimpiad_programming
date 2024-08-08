from random import *

n, x = randrange(1, 100), randrange(1, 100)
print(n, x)
print("".join([("<>=")[randrange(3)] for i in range(n - 1)]))