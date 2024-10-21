import csv

file : str= "./../dataSets/crop_production.csv"
opfile : str= "./../dataSets/tempinput.csv"
tarfile : str = "./../dataSets/temptarget.csv"
data :list = []
fh = open(file, "r",newline="")
opfh = open (opfile,"w",newline="")
tarfh = open (tarfile,"w",newline="")
reader = csv.reader(fh)
writer = csv.writer(opfh)
tarwriter = csv.writer(tarfh)
cropid : dict ={}
cid : int = 1
prodData : list = []
def writeData():
    # pass
    if data:
        writer.writerows(data)
        tarwriter.writerows(prodData)
        data.clear()
        prodData.clear()

def processData():
    global cid
    for i in range(len(data)):

        prodData.append([data[i][-1]])
        data[i] = data[i][-3:-1]
        if data[i][0] not in cropid:
            cropid[data[i][0]] = cid
            cid += 1
        data[i][0] = cropid[data[i][0]]
        # print(i)
    
    writeData()

count :int = 0
for i in reader:
    data.append(i)
    count += 1
    if(count >= 3000):
        processData()
        count = 0
        break
processData()