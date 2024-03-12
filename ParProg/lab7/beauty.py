import sys

filename = sys.argv[1] 
file = open(filename, "r")
data = file.readlines()

fat = len(str(len(data) + 1))

for i in range(len(data)):
    print(str(i + 1), ". ", " " * (fat - len(str(i + 1))), data[i], end='', sep='')

