from random import *


n = randrange(7, 20)
m = randrange(4, n + 1)

print("".join([chr(randrange(ord("a"), ord("c") + 1)) for i in range(n)]))
print("".join([chr(randrange(ord("a"), ord("c") + 1)) for i in range(m)]))
