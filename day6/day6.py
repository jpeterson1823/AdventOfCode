# Exit codes:
# 1: Program attempts to find the index of a tree object within a list due to the object already
#       having a defined "right" value, meaning some error has occured with either finding the
#       index of the object, the evaluation of the object in the array, or the addition of the
#       object to the array.

class Tree(object):
    def __init__(self):
        self.right = None
        self.left = None
        self.data = None
    
    def inside(self,arr):
        for tree in arr:
            if tree.data == self.data : return True
        return False

    def find_in(self, ls):
        for i in range(len(ls)):
            if self.data == ls[i].data:
                return i
        return -1
    
    def get_str(self):
        return '|-- {}\nR: {}\nL: {}\n'.format(self.data,self.right,self.left)

omap = open('day6.data')
orbits = [tuple(line.split(')')) for line in omap.read().splitlines()]

# Create tree objects
tree_list = []
total_orbits = 0
for orbit in orbits:
    obj1 = Tree()
    obj1.data = orbit[0]
    if not obj1.inside(tree_list):
        obj1.right = orbit[1]
        tree_list.append(obj1)
        total_orbits +=1
    else:
        index = obj1.find_in(tree_list)
        if index == -1 : print('Error finding obj in list.');exit(1)
        tree_list[index].left = orbit[1]
        total_orbits+=1




print('Total Orbits: {}'.format(total_orbits))