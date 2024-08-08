
t = int(input())


def create(f):
    global resources, recipes
    state = True
    mn = 10**9
    for w in recipes[f]:
        if resources[w[0] - 1] - w[1] < 0:
            state = False
            mn = min(mn, w[0])
    if not state:
        print(f"FAIL: missing {mn}")
    else:
        for w in recipes[f]:
            resources[w[0] - 1] -= w[1]
        print("OK")
    
for _ in range(t):
    A, E, n = map(int, input().split())
    e = list(map(int, input().split()))
    x = list(map(int, input().split()))
    work = [False] * n 
    m = int(input())
    recipes = [[] for i in range(m)]
    for i in range(m):
        k = int(input())
        for j in range(k):
            s = list(map(int, input().split()))
            recipes[i].append(s)
    q = int(input())
    balance = A
    prev = 0
    resources = [0] * n
    for _ in range(q):
        # print(balance, resources)
        action = input().split()
        step = int(action[1])
        # Текущий ход: step
        for __ in range(step - prev):
            for i in range(n):
                if not work[i]:
                    continue
                if balance - e[i] < 0:
                    continue
                balance -= e[i]
                resources[i] += x[i]
            balance += E
        prev = step
        
        f = int(action[3])
        typ = action[4]
        if typ == "ON":
            work[f - 1] = True
        elif typ == "OFF":
            work[f - 1] = False
        else:
            create(f - 1)

