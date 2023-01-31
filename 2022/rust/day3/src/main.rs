use std::fs;

fn main() {
    let pocket_strings = parse_input();
    part1(&pocket_strings);
    part2(&pocket_strings);
}

fn part1(pocket_strings: &Vec<String>) {
    let mut duplicates: Vec<u8> = Vec::new();

    for pstr in pocket_strings {
        let (p1, p2) = get_pockets(pstr.clone());
        for c in p1.chars() {
            if p2.contains(c) {
                duplicates.push(priority(c));
                break;
            }
        }
    }

    println!("[Part1] {}", duplicates.iter().map(|v| *v as u32).sum::<u32>());
}

fn part2(pocket_strings: &Vec<String>) {
    let mut badges: Vec<u32> = Vec::new();

    for i in (0..pocket_strings.len()).step_by(3) {
        for c in pocket_strings[i].chars() {
            if pocket_strings[i+1].contains(c) && pocket_strings[i+2].contains(c) {
                badges.push(priority(c) as u32);
                break;
            }
        }
    }

    println!("[Part2] {}", badges.iter().sum::<u32>());
}

// parse input from txt file into Vec<String>
fn parse_input() -> Vec<String> {
	let input = fs::read_to_string("input.txt")
                    .expect("Failed to read input from file. Does 'input.txt' exist in root?");
    input.split("\n").filter(|s| s.len() > 0).map(|s| s.to_string()).collect()
}

// calculates alphabetic char's priority value
fn priority(code: char) -> u8 {
    if code.is_uppercase() {
        code as u8 - 38u8
    } else {
        code as u8 - 96u8
    }
}

// returns tuple of the two pocket strings contained in pstr
fn get_pockets(pstr: String) -> (String, String) {
    let middle = pstr.len()/2;
    (pstr[0..middle].to_string(), pstr[middle..pstr.len()].to_string())
}
