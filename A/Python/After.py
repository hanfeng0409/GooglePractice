cases_num = 0
num_of_one_case = []
n=0
case_data = []
with open(r'..\data\A-small-practice.in', 'r') as f:
    data = f.readlines()  # txt中所有字符串读入data
    for line in data:
        linedata = line.split()
        numbers_float = list(map(float, linedata))
        if n==0:
            cases_num = int(numbers_float[0])
        if n>0 and n%2==0:
            case_data.append(numbers_float)
        if n > 0 and n % 2 != 0:
            num_of_one_case.append(int(numbers_float[0]))
        n += 1

with open(r'.\A-small-practice.out', 'w') as f:
    for sample in range(len(case_data)):
        a,b = 0,1
        ans = 0
        arr_sorted = sorted(case_data[sample])
        d = {}
        for a in range(num_of_one_case[sample]-1,-1,-1):
            for b in range(a - 1, -1, -1):
                z = arr_sorted[a] * arr_sorted[b]
                if z!= 0:
                    if z in d.keys():
                        ans = ans + d[int(z)]
                else:
                    ans = ans + b
            if arr_sorted[a] in d.keys():
                d[int(arr_sorted[a])] = d[int(arr_sorted[a])]+1
            else:
                d[int(arr_sorted[a])]=1

        print(sample,ans)
        f.write('Case #%d: %d\n' %(int(sample+1),int(ans)))

