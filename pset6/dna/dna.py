from sys import argv, exit
import csv

def main():
    if len(argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        exit(1)

    STRs = []
    people = []

    with open(argv[1], mode="r") as csvfile:
        reader = csv.DictReader(csvfile)
        STRs = reader.fieldnames[1:]
        for row in reader:
            people.append(row)

    mydict = dict.fromkeys(STRs, 0)

    with open(argv[2], mode="r") as file:
        sequence = file.readline()
        for STR in STRs:
            mydict[STR] = find_count(sequence, STR)

    for each in people:
        checkcount = 0
        for STR in STRs:
            if int(each[STR]) != mydict[STR]:
                continue
            checkcount += 1

        if checkcount == len(STRs):
            print(each['name'])
            exit(0)

    print("No match")
    exit(1)


def find_count(sequence, STR):
    L = len(STR)
    max = 0
    for i in range(len(sequence)):
        count = 0

        if sequence[i: i + L] == STR:
            count += 1
            while sequence[i: i + L] == sequence[i + L: i + (2 * L)]:
                count += 1
                i += L

        if count > max:
            max = count

    return max

if __name__ == "__main__":
    main()


'''
sequence = []
people = []

with open(argv[1]) as csvfile:
    myreader = csv.reader(csvfile, delimiter=',')
    line = 0
    for row in myreader:
        if line == 0:
            for each in row:
                sequence.append(each)
            #sequence.pop(0)
            line += 1
        else:
            people.append(row) #2d list

    sequence.pop(0)
    print(sequence)
    print()
    print(people)
    print()

with open(argv[2]) as file:
    data = file.read()

tata = list(data)
tata.pop(-1)

#print(tata)

maxes = []

n = 0
while n < len(sequence): #count once for each sequence
    i = 0
    if len(sequence[n]) == 5:
        count = 0
        max = 0
        while i < len(tata)-4:
            #count the max number of consecutive count for a certain sequence
            while (tata[i] == sequence[n][0] and tata[i+1] == sequence[n][1] and tata[i+2] == sequence[n][2] and tata[i+3] == sequence[n][3] and tata[i+4] == sequence[n][4]):
                count += 1
                i += 4
            if count > max:
                max = count
            i += 1
        maxes.append(max)
        #print(maxes)
    elif len(sequence[n]) == 8:
        count = 0
        max = 0
        while i < len(tata)-7:
            #count the max number of consecutive count for a certain sequence
            while (tata[i] == sequence[n][0] and tata[i+1] == sequence[n][1] and tata[i+2] == sequence[n][2] and tata[i+3] == sequence[n][3] and tata[i+4] == sequence[n][4] and tata[i+5] == sequence[n][5] and tata[i+6] == sequence[n][6] and tata[i+7] == sequence[n][7]):
                count += 1
                i += 7
            i += 1
            if count > max:
                max = count
        maxes.append(max)
    elif len(sequence[n]) == 4: #------------------------------------------------------------------------------------
        count = 0
        max = 0
        while i < len(tata)-3:
            #count the max number of consecutive count for a certain sequence
            while (tata[i] == sequence[n][0] and tata[i+1] == sequence[n][1] and tata[i+2] == sequence[n][2] and tata[i+3] == sequence[n][3]):
                count += 1
                i += 3
            i += 1
            if count > max:
                max = count
        maxes.append(max)
    n += 1

print(maxes)'''

#make something that checks this sequence with each of the other people, and if nothing matches, then print "No match"