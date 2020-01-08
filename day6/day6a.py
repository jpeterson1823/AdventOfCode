#get the list of orbits into a two-dimensional array
input1 = open("day6.data","r")
orbits = input1.read()
orbits = orbits.split("\n")
for i in range(len(orbits)):
    orbits[i] = orbits[i].split(")")
 
list1 =[]
 
for i in range(len(orbits)):
    for j in range(len(orbits[i])):
        list1.append(orbits[i][j])
 
#planets is a list of all planets, with no duplicates
planets = list(set(list1))
 
for i in range(len(planets)-1):     #delete COM from planets
    if (planets[i]=="COM"):
        del(planets[i])
 
#recursive function to find and count all direct and indirect orbits of a given planet,
#going backwards
def findOrbits(orbitArray, world, count):
    for i in orbitArray:
       
        localCount = count
        endCheck = i[0]
        worldCheck = i[1]
       
        if(worldCheck==world):
            if(endCheck!="COM"):
                localCount += 1
                returnValue = findOrbits(orbitArray,endCheck,localCount)
            else:
                localCount +=1
                returnValue = localCount
               
    return returnValue
 
#total count of all direct and indirect orbits
orbitCount = 0
 
#loop to find anc count all orbits of every planet
for z in planets:
    number = findOrbits(orbits, z, 0)
    orbitCount += number
 
#print the resulting orbit count
print("The total direct and indirect orbits is " + str(orbitCount))