'''
A few key facts about the password:

    It is a six-digit number.
    The value is within the range given in your puzzle input.
    Two adjacent digits are the same (like 22 in 122345).
    Going from left to right, the digits never decrease; they only ever increase or stay the same (like 111123 or 135679).
'''     
def adj(num):
    while num >= 10:
        if num%10 == (num/10)%10 : return True
        else : num/=10
    return False   

def is_viable(num):
    if adj(num):
        num_split = [int(part) for part in list(str(num))]
        for i in range(1,len(num_split)):
            if num_split[i-1] > num_split[i]:
                return False
        return True
    else : return False

minimum,maximum = 134564,585159
#minimum,maximum = 100000,122222
passwds = [num for num in range(minimum,maximum) if is_viable(num)]
print('# of Passwords: {}'.format(len(passwds)))