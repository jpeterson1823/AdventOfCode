def get_intcode():
    file = open("day5.data")
    intcode = []
    for num in file.read().split(','):
        intcode.append(int(num))
    file.close()
    return intcode

def read_code(intcode):
    pos = 0
    while intcode[pos] != 99:
        inst = str(intcode[pos])

        while len(inst) != 5:
            inst = '0'+inst

        op_code = inst[3:]
        c = int(inst[2])
        b = int(inst[1])
        a = int(inst[0])
        
        if op_code == '99':
            exit()
        elif op_code == '03':
            intcode[intcode[pos+1]] = input('Input: ')
            pos+=2
        elif op_code == '04':
            print(intcode[intcode[pos+1]])
            pos+=2
        else:
            val1 = intcode[intcode[pos+1]] if c == 0 else intcode[pos+1]
            val2 = intcode[intcode[pos+2]] if b == 0 else intcode[pos+2]
            store_val = intcode[pos+3] if a == 0 else intcode[intcode[pos+3]]
            
            if op_code == '05':
                if val1 != 0:
                    pos = val2
                else : pos+=3

            elif op_code == '06':
                if val1 == 0:
                    pos = val2
                else : pos+=3
            else:
                if op_code == '01':
                    intcode[store_val] = val1 + val2
                elif op_code == '02':
                    intcode[store_val] = val1*val2
                elif op_code == '07':
                    intcode[store_val] = 1 if val1 < val2 else 0
                elif op_code == '08':
                    intcode[store_val] = 1 if val1 == val2 else 0
                else : print('Unknown Op_Code at pos {}.'.format(pos))
                pos+=4
                
def main():
    read_code(get_intcode())

if __name__ == "__main__":
    main()