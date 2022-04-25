mod part1;
mod part2;

use std::fs::File;
use std::io::{self, BufRead};
use std::process;

fn parse_input() -> Vec<String> {
    let mut input: Vec<String> = Vec::new();

    // open file
    let file = match File::open("input.txt") {
        Ok(f) => f,
        Err(e) => {
            eprintln!("[ERROR] Failed to parse input: {}", e);
            process::exit(1);
        }
    };

    // read file line-by-line and store in vec
    for line in io::BufReader::new(file).lines() {
        if let Ok(string) = line {
            input.push(string);
        }
    }

    // return parsed input
    input
}

fn main() {
    let input = parse_input();
    part1::run(&input);
}
