n = 30

months = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]

def tr_opt(a):
    a = list(map(int, a.split(".")))
    cur = a[0] + sum(months[:(a[1] - 1)]) + (a[2] % 4 == 0 and a[1] > 2) + a[2] * 365 + a[2] // 4
    # print(a, a[0], sum(months[:(a[1] - 1)]), (a[2] % 2024 == 0 and a[1] < 2))
    return cur

def tr_brut(a, b):
    a = list(map(int, a.split(".")))
    b = list(map(int, b.split(".")))
    a[0] -= 1
    b[0] -= 1
    a[1] -= 1
    b[1] -= 1
    res = 0
    day = a[0]
    month = a[1]
    year = a[2]
    while not(day == b[0] and month == b[1] and year == b[2]):
        #print(day, month, year)
        day += 1
        res += 1
        if (day == months[month] + int(month == 1 and year % 4 == 0)):
            month += 1
            day = 0
        if (month == 12):
            month = 0
            year += 1
    return res
def solve():

    for _ in range(n):
        s = input().split()
        a, b = s[0], s[1]
        #print(tr(b) - tr(a))
        print(tr_brut(a, b))

solve()