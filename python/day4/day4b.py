def increasing(num):
    while num >= 10:
        if num%10 < (num/10)%10 : return False
        else : num/=10
    return True  

def is_viable(num):
    if increasing(num):
        num_split = [int(part) for part in list(str(num))]

        for i in range(2,len(num_split)):
            if num_split[i-2] > num_split[i-1]:
                return False

        groups = []
        nums = []
        for i in range(len(num_split)):
            if num_split[i] not in nums:
                temp = [num_split[i]]
                nums.append(num_split[i])
                for j in range(i+1,len(num_split)):
                    if num_split[i] == num_split[j]:
                        temp.append(num_split[j])
                    else: j = len(num_split)
                groups.append(temp)

        #print('Num: {}\nGroups: {}'.format(num, groups))
        
        for group in groups: 
            if len(group) == 2: print('Num: {}\nGroups: {}\nTrue'.format(num, groups));return True
    

minimum,maximum = 134564,585159
passwds = [num for num in range(minimum,maximum) if is_viable(num)]
print('# of Passwords: {}'.format(len(passwds)))