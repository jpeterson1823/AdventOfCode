use std::fs;

static ROUND_WIN:  i32 = 6i32;
static ROUND_DRAW: i32 = 3i32;
static ROUND_LOSS: i32 = 0i32;

static ROCK: i32 = 1i32;
static PAPER: i32 = 2i32;
static SCISSORS: i32 = 3i32;

fn main() {
    // get playbook from input
	let playbook = parse_input();

    // play each round
    let mut p1_total = 0;
    for round in &playbook {
        p1_total += part1_play_round(round);
    }

    let mut p2_total = 0;
    for round in &playbook {
        p2_total += part2_play_round(round);
    }

    println!("[Part1] {}", p1_total);
    println!("[Part2] {}", p2_total);
}

fn parse_input() -> Vec<String> {
	let input = fs::read_to_string("input.txt")
                    .expect("Failed to read input from file. Does 'input.txt' exist in root?");
    input.split("\n").filter(|token| token.len() > 0).map(|s| String::from(s)).collect()
}

fn part1_play_round(round: &String) -> i32{
    let opponent = round.chars().nth(0).unwrap();
    let play = round.chars().nth(2).unwrap();
    let converted_play = (play as u8 - 23u8) as char;

    if opponent == converted_play {
        match converted_play {
            'A' => ROUND_DRAW + ROCK,
            'B' => ROUND_DRAW + PAPER,
            'C' => ROUND_DRAW + SCISSORS,
            _ => unreachable!()
        }
    }
    else {
        match converted_play {
            'A' => if opponent == 'B' {ROUND_LOSS+ROCK} else {ROUND_WIN+ROCK},
            'B' => if opponent == 'C' {ROUND_LOSS+PAPER} else {ROUND_WIN+PAPER},
            'C' => if opponent == 'A' {ROUND_LOSS+SCISSORS} else {ROUND_WIN+SCISSORS},
            _ => unreachable!()
        }
    }
}

fn part2_play_round(round: &String) -> i32 {
    let opponent = round.chars().nth(0).unwrap();
    let play = round.chars().nth(2).unwrap();

    match play {
        'X' => {
            if opponent == 'A' {ROUND_LOSS + SCISSORS}
            else if opponent == 'B' {ROUND_LOSS + ROCK}
            else if opponent == 'C' {ROUND_LOSS + PAPER}
            else {unreachable!()}
        },
        'Y' => {
            if opponent == 'A' {ROUND_DRAW + ROCK}
            else if opponent == 'B' {ROUND_DRAW + PAPER}
            else if opponent == 'C' {ROUND_DRAW + SCISSORS}
            else {unreachable!()}
        },
        'Z' => {
            if opponent == 'A' {ROUND_WIN + PAPER}
            else if opponent == 'B' {ROUND_WIN + SCISSORS}
            else if opponent == 'C' {ROUND_WIN + ROCK}
            else {unreachable!()}
        },
        _ => unreachable!()
    }
}
