from random import *
l = 0
n = randrange(10, 20)
print(n)
for i in range(n):
    t = ["+", "?"][randrange(2)]
    if l == 0:
        t = "+"
    if t == "+":
        print("+", randrange(0, l + 1), randrange(1, 5))
        l += 1
    else:
        left = randrange(1, l + 1)
        right = randrange(left, l + 1)
        print("?", left, right)