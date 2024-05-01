import numpy as np

problem = 1
filepath = "data4_%d.txt" % problem

def read(filepath):
    with open(filepath, "r") as file:
        while True:
            line = file.readline()
            if not line:
                break
            line = line.strip("\n\r")
            yield line

numbers = []
for line in read(filepath):
    numbers.append(int(line))

perteam = 4
nbteams = len(numbers)//perteam
numbers = np.array(numbers, dtype="int64")
numbers = numbers.reshape((nbteams, perteam))



def compute_team(time):
    vec = time[1:] - time[:-1]
    soma = sum(time)
    soma += sum((vec**2)//100)
    return soma

def compute_meantime(matrix):
    times = tuple(map(compute_team, matrix))
    return np.mean(times)

def randomize(matrix, nshuffle: int):
    m, n = matrix.shape
    for _ in range(nshuffle):
        while True:
            a0, a1 = np.random.randint(0, m, 2)
            b0, b1 = np.random.randint(0, n, 2)
            if a0 != a1 or b0 != b1:
                break
        temp = matrix[a0, b0]
        matrix[a0, b0] = matrix[a1, b1]
        matrix[a1, b1] = temp


soma = 0
ntests = 1000
for i in range(ntests):
    soma += compute_meantime(numbers)
    randomize(numbers, nbteams * perteam)
print(soma / ntests)


