from helper import readFile



# for i in range(len(arr)):
#     print(arr[i])

def p1():
    res = 0
    sum = 50
    to_add = 0
    added = False
    arr = []
    arr = readFile()
    for i in range(len(arr)):
        print("===")

        rot = arr[i][0]

        if rot == "L":
            to_add -= int(arr[i][1:])
            # print(f"Turn left! {to_add}")
        else:
            to_add += int(arr[i][1:])
            # print(f"turn right! {to_add}")
        
        sum += to_add
        print(f"to add: {to_add}")
        print(f"sum after adding: {sum}")

        while  sum > 99:
            
            # print(f"Sum is over 99: {sum}")
            if not added:
                sum = sum-100
                res+=1
                addded = True

            # print(f"Normalise: {sum}")
            print("pass by zero!")
            

        while sum<0:
            # print(f"Sum is under 99: {sum}")
            if not added:
                res+=1
                sum = 100+sum    
                addded = True
            # print(f"Normalise: {sum}")
            print("pass by zero!")

            
        print(f"sum after normalising: {sum}")


        if sum==0 and added:
            # print(f"Sum is zero: {sum}")
            print("pass is zero!")

            res += 1

        to_add = 0
        addded = False

    print(f"Total zeros: {res}")
    print("===")
    return res


# print(p1())
p1()