b228 = []
for i in range(8):
    a = input()
    a = a.split()
    b228.append(a[0])
    b228.append(a[1])

for i in range(0, len(b228), 2):
    fir = b228[i]
    numb = b228[i + 1] 
    numb = numb.split(".")
    print(numb[0], ",", numb[1][:2], sep='')

    
