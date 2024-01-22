#!/usr/bin/python
import os, sys
print(sys.version)
if (os.name == 'nt'):
    print("Windows")
else:
    print(os.name)

class DNARegion(object):
    """Describes the autozygousReion"""
    def __init__(self, Chromosome, StartPoint, EndPoint, Length):
        self.startPoint = int(StartPoint)
        self.endPoint = int(EndPoint)
        self.chromosome = int(Chromosome)
        self.length = int(Length)        

def FilterList(list1, list2):
    list3 = list()
    list1Place = 0
    list2Place = 0
    stopNow = False
    addThisRegion = False    

    while (stopNow == False):

        thisRegion = list1[list1Place]        
        addThisRegion = True
        endOFComparison = False

        if (list2[list2Place].chromosome == thisRegion.chromosome):
            if (list2[list2Place].startPoint > thisRegion.endPoint or thisRegion.startPoint > list2[list2Place].endPoint):
                if (list2[list2Place].startPoint > thisRegion.endPoint):
                    addThisRegion = False
                    list1Place += 1
                elif (thisRegion.startPoint > list2[list2Place].endPoint):
                    addThisRegion = False
                    list2Place += 1
            else:
                if (thisRegion.startPoint < list2[list2Place].startPoint):
                    thisRegion.startPoint = list2[list2Place].startPoint
                if (thisRegion.endPoint > list2[list2Place].endPoint):
                    thisRegion.endPoint = list2[list2Place].endPoint

        elif (list2[list2Place].chromosome < thisRegion.chromosome):
            list2Place += 1
            addThisRegion = False
        elif (list2[list2Place].chromosome > thisRegion.chromosome):
            list1Place += 1
            addThisRegion = False
       

        if (addThisRegion == True):
            list3.append(thisRegion)
            if (thisRegion.endPoint == list1[list1Place].endPoint):
                list1Place += 1
            else:
                list2Place += 1
            thisRegion = None

        if (list1Place >= len(list1) or list2Place >= len(list2)):
            stopNow = True

    return list3

path = sys.argv[1] 
if (path.endswith("/") == False):
	path = path + "/"

dirs = os.listdir(path)
sorted(dirs)

listOfRegions = list()
commonRegions = list()

for f in dirs:
    if f.endswith(".txt"):
        file = open(path + f, "r")
        for x in file:
            items = x.split("\t")
            if (len(items) == 4):
                if not (items[0].startswith('C') and len(items) == 4):
                    if (items[3].endswith('\n')):
                        items[3] = items[3][0:len(items[3]) - 1]
                    dnaregion = DNARegion(items[0], items[1], items[2], items[3])
                    listOfRegions.append(dnaregion)
        file.close()
        if (len(listOfRegions) > 0):
            if len(commonRegions):
                commonRegions = FilterList(commonRegions, listOfRegions)
            else:
                commonRegions = listOfRegions[:]
                del listOfRegions[:]

for x in commonRegions:
    print(str(x.chromosome) + '\t' + str(x.startPoint) + '\t' + str(x.endPoint) + '\t' + str(x.endPoint - x.startPoint))
