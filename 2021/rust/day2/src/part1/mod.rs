use super::common::position::Position;

pub fn run(input: &Vec<String>) {
    // create submarine position
    let mut position = Position::default();

    // parse and execute each instruction
    for instruction in input {
        // split instruction into the direction and number of steps
        let pair = instruction.split(' ').collect::<Vec<&str>>();
        let direction = pair[0];
        let steps = pair[1].parse::<i32>().unwrap();

        // execute instruction
        if direction.eq("forward") {
            position.x += steps;
        }
        else if direction.eq("up") {
            position.y += steps;
        }
        else if direction.eq("down") {
            position.y -= steps;
        }
    }

    // calculate answer and print
    println!("Part 1) {}", (position.x * position.y).abs());
}

