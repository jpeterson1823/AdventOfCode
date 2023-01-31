use std::fs;

fn main() {
    let input = parse_input();
    part1(&input);
    part2(&input);
}

fn valid_sequence(s: &[char]) -> bool {
    let mut seen = Vec::new();
    for c in s {
        if seen.contains(c) {
            return false;
        } else {
            seen.push(c.clone());
        }
    }
    true
}

fn part1(input: &String) {
    // iterate through string with char windows of wlen
    let chars: Vec<char> = input.chars().collect();
    let wlen = 4;
    for i in wlen..input.len() {
        let window = &chars[i-wlen..i];
        if valid_sequence(window) {
            println!("[Part1] {}", i);
            break;
        }
    }
}

fn part2(input: &String) {
    // iterate through string with char windows of wlen
    let chars: Vec<char> = input.chars().collect();
    let wlen = 14;
    for i in wlen..input.len() {
        let window = &chars[i-wlen..i];
        if valid_sequence(window) {
            println!("[Part2] {}", i);
            break;
        }
    }
}


fn parse_input() -> String {
    fs::read_to_string("input.txt")
        .expect("Failed to read input from file. Does 'input.txt' exist in root?")
}
