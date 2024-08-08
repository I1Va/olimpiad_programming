from random import *

n = randrange(1, 150)
alp = [chr(i) for i in range(ord("A"), ord("E") + 1)]
sz = len(alp)
print(n)
words = ["".join([alp[randrange(sz)] for i in range(3)]) for i in range(6)]

for i in range(n):
    print(words[randrange(6)], words[randrange(6)])