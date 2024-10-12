import csv

file  = open("./dataSets/output_data.csv","r")
opfile = open("./dataSets/target.csv","w")

reader = csv.reader(file)
writer = csv.writer(opfile)
prodidx = 7
for i in reader:
    print(i)
    # break
    writer.writerow([i[prodidx]])
