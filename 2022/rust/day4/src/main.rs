use std::fs;

fn main() {
    let input = parse_input();
    let pairs = parse_pairs(&input);
    part1(&pairs);
}

fn part1(pairs: &Vec<Vec<Vec<u32>>>) {
    let mut p1_answer = 0;
    for pair in pairs {
        if pair.len() > 1 {
            let a = &pair[0];
            let b = &pair[1];

            // check if a task encompases its partner
            if a_in_b(a, b) || a_in_b(b, a) {
                p1_answer += 1;
            }
        }
    }

    let mut p2_answer = 0;
    for pair in pairs {
        if pair.len() > 1 {
            let a = &pair[0];
            let b = &pair[1];
            for v in a {
                if b.contains(v) {
                    p2_answer += 1;
                    break;
                }
            }
        }
    }

    println!("[Part1] {p1_answer}");
    println!("[Part2] {p2_answer}");
}

fn parse_input() -> String {
    fs::read_to_string("input.txt")
        .expect("Failed to read input from file. Does 'input.txt' exist in root?")
}

fn parse_pairs(input: &String) -> Vec<Vec<Vec<u32>>> {
    let mut pairs = Vec::new();
    for pair_str in input.split("\n") {
        let mut pair = Vec::new();
        for range_str in pair_str.split(',') {
            let nums: Vec<u32> = range_str.split('-')
                                          .filter(|t| t.len() > 0)
                                          .map(|t| t.parse().unwrap()).collect();
            if nums.len() > 0 {
                pair.push((nums[0]..(nums[1] + 1)).collect());
            }
        }
        pairs.push(pair);
    }
    pairs
}

fn a_in_b(a: &Vec<u32>, b: &Vec<u32>) -> bool {
    for v in a {
        if !b.contains(&v) { return false; }
    }
    true
}

