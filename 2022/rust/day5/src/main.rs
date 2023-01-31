use std::fs;

fn main() {
    let input = parse_input();
    let mut stacks = parse_crate_stacks(&input);

    for instruction in &input[9..] {
        // parse instruction
        let split: Vec<&str> = instruction.split(" ").collect();
        let n   : u32 = split[1].parse().ok().unwrap();
        let src : usize = split[3].parse().ok().unwrap();
        let dest: usize = split[5].parse().ok().unwrap();
        for _ in 0..n {
            let temp = stacks[src-1].pop().unwrap();
            stacks[dest-1].push(temp);
        }
    }
    print!("[Part1] ");
    for stack in &stacks { print!("{}", stack.last().unwrap()); }
    println!();

    let mut stacks = parse_crate_stacks(&input);
    for instruction in &input[9..] {
        // parse instruction
        let split: Vec<&str> = instruction.split(" ").collect();
        let n   : u32 = split[1].parse().ok().unwrap();
        let src : usize = split[3].parse().ok().unwrap();
        let dest: usize = split[5].parse().ok().unwrap();

        let mut temp_stack = Vec::new();
        for _ in 0..n {
            let temp = stacks[src-1].pop().unwrap();
            temp_stack.push(temp);
        }
        while temp_stack.len() > 0 {
            let temp = temp_stack.pop().unwrap();
            stacks[dest-1].push(temp);
        }
    }
    print!("[Part2] ");
    for stack in &stacks { print!("{}", stack.last().unwrap()); }
    println!();
}


fn parse_input() -> Vec<String> {
    fs::read_to_string("input.txt")
        .expect("Failed to read input from file. Does 'input.txt' exist in root?")
        .split("\n")
        .filter(|s| s.len() > 0)
        .map(|s| s.to_string())
        .collect()
}

fn parse_crate_stacks(input: &Vec<String>) -> Vec<Vec<char>> {
    // there are 9 crate stacks, so create 9 empty vecs
    let mut stacks: Vec<Vec<char>> = Vec::new();
    for _ in 0..9 { stacks.push(Vec::new()); }

    // stack data is on first 8 lines
    let str_stacks = &input[0..8];

    // iterate backwards through lines, getting each crate
    for line in str_stacks.iter().rev() {
        // iterate through each crate char
        for i in (1..line.len()).step_by(4) {
            let c = line.chars().nth(i).unwrap();
            if c != ' ' {
                stacks[(i-1) / 4].push(c);
            }
        }
    }

    stacks
}
