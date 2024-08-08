from datetime import datetime
    

n = 70

def get(a, b):
    a = list(map(int, a.split(".")))
    b = list(map(int, b.split(".")))
    some_date = datetime(a[2], a[1], a[0])
    now_date = datetime(b[2], b[1], b[0])  
    d = now_date - some_date
    return d.days
 
for _ in range(n):
    s = input().split()
    a, b = s[0], s[1]
    print(get(a, b))