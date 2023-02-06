use std::ops::Sub;
use std::fmt;

pub fn solve(instructions: &Vec<(char, u32)>) {
    let mut rope = Rope::new();

    // move rope via instructions
    for instruction in instructions {
        for _step in 0..instruction.1 {
            rope.step(instruction.0);
        }
    }

    println!("[Part1] {}", rope.get_visited().len());
}

#[derive(Copy, Clone, PartialEq, Debug)]
pub struct Point {
    pub x: i32,
    pub y: i32
}
impl Point {
    pub fn new() -> Self {
        Self { x:0, y:0 }
    }
}
impl Sub for Point {
    type Output = Self;
    fn sub(self, other: Self) -> Self::Output {
        Self {
            x: self.x - other.x,
            y: self.y - other.y
        }
    }
}
impl fmt::Display for Point {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "({}, {})", self.x, self.y)
    }
}


struct Rope {
    head: Point,
    tail: Point,
    visited: Vec<Point>
}

impl Rope {
    pub fn new() -> Self {
        // initialize with (0,0) in visited as tail spawns there
        Self {
            head: Point::new(),
            tail: Point::new(),
            visited: vec![Point::new()]
        }
    }

    pub fn step(&mut self, direction: char) {
        //println!("DIRECTION: {direction}");
        match direction {
            'L' => self.head.x -= 1,
            'R' => self.head.x += 1,
            'U' => self.head.y += 1,
            'D' => self.head.y -= 1,
            _   => unreachable!()
        };
        self.update_tail();
    }

    // if tail not in valid place, move accordingly
    fn update_tail(&mut self) {
        //print!("ROPE: {:?}, {:?}",self.head, self.tail);
        if !self.is_tail_valid() {
            //print!("\tINVALID!\t");
            let delta = self.head - self.tail;
            let dxhat = if delta.x != 0 { delta.x/delta.x.abs() } else { 0 };
            let dyhat = if delta.y != 0 { delta.y/delta.y.abs() } else { 0 };
            
            // check if horizontally skewed
            if delta.x.abs() > 1 {
                // tail moves in direction of dx
                self.tail.x += dxhat;

                // check if vertically skewed at all
                if delta.y.abs() > 0 {
                    // tail moves in direction of dy
                    self.tail.y += dyhat;
                }
            }

            // check if vertically skewed
            else if delta.y.abs() > 1 {
                // tail moves in direction of dy
                self.tail.y += dyhat;

                // check if horizontally skewed at all
                if delta.x.abs() > 0 {
                    // tail moves in direction of dx
                    self.tail.x += dxhat;
                }
            }

            //println!("NEW: {:?}, {:?}", self.head, self.tail);

            // tail must have moved. if visiting new spot, add to visited
            if !self.visited.contains(&self.tail) {
                self.visited.push(self.tail.clone());
            }
        } //else { println!("\tVALID!"); }
    }

    // determines if tail is in a valid place relative to head
    fn is_tail_valid(&self) -> bool {
        // tail in valid place if distance between head in x and y are both at most 1
        let delta = self.head - self.tail;
        delta.x.abs() < 2 && delta.y.abs() < 2
    }

    // returns ref to list of unique visited places
    pub fn get_visited(&self) -> &Vec<Point> {
        &self.visited
    }
}
