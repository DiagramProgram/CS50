#num = input("Number: ")

nums = list(map(int, input("Number: ")))

copy = nums.copy()

sum = 0
seclist = [] #temporary

if len(nums) %2 == 0:
    i = 0
    while i < len(nums):
        seclist.append(nums[i]*2)
        nums.pop(i)
        i += 1
else:
    i = 1
    while i < len(nums):
        seclist.append(nums[i]*2)
        nums.pop(i)
        i += 1

for each in seclist:
    if each > 9:
        sum += 1
        sum += each-10
    else:
        sum += each

for each in nums:
    sum += each

#print(sum)

#print(seclist)

#print(copy)

#print(copy[0])
#print(copy[2])

if (sum % 10 != 0):
    print("INVALID")
elif ((copy[0] == 3 and (copy[1] == 4 or copy[1] == 7)) and len(copy) == 15):
    print("AMEX")
elif ((copy[0] == 5 and (copy[1] >= 1 and copy[1] <= 5)) and len(copy) == 16):
    print("MASTERCARD")
elif (copy[0] == 4 and (len(copy) == 13 or len(copy) == 16)):
    print("VISA")

