import csv
cities = {}
crops = {}
seasons = {}
fh = open("./../dataSets/filtered.csv","r")
reader = csv.reader(fh)
wfile = open("./../dataSets/processed.csv","w")