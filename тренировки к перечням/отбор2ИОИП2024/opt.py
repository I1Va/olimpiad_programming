def equal(a, b):
    return a == b

s = input()
t = input()
n = len(s)
prefix_string = ""
j = 0
count = 0
for i in range(n):
    if equal(s[i], t[j]):
        prefix_string += s[i]
        j += 1
        if j == len(t):
            break
    else:
        if i % 2 == 1:
            count += 1
            continue
        if count == 0:
            prefix_string = prefix_string[:-1]
            j -= 1
        count += 1

# if len(prefix_string) % 2 == 0:
#     print("NO")
#     exit(0)
if t == prefix_string:
    print("YES")
else:
    print("NO")