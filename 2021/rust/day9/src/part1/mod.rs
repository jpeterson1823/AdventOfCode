struct Point {
    pub x: usize,
    pub y: usize,
}

impl Point {
    pub fn new(x: usize, y: usize) -> Self {
        Self { x, y }
    }

    pub fn get_above(&self) -> Self {
        if self.y != 0 {
            Self { 
                x: self.x,
                y: self.y-1
            }
        } else {
            Self { 
                x: self.x, 
                y: self.y 
            }
        }
    }

    pub fn get_below(&self) -> Self {
        Self {
            x: self.x,
            y: self.y+1
        }
    }

    pub fn get_left(&self) -> Self {
        if self.x != 0 {
            Self {
                x: self.x-1,
                y: self.y
            }
        } else {
            Self {
                x: self.x,
                y: self.y
            }
        }
    }
    
    pub fn get_right(&self) -> Self {
        Self {
            x: self.x+1,
            y: self.y
        }
    }
}

struct HeightMap {
    map: Vec<Vec<i32>>
}

impl HeightMap {
    pub fn new(input: &String) -> Self {
        let mut map: Vec<Vec<i32>> = Vec::new();
        for row in input.split('\n') {
            map.push(row.chars().map(|c| c.to_digit(10).unwrap() as i32).collect());
        }
        Self { map }
    }

    pub fn get(&self, p: &Point) -> i32 {
        self.map[p.y][p.x]
    }

    pub fn find_nearest_low(&self, start: Point) -> Point {
        let mut smaller = Vec::new();
        let val = self.get(&start);

        // check if above is smaller than current
        if self.get(&start.get_above()) < val {
            smaller.push(self.find_nearest_low(start.get_above()));
        }
        
        // check if below is smaller than current
        if self.get(&start.get_below()) < val {
            smaller.push(self.find_nearest_low(start.get_below()));
        }

        // check if left is smaller than current

        Point { x: 0, y: 0 }
    }
}

pub fn run(input: &String){
    // parse map from input
    let map = HeightMap::new(input);
}
