from collections import deque
a = int(input())
n = 0
w = {}
cost = {}
flag = False
pred1, pred2, pred3 = False, False, False
for i in range(a):
    current1, current2, current3 = [True if zn == '.' else False for zn in input()]
    if flag:
        if pred1:
            if current1:
                w[n] = w.get(n, []) + [n + 3]
                cost[n] = cost.get(n, []) + [0]
            if pred2:
                w[n] = w.get(n, []) + [n + 1]
                cost[n] = cost.get(n, []) + [1]
        if pred2:
            if current2:
                w[n + 1] = w.get(n + 1, []) + [n + 1 + 3]
                cost[n + 1] = cost.get(n + 1, []) + [0]
            if pred1:
                w[n + 1] = w.get(n + 1, []) + [n]
                cost[n + 1] = cost.get(n + 1, []) + [1]
            if pred3:
                w[n + 1] = w.get(n + 1, []) + [n + 2]
                cost[n + 1] = cost.get(n + 1, []) + [1]
        if pred3:
            if current3:
                w[n + 2] = w.get(n + 2, []) + [n + 2 + 3]
                cost[n + 2] = cost.get(n + 2, []) + [0]
            if pred2:
                w[n + 2] = w.get(n + 2, []) + [n + 1]
                cost[n + 2] = cost.get(n + 2, []) + [1]         
        n += 3
    pred1, pred2, pred3 = current1, current2, current3
    flag = True

ans = []
begins = [0, 1, 2]
def bfs(start):
    dist = [-1] * (a * 3)
    prices = [-1] * (a * 3)
    prices[start] = 0
    dist[start] = 0
    queue = deque([start])
    if start in w.keys():
        while queue:
            u = queue.pop()
            if u in w.keys():
                for v in w[u]:
                    if dist[v] == -1:
                        dist[v] = dist[u] + 1
                        prices[v] = prices[u] + cost[u][w[u].index(v)]
                        queue.appendleft(v)
    pox = [prices[-1], prices[-2], prices[-3]]
    if prices[-1] >= 0 or prices[-2] >= 0 or prices[-3] >= 0:
        ans.append(min(x for x in prices[-1:-4:-1] if x >= 0))
    else:
        ans.append(10**4)
bfs(0)
bfs(1)
bfs(2)


if min(ans) == 10**4:
    print(-1)
else:
    print(ans.index(min(ans)) + 1)
    print(min(ans))
