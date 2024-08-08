a = int(input())
b = int(input())
c = int(input())
p = [a, b, c]
p.sort()
a, b, c = p[0], p[1], p[2]

s1 = (a + c == 2 * b)
s2 = a * c == b * b

if s1 and s2:
    print(f"B {a} {b} {c}")
elif s1:
    print(f"A {a} {b} {c}")
elif s2:
    print(f"G {a} {b} {c}")
else:
    print("No")
