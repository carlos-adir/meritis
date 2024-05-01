
input_filepath = "input/data.txt"
output_filepath = "input/sorted_data.txt"
data = []
with open(input_filepath, "r") as file:
    for line in file:
        line = line.strip("\r\n")
        numbers = tuple(map(int, line.split(",")))
        data.append(numbers)
    
sorter = lambda numbers: (numbers[1], numbers[2])
data = sorted(data, key=sorter)

with open(output_filepath, "w") as file:
    for numbers in data:
        line = ",".join(map(str, numbers))
        file.write(line + "\n")

    