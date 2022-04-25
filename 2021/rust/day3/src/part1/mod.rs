const BITWIDTH: usize = 12;

pub fn run(input: &Vec<String>) {
    // create epsilon and gama vars
    let mut epsilon = 0u128;
    let mut gamma   = 0u128;

    // count number of zeros and ones for each line
    let mut n0: [u16; BITWIDTH] = [0u16; BITWIDTH];
    let mut n1: [u16; BITWIDTH] = [0u16; BITWIDTH];
    for line in input {
        for bit in 0..BITWIDTH {
            if line.chars().nth(bit).unwrap() == '0' {
                n0[bit] += 1;
            } else {
                n1[bit] += 1;
            }
        }
    }

    // calc gamma and epsilon rates
    for bit in 0..BITWIDTH {
        gamma <<= 1;
        epsilon <<= 1;
        if n0[bit] > n1[bit] {
            gamma += 1;
        } else {
            epsilon += 1;
        }
    }

    println!("Part 1) Power Rating: {}", gamma*epsilon);
}

