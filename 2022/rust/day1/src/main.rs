use std::fs;
use std::io;

fn main() {
	// get input data from file
	let input = parse_input()
		.expect("Failed to read input from file. Does 'input.txt' exist in root?");
    part1(&input);
    part2(&input);
}

fn parse_input() -> Result<String, io::Error>{
	fs::read_to_string("input.txt")
}

fn part1(input: &String){
    let pockets = parse_elf_pockets(input);

    // find pocket with the most calories
    let mut max = 0;
    for pocket in pockets {
        let calories: i32 = pocket.iter().sum();
        if calories > max {
            max = calories;
        }
    }

    println!("[Part1] Most calories carried by elf: {}", max);
}

fn part2(input: &String) {
    let calorie_sums: Vec<i32> = parse_elf_pockets(input).iter().map(|pocket| pocket.iter().sum()).collect();
    let mut a = 0;
    let mut b = 0;
    let mut c = 0;
    for csum in calorie_sums {
        if csum > a {
            c = b;
            b = a;
            a = csum;
        }
        else if csum > b && csum != a {
            c = b;
            b = csum;
        }
        else if csum > c && csum != b {
            c = csum;
        }
    }
    println!("[Part2] Sum of top 3 calorie totals: {}", a + b + c);
}

fn parse_elf_pockets(input: &String) -> Vec<Vec<i32>> {
    let mut pockets: Vec<Vec<i32>> = Vec::new();

    // tokenize into each elf's pocket string
    let pocket_strs: Vec<&str> = input.split("\n\n").collect();
    // turn each tokenized pocket into Vec<i32> and add to `pockets`
    for pstr in pocket_strs {
        let tokenized = pstr.split("\n")
                            .filter(|token| token.len() != 0)
                            .map(|token| match token.parse::<i32>() {
                                Ok(n) => n,
                                Err(_) => {
                                    println!("Cannot convert str to i32: \"{}\"", token);
                                    println!("Invalid token found in the following input string:\n\"{}\"",pstr);
                                    panic!("Panic!");
                                }
                            })
                            .collect::<Vec<i32>>();
        pockets.push(tokenized);
    }

    return pockets;
}
