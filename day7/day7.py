class Amplifier:
    def __init__(self,phase,signal,intcode):
        self.input_count = 0
        self.phase = phase
        self.signal = signal
        self.value = self.read_code(intcode)

    def get_input(self):
            self.input_count+=1
            if self.input_count == 1:
                return self.phase
            else: return self.signal

    def read_code(self,intcode):
        pos = 0
        while intcode[pos] != 99:
            #print(pos)
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
                intcode[intcode[pos+1]] = self.get_input()
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
                        #print('05 change')
                    else : pos+=3

                elif op_code == '06':
                    if val1 == 0:
                        pos = val2
                        #print('06 change')
                    else : pos+=3
                else:
                    if op_code == '01':
                        #print('add')
                        intcode[store_val] = val1 + val2
                    elif op_code == '02':
                        #print('mult')
                        intcode[store_val] = val1*val2
                    elif op_code == '07':
                        #print('less')
                        intcode[store_val] = 1 if val1 < val2 else 0
                    elif op_code == '08':
                        #print('eq')
                        intcode[store_val] = 1 if val1 == val2 else 0
                    else : print('Unknown Op_Code at pos {}.'.format(pos))
                    pos+=4
            #print(intcode)
            

def get_intcode():
    file = open("test.data")
    intcode = []
    for num in file.read().split(',') : intcode.append(int(num))
    file.close()
    return intcode

def main():
    intcode = get_intcode()
    amps = []
    phases = [4,3,2,1,0]
    for i in range(5):
        if i == 0:
            amps.append(Amplifier(phases[i],0,intcode))
        else:
            amps.append(Amplifier(phases[i],amps[len(amps)-1].value,intcode))
    
    print("Thruster: %i" % amps[len(amps)-1].value)


if __name__ == "__main__":
    main()