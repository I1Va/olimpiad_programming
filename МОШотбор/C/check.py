
data = []
with open("c2ans.txt", "r") as f:
    for i in range(7):
        n = int(f.readline())
        d = list(map(int, f.readline().split()))
        data.append(d)

print(len(data))
with open("c2.txt", "r") as f:
    tc = int(f.readline())
    for i in range(tc):
        n = int(f.readline())
        a = list(map(int, f.readline().split()))
        b = list(map(int, f.readline().split()))
        resa = 0
        resb = 0
        for x in data[i]:
            resa += a[x - 1]
            resb += b[x - 1]
        if resa == resb:
            print(f"{i}: OK ({resa})")

