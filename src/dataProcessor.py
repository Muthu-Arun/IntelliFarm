import csv
cities = {}
crops = {}
seasons = {}
fh = open("./../dataSets/filtered.csv","r")
reader = csv.reader(fh)
wfile = open("./../dataSets/processed.csv","w")
idCities = 0
idCrops = 0
idSeasons = 0
for i in reader:
    if i[8] == "" or i[9] == "0.0":
        continue
    print(i)
    if i[1] not in cities:
        cities[i[1]] = idCities
        idCities += 1
    if i[2] not in crops:
        crops[i[2]] = idCrops
        idCrops += 1
    if i[4] not in seasons:
        seasons[i[4]] = idSeasons
        idSeasons +=1
print(cities)
print(crops)
print(seasons)

writer = csv.writer(wfile)
row = []
fh.seek(0,0)
reader = csv.reader(fh)
for i in reader:
    if i[9] == "0.0":
        continue
    row.append(cities[i[1]])
    row.append(crops[i[2]])
    row.append(seasons[i[4]])
    row.append(i[5])
    row.append(i[7])
    # row.append(i[9])
    # data.append(row)
    writer.writerow(row)
    row.clear()

# print("Written ",len(data), "rows ")
# print(data)
wfile.close()
fh.close()