time = 0
cur = 0
q = []

for i in range(9 * 15 + 1):
    q.append(3)
    if time % 15 == 0:
        time = 0
        q.append(q[cur])
    time += 1
c = 0
s = []
ans = 2
for i in range(30):
    s.append(q.pop(0))
while len(q):
    cur = q.pop(0)
    ans += 1
    if cur == 3:
        c += 1
    else:
        s.append(cur)
    if (c == 50):
        s.append(3)
        c = 0

while len(s):
    cur = q.pop(0)
    ans += 3
    if cur == 1:
        ans += 1
    if cur == 2:
        ans += 12
        
        
    
    