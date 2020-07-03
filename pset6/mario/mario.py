x = input("Height: ")

while not x.isdigit():
    x = input("Height: ")

x = int(x)

while (x < 1 or x > 8):
    x = input("Height: ")
    x = int(x)


p = x-1
s = 1
for i in range(x):
    print(" " * p, end="")
    print("#" *s, end="")
    print("  ", end="")
    print("#"*s)
    p -= 1
    s += 1