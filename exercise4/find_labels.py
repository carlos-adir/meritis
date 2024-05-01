# This file finds the labels corresponding to the given time in a file

import numpy as np


def compute_time(team):
    total = sum(team)
    vecor = team[1:] - team[:-1]
    total += sum(v**2//100 for v in vecor)
    return total


PERTEAM = 4
input_filepath = "data4_2.txt"
solut_filepath = "output4_2.txt"

input_times = []
solut_times = []
output_indexs = []

with open(input_filepath, "r") as file:
    while True:
        line = file.readline()
        if not line:
            break
        input_times.append(int(line))
minimal_time = min(input_times)


with open(solut_filepath, "r") as file:
    while True:
        line = file.readline()
        if not line:
            break
        line = list(map(int, line.strip().split(" ")))
        for value in line:
            solut_times.append(minimal_time + value)

print(input_times)
print(solut_times)
for solut_time in solut_times:
    for j, input_time in enumerate(input_times):
        if input_time != solut_time:
            continue
        if j not in output_indexs:
            output_indexs.append(j)
            break
indexed_times = [solut_times[ind] for ind in output_indexs]
print(indexed_times)

alltimes = []
allsquares = []
NBTEAMS = len(input_times)//PERTEAM
for i in range(NBTEAMS):
    team = solut_times[PERTEAM*i:PERTEAM*(i+1)]
    team = np.array(team, dtype="int64")
    time = compute_time(team)
    alltimes.append(time)
    vecor = team[1:]-team[:-1]
    squar = sum(v**2//100 for v in vecor)
    allsquares.append(squar)
    print("Team %d: %.2f" % (i, time/100.))
    print("    " + str(team))

print("Evaluating all")
print("    Minimal time: %.2f" % (min(solut_times)/100.))
print("    Maximal time: %.2f" % (max(solut_times)/100.))
print("       Mean time: %.6f" % (np.mean(solut_times)/100))
print("Evaluating solution")
print("    Minimal time: %.2f" % (min(alltimes)/100.))
print("    Maximal time: %.2f" % (max(alltimes)/100.))
print("      Difference: %.2f" % ((max(alltimes) - min(alltimes))/100.))
print("     Mean quadra: %.6f" % (np.mean(allsquares)/100.))

output_labels = [10_000 + ind for ind in output_indexs]
line = " ".join(map(str, output_labels))
print(line)
