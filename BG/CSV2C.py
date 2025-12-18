#!/usr/bin/python3

import csv
import os
import sys

script_dir = os.path.dirname(os.path.abspath(__file__))

filename = os.path.join(script_dir, "test.csv")
newname = os.path.join(script_dir, "test.c")
newname2 = "test"

try:
    with open(filename, 'r') as oldfile:
        reader = csv.reader(oldfile)
        your_list = list(reader)
except FileNotFoundError:
    print(f"Error: The file {filename} was not found.")
    sys.exit(1)

with open(newname, 'w') as newfile:  
    newfile.write("const unsigned char " + newname2 + "[]={\n")

    rows = len(your_list)
    columns = len(your_list[0])

    for i in range(rows):
        for j in range(columns):
            newfile.write(your_list[i][j] + ",")
        newfile.write("\n")

    z = newfile.tell()
    z = z - 3
    newfile.seek(z)

    newfile.write("\n};\n\n")

print("완료")
