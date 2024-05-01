"""
Python script to get the minimal and maximal value of times,
and gives the quantities of entries
"""
def read_file(filepath):
    values = []
    with open(filepath, "r") as file:
        while True:
            line = file.readline()
            if not line:
                break
            _, a, b = map(int, line.split(","))
            values.append((a, b))
    return tuple(values)

filepath = "input/data.txt"
values = read_file(filepath)
minimal = min(min(a, b) for a, b in values)
maximal = max(max(a, b) for a, b in values)
print(f"minimal = {minimal}")
print(f"maximal = {maximal}")
print(f"nb entries = {len(values)}")
