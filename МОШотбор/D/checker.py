data = []
with open("d2a.txt", "r") as f:
    for i in range(14):
        data.append(list(map(int, f.readline().split())))

score = 0
with open("d2.txt", "r") as f:
    t = int(f.readline())
    state = True
    for ti in range(t):
        n, m, k = map(int, f.readline().split())
        colors = [set() for i in range(n)]
        for i in range(m):
            u, v = map(int, f.readline().split())
            u -= 1
            v -= 1
            if (data[ti][i] in colors[u] or data[ti][i] in colors[v]):
                state = False
            colors[u].add(data[ti][i])
            colors[v].add(data[ti][i])
        if state:
            score += 5
print(f"score: {score}")