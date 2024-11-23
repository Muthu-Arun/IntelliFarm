import csv

datafile = open("../dataSets/Guntur_weather_data.csv", "r")
processedInput = open("../dataSets/processedInput.csv", "w")
processedInput = open("../dataSets/processedInput.csv", "w")
processedTarget = open("../dataSets/processedTarget.csv", "w")

reader = csv.reader(datafile)
inpwriter = csv.writer(processedInput)
tarwriter = csv.writer(processedTarget)
inputdata: list = []
targetdata: list = []


def write():
    inpwriter.writerows(inputdata)
    tarwriter.writerows(targetdata)
    inputdata.clear()
    targetdata.clear()


def load():
    count: int = 0
    for row in reader:
        count += 1
        if count <= 1000:
            inputdata.append([row[0], row[1], row[2], row[4]])
            targetdata.append([row[3]])
        else:
            count = 0
            write()


write()
load()
