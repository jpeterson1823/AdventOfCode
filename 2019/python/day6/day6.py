planets = {}
for line in open('day6.data').readlines():
    a,b = line.strip().split(')')
    if a not in planets:
        planets[a] = []
    planets[a].append(b)


def get_orbits(planet):
    ans = 0
    for y in planets.get(planet, []):
        ans += get_orbits(y)
        ans += 1
    return ans

def get_path(start):
    you = []
    for planet in planets.keys():
        if start in planets.get(planet):
            you.append(planet)
            for p in get_path(planet):
                you.append(p)
    return you




totalOrbits = 0
for planet in planets:
    totalOrbits += get_orbits(planet)

you_path = get_path('YOU')
san_path = get_path('SAN')

remove = [i for i in you_path if i in san_path]

temp = [i for i in you_path if i not in remove]
you_path = temp
temp = [i for i in san_path if i not in remove]
san_path = temp

transfers = len(you_path) + len(san_path)
print("Total Orbits: {}\nOrbital Transfers: {}".format(totalOrbits, transfers))
#506