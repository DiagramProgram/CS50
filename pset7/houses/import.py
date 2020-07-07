from sys import argv, exit
import csv
from cs50 import SQL

if len(argv) != 2:
    print("Incorrect Usage")
    exit(1)

db = SQL("sqlite:///students.db")


first = ''
mid = ''
last = ''
house = ''
birth = ''

with open(argv[1], mode="r") as csvfile:
    #reader = csv.DictReader(csvfile)
    reader = csv.reader(csvfile)


    itercars = iter(reader)
    next(itercars)

    for row in itercars:
        i = 0
        name = row[i].split()
        if len(name) == 2:
            first = name[0]
            mid = None
            last = name[1]
        elif len(name) == 3:
            first = name[0]
            mid = name[1]
            last = name[2]
        house = row[i+1]
        birth = row[i+2]

        rows = db.execute("INSERT INTO students ('first', 'middle', 'last', 'house', 'birth') VALUES (?, ?, ?, ?, ?)",
                   first, mid, last, house, birth)
        i += 1


#print(names)

#mydict = dict.fromkeys(dod, 0)
#print(mydict)

#print(people[0])