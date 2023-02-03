use std::rc::Rc;
use std::cell::RefCell;

#[derive(Debug)]
#[allow(dead_code)]
pub struct Directory {
    name:  String,
    files: Vec<(String, u32)>,
    dirs:  Vec<Rc<RefCell<Directory>>>
}

impl Directory {
    pub fn new(name: String) -> Self {
        Directory {
            name,
            files: Vec::new(),
            dirs:  Vec::new()
        }
    }

    #[allow(dead_code)]
    pub fn get_name(&self) -> &String {
        &self.name
    }

    pub fn add_file(&mut self, name: String, size: u32) {
        self.files.push((name, size));
    }

    #[allow(dead_code)]
    pub fn get_files(&self) -> &Vec<(String, u32)> {
        &self.files
    }

    pub fn add_dir(&mut self, name: String) -> Rc<RefCell<Directory>> {
        let dir = Rc::new(RefCell::new(Directory::new(name)));
        self.dirs.push(dir.clone());
        dir.clone()
    }
    
    pub fn get_dirs(&self) -> &Vec<Rc<RefCell<Directory>>> {
        &self.dirs
    }

    pub fn calculate_size(&self) -> u32 {
        let mut size = 0u32;

        // sum up size of contained files
        for file in self.files.iter() {
            size += file.1;
        }

        // recurse for each child directory
        for dir in self.dirs.iter() {
            size += dir.borrow().calculate_size();
        }

        size
    }

    #[allow(dead_code)]
    pub fn print(&self) {
        println!("{}", self.name);
        for file in self.files.iter() {
            println!("\t{}, {}", file.0, file.1);
        }
        for dir in self.dirs.iter() {
            println!("\t{}", dir.borrow().name);
        }
    }
}
