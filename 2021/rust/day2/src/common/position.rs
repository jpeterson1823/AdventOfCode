pub struct Position {
    pub x: i32,
    pub y: i32,
}

impl Position {
    pub fn default() -> Position {
        Position { x: 0, y: 0 }
    }

    pub fn new(x: i32, y: i32) -> Position {
        Position { x, y }
    }

    pub fn print(&self, label: Option<&String>) {
        if let Some(s) = label {
            println!("{}(x={}, y{})", s, self.x, self.y);
        } else {
            println!("Position(x={}, y={})", self.x, self.y);
        }
    }
}
