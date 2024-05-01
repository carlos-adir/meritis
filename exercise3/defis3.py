
import numpy as np

from tqdm import tqdm

def read_file(filepath):
    values = []
    with open(filepath, "r") as file:
        while True:
            line = file.readline()
            if not line:
                break
            _, a, b = map(int, line.split(","))
            values.append((a, b))
    return values


filepath = "input/data.txt"
intervals = read_file(filepath)

intervals = tuple(sorted(intervals))
intervals = np.array(intervals, dtype="int64")


times = set(intervals[:, 0]) | set(intervals[:, 1])
times = tuple(sorted(times))
print("number of intervals: ", len(times))
# print(times)
nbiters = len(intervals)
maxval = 0
i = 0
j = 1
for a, b in zip(times, times[1:]):
    while j < nbiters and intervals[j, 0] < b:
        j += 1
    while i < j and intervals[i, 1] < a:
        i += 1
    soma = sum((intervals[i:j, 0] <= a) * (b <= intervals[i:j, 1]))
    maxval = max(soma, maxval)

print("max val = ", maxval)



