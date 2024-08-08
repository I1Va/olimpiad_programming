def get():
    global mes, path
    buf = ""
    for x in mes:
        buf += x
        if buf in path:
            print(path[buf], end = "")
            buf = ""
    if buf in path:
        print(path[buf], end = "")
        buf = ""
    print()

def rec(s, cur):
    global path, tc, data
    if not len(s):
        return
    if not (s[0] == "(" and s[-1] == ")"):
        # s - лист
        path[cur] = s
        return
    else:
        s = s[1:-1]
        cnt = 0
        idx = -1
        for i in range(len(s)):
            if s[i] == "(":
                cnt += 1
            elif s[i] == ")":
                cnt -= 1
            elif s[i] == "," and cnt == 0:
                idx = i
        # if not len(s[:idx]):
        #     print(tc)
        rec(s[:idx], cur + "0")
        if len(s[idx + 1:]):
            rec(s[idx + 1:], cur + "1")

n = int(input())
for tc in range(n):
    path = {}
    data = input()
    rec(data, "")
    mes = input()
    get()
   