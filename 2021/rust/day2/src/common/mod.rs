pub mod position;

use std::fs::File;
use std::io::{self, BufRead};
use std::process;

// Read file line-by-line and store in Vec<String>
pub fn parse_input(path: &str) -> Vec<String>{
    let mut input: Vec<String> = Vec::new();

    // open file
    let file = match File::open("input.txt") {
        Ok(f) => f,
        Err(e) => {
            eprintln!("[ERROR] Failed to parse input from file: {}", e);
            process::exit(1);
        }
    };

    // read file and store in vec
    let lines = io::BufReader::new(file).lines();
    for line in lines {
        if let Ok(string) = line {
            input.push(string);
        }
    }

    // return parsed input
    input
}
