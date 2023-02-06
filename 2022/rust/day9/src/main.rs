use std::fs;

mod part1;
mod part2;

fn main() {
    let instructions = parse_input();
    part1::solve(&instructions);
    part2::solve(&instructions);
}

fn parse_input() -> Vec<(char, u32)> {
    let mut instructions = Vec::new();
    let input = fs::read_to_string("input.txt").expect("Failed to find input.txt");

    for line in input.split('\n').filter(|s| s.len() > 0) {
        let d = line.split(' ').collect::<Vec<&str>>();
        instructions.push((d[0].chars().nth(0).unwrap(), d[1].parse::<u32>().unwrap()));
    }

    instructions
}

