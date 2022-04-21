use std::fs;
use std::io;

mod part1;
mod part2;

fn main() {
    // get input data from file
    let input = parse_input()
        .expect("Failed to read input from file. Does 'input.txt' exist in root?");

    part1::run(&input);
    part2::run(&input);
}

fn parse_input() -> Result<String, io::Error>{
    fs::read_to_string("input.txt")
}
