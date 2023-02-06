use super::part1::Point;
use std::cell::RefCell;
use std::rc::Rc;
use std::fmt;

pub fn solve(instructions: &Vec<(char, u32)>) {
    let krope = KnotRope::new(10);

    for instruction in instructions {
        for _step in 0..instruction.1 {
            krope.step(instruction.0);
        }
    }

    println!("{krope}");
}

// basically a linked list node
struct Knot { //{{{
    pub pos: Point,
    pub tail: Option<Rc<RefCell<Knot>>>
}
impl Knot {
    // creates Knot instance at pos=(0,0) with no tail
    pub fn new() -> Self {
        Self {
            pos: Point::new(),
            tail: None
        }
    }
    // creates Knot instance wrapped with rc-refcell smart pointer
    pub fn smart_new() -> Rc<RefCell<Self>> {
        Rc::new(RefCell::new(Self {
            pos: Point::new(),
            tail: None
        }))
    }

    //**** accessors, mutators, and control flow helpers
    pub fn set_pos(&mut self, pos: Point) {
        self.pos = pos;
    }
    pub fn set_tail(&mut self, knot: Rc<RefCell<Knot>>) {
        self.tail = Some(knot);
    }
    pub fn has_tail(&self) -> bool {
        match self.tail {
            Some(_) => true,
            None => false
        }
    }
    pub fn remove_tail(&mut self) {
        self.tail = None;
    }
}
impl fmt::Display for Knot {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "({})", self.pos)
    }
}
//}}}

// Rope with multiple knots, modeled after a linked list
struct KnotRope {
    head: Rc<RefCell<Knot>>,
    tail: Rc<RefCell<Knot>>,
    knots: u32,
    visited: Vec<Point>
}
impl KnotRope {
    // create new KnotRope instance with head->tail->none, both at pos=(0,0)
    pub fn new(knots: u32) -> Self {
        // create head knot and tail knot
        let head = Knot::smart_new();
        let mut tail = head.clone();

        // add origin to visited
        let visited = vec![Point::new()];

        // add requested knots to tail, then update tail
        for _ in 0..knots-1 {
            let new_tail = Knot::smart_new();
            tail.borrow_mut().set_tail(new_tail.clone());
            tail = new_tail;
        }

        // generate Self obj
        Self { head, tail, knots, visited }
    }

    //**** accessors, mutators, and control flow helpers
    // number of knots; effectively rope length
    pub fn knots(&self) -> u32 {
        self.knots
    }
    pub fn head(&self) -> Rc<RefCell<Knot>> {
        self.head.clone()
    }
    pub fn tail(&self) -> Rc<RefCell<Knot>> {
        self.tail.clone()
    }
    pub fn get_knot(&self, index: u32) -> Rc<RefCell<Knot>> {
        let mut knot = self.head.clone();
        for _ in 0..index {
            knot = match knot.clone().borrow().tail {
                Some(k) => k.clone(),
                None => panic!("[KnotRope.OutOfBounds] Attempted to move past tail node of KnotRope.")
            };
        }
        knot
    }

    // steps rope in direction and updates tails
    pub fn step(&self, direction: char) {
        let mut head = self.head.borrow_mut();
        match direction {
            'L' => head.pos.x -= 1,
            'R' => head.pos.x += 1,
            'U' => head.pos.y += 1,
            'D' => head.pos.y -= 1,
            _   => unreachable!()
        };
        self.update_tail();
    }

    // recursively updates tail knots, returns true if update performed
    fn update_tail(&self) -> bool {
        // first, determine if node even has tail
        // if no tail, then return false as update cannot occur
        match self. head.borrow().tail {
            Some(_) => (),
            None => return false
        };

        // check if tail needs to be updated
        if self.is_tail_invalid() {
            //print!("\tINVALID!\t");
            let delta = self.head.borrow().pos - self.tail.borrow().pos;
            let dxhat = if delta.x != 0 { delta.x/delta.x.abs() } else { 0 };
            let dyhat = if delta.y != 0 { delta.y/delta.y.abs() } else { 0 };
            
            // check if horizontally skewed
            if delta.x.abs() > 1 {
                // tail moves in direction of dx
                self.tail.borrow_mut().pos.x += dxhat;

                // check if vertically skewed at all
                if delta.y.abs() > 0 {
                    // tail moves in direction of dy
                    self.tail.borrow_mut().pos.y += dyhat;
                }
            }

            // check if vertically skewed
            else if delta.y.abs() > 1 {
                // tail moves in direction of dy
                self.tail.borrow_mut().pos.y += dyhat;

                // check if horizontally skewed at all
                if delta.x.abs() > 0 {
                    // tail moves in direction of dx
                    self.tail.borrow_mut().pos.x += dxhat;
                }
            }

            // TODO: recurse for tails

            // since tail moved, return true
            true
        } else { false }
    }

    // determines if tail is in valid position relative to head
    // tail is valid as long as it is no more than 1 place away from head in all directions
    fn is_tail_invalid(&self) -> bool {
        let delta = *self.head.borrow().pos() - *self.tail.borrow().pos();
        delta.x.abs() > 1 && delta.y.abs() > 1
    }
}
impl fmt::Display for KnotRope {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        let mut string = format!("H{}", self.head.borrow().pos());
        let mut current = self.head.clone();
        #[allow(while_true)]
        while true {
            // if no tail to move to, break loop
            let next = match current.borrow().tail() {
                Some(knot) => knot.clone(),
                None => break
            };
            string += format!("-->{}", next.borrow().pos()).as_str();
            current = next;
        }
        string += "T";
        write!(f, "{}", string)
    }
}
