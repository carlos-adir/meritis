filepath = "input/data.txt"

dicts = {}
with open(filepath, "r") as file:
    while True:
        line = file.readline()
        if not line:
            break
        line = line.strip("\r\n")
        _, pays, time = line.split(",")
        time = int(time)
        if pays not in dicts:
            dicts[pays] = []
        dicts[pays].append(time)

min_pays = ""
minimal_sum = float("inf")
for pays, times in dicts.items():
    if sum(times) < minimal_sum:
        minimal_sum = sum(times)
        min_pays = pays

print(min_pays)
