def main():
    intcode = get_intcode()
    print('Value: %i' % read_code(get_intcode()))

    for a1 in range(99):
        for a2 in range(99):
            intcode[1] = a1
            intcode[2] = a2
            if read_code(intcode) == 19690720:
                print('Noun: {}\nVerb: {}\nAnswer: {}'.format(a1,a2,100*a1+a2))
                exit()
            else : intcode = get_intcode()
    print('Could not find value to match 19690720.')

# Reads Intcode
def read_code(code):
    pos = 0
    while code[pos] != 99:
        #Do Stuff Here
        if code[pos] == 1:
            code[code[pos+3]] = code[code[pos+1]]+code[code[pos+2]]
        elif code[pos] == 2:
            code[code[pos+3]] = code[code[pos+1]]*code[code[pos+2]]
        elif code[pos] == 3:
            code[code[pos+1]] = input("Enter a number: ")
        elif code[pos] == 4:
            print('Output: %i'%code[code[pos+1]])
        else : print('Error while reading: index=%i' % pos)

        pos += 4
    return code[0]

def get_intcode():
    file = open("input.txt")
    intcode = []
    for num in file.read().split(',') : intcode.append(int(num))
    file.close()
    return intcode

if __name__ == "__main__":
    main()