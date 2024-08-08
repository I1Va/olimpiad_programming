from random import randrange

n = randrange(6)
print(n)
print("".join([["0", "1"][randrange(2)] for i in range(n)]))
print("".join([["0", "1"][randrange(2)] for i in range(n)]))