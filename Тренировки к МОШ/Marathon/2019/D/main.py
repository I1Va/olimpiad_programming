ans = []
for i in range(1, 9 + 1):
    print(f"L {i} {i} 10")
    print(f"L {10 - i} {i} 20")

for i in range(11, 20):
    print(f"L {i - 10} {i} 20")
    print(f"L {20 - i} {i} 10")

print(len(ans))
for x in ans:
    print(x)