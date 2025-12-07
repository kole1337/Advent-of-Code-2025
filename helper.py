def readFile():
    arr = []
    with open('example.txt', 'r') as file:
        for line in file:
            arr.append(line.strip())
        # for i in range(len(arr)):
            # print(arr[i])
    # print(len(arr))
    return arr

# arr1 = readFile()
# for i in range(len(arr1)):
#             print(arr1[i])