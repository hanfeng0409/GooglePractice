import numpy as np
import os
from itertools import combinations

cases_num = 0
n = 0
num_of_one_case = []
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



def cal(arr):
    # return ((arr[0]*arr[1])==arr[2]) | ((arr[0]*arr[2])==arr[1]) | ((arr[2]*arr[1])==arr[0])
    return np.sum(
        ((arr[:,0]*arr[:,1])==arr[:,2]) |
        ((arr[:,0]*arr[:,2])==arr[:,1]) |
        ((arr[:,2]*arr[:,1])==arr[:,0])
    )



with open(r'.\A-small-practice.out', 'w') as f:
    for sample in range(len(case_data)):
        foot_np = np.array(case_data[sample])[np.array(list(combinations(np.arange(len(case_data[sample])),3)))]
        print(sample)
        f.write('Case #' + str(int(sample+1))+ ': '+str(int(cal(foot_np)))+'\n')

