file_lines = open('input.txt').readlines()
def origin_md(point) : return abs(0-point['x'])+abs(0-point['y'])
def compare_coord(coord1, coord2):
    if coord1['x'] == coord2['x']:
        if coord1['y'] == coord2['y']:
            return True
    else: return False

wire1i = file_lines[0].split(',')
wire2i = file_lines[1].split(',')

# Create coordinates from list of directions
# and log line points
wire1x, wire1y, wire2x, wire2y = 0, 0, 0, 0
wire1coords = []
wire2coords = []
for i in wire1i:
    if i[0] == 'R' : wire1x += int(i[1:])
    elif i[0] == 'L' : wire1x -= int(i[1:])
    elif i[0] == 'U' : wire1y += int(i[1:])
    else : wire1y -= int(i[1:])
    coord = {'x':wire1x, 'y':wire1y}
    wire1coords.append(coord)

for i in wire2i:
    if i[0] == 'R' : wire2x += int(i[1:])
    elif i[0] == 'L' : wire2x -= int(i[1:])
    elif i[0] == 'U' : wire2y += int(i[1:])
    else : wire2y -= int(i[1:])
    coord = {'x':wire2x,'y':wire2y}
    wire2coords.append(coord)
i = 1
for i in range(len(wire1coords)):
    coord1 = wire1coords[i-1]
    coord2 = wire1coords[i]
    if coord1['x'] != coord2['x']:
        diff = abs(coord1['x'] - coord2['x'])
        minx = min(coord1['x'], coord2['x'])
        y = coord1['y']
        for j in range(1,diff):
            wire1coords.append({'x':minx+j,'y':y})
    else:
        diff = abs(coord1['y'] - coord2['y'])
        miny = min(coord1['y'], coord2['y'])
        x = coord1['x']
        for j in range(1,diff):
            wire1coords.append({'x':x,'y':miny+j})
for i in range(len(wire2coords)):
    coord1 = wire2coords[i-1]
    coord2 = wire2coords[i]
    if coord1['x'] != coord2['x']:
        diff = abs(coord1['x'] - coord2['x'])
        minx = min(coord1['x'], coord2['x'])
        y = coord1['y']
        for j in range(1,diff):
            wire2coords.append({'x':minx+j,'y':y})
    else:
        diff = abs(coord1['y'] - coord2['y'])
        miny = min(coord1['y'], coord2['y'])
        x = coord1['x']
        for j in range(1,diff):
            wire2coords.append({'x':x,'y':miny+j})

intersects = []
num = 0
print('# of Coords for Wire1: {}'.format(len(wire1coords)))
print('# of Coords for Wire2: {}'.format(len(wire2coords)))

for coord in wire1coords:
    if coord in wire2coords:
        intersects.append(coord)
    else:
        if num%1000 == 0 and num != 0:
            print(num)
        num+=1

print('Intersection Points: {}'.format(len(intersects)))

dist = origin_md(intersects[0])
coord
for i in intersects:
    if dist > origin_md(i):
        dist = origin_md(i)
        coord = i

print('Closest Distance to origin: {}\nCoord: {}'.format(dist,coord))