use super::common::position::Position;

struct Submarine {
    position: Position,
    aim: i32,
}

impl Submarine {
    fn forward(&mut self, steps: i32) {
        self.position.x += steps;
        self.position.y += self.aim * steps;
    }
}

pub fn run(input: &Vec<String>) {
    // create submarine
    let mut submarine = Submarine {
        position: Position::default(),
        aim: 0,
    };

    // parse and execute every instruction
    for instruction in input {
        let pair = instruction.split(' ').collect::<Vec<&str>>();
        let direction = pair[0];
        let steps = pair[1].parse::<i32>().unwrap();

        if direction.eq("forward") {
            submarine.forward(steps);
        }
        else if direction.eq("up") {
            submarine.aim -= steps;
        }
        else if direction.eq("down") {
            submarine.aim += steps;
        }
    }

    // calculate and print answer
    let answer = submarine.position.x * submarine.position.y;
    println!("Part 2) {}", answer.abs());
}
