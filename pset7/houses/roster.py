from sys import argv, exit
import csv
from cs50 import SQL


if len(argv) != 2:
    print("Incorrect Usage")
    exit(1)

db = SQL("sqlite:///students.db")

rows = db.execute('SELECT DISTINCT * FROM students WHERE house = ? ORDER BY last, first', argv[1])

for each in rows:
    if each["middle"] == None:
        print(each['first'] + ' ' + each['last'] + ', ' + 'born ' + str(each['birth']))
    else:
        print(each['first'] + ' ' + each['middle'] + ' ' + each['last'] + ', born ' + str(each['birth']))
