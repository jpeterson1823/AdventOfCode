use std::fs;

mod directory;
mod part1;
mod part2;

fn main() {
    let input = parse_input();
    part1::run(&input);
    part2::run(&input);
}

fn parse_input() -> Vec<String> {
    fs::read_to_string("input.txt")
        .expect("Failed to open input.txt")
        .split('\n')
        .filter(|s| s.len() > 0)
        .map(|s| s.to_string())
        .collect()
}

