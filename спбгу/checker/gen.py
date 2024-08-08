from random import *

n = 100
s = "".join([["0", "1"][randrange(2)] for i in range(n)])
print(s)