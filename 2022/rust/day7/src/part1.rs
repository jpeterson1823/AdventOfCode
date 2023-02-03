use super::directory::Directory;
use std::cell::RefCell;
use std::rc::Rc;

pub fn run(input: &Vec<String>) {
    let limit = 100000u32;
    let root = parse_file_tree(input);

    // create a queue of directories to size
    let mut dir_q = create_dir_queue(root.clone());

    // sum sizes of dirs that are less than limit
    let mut sum = 0u32;
    while dir_q.len() != 0 {
        let temp = dir_q.pop().unwrap().borrow().calculate_size();
        if temp <= limit { sum += temp; }
    }

    println!("[Part1] {sum}");
}

pub fn parse_file_tree(input: &Vec<String>) -> Rc<RefCell<Directory>> {
    let root = Rc::new(RefCell::new(Directory::new("/".to_string())));

    let mut path: Vec<Rc<RefCell<Directory>>> = Vec::new();
    let mut cwd = root.clone();

    // iterate through each line of input
    let mut listing = false;
    for line in input {
        let delimited: Vec<&str> = line.split(' ').collect();
        let is_command = delimited[0].chars().nth(0).unwrap() == '$';

        // if listing flag set, either add entries to cwd or disable flag
        if listing {
            let is_dir = delimited[0].contains("dir");
            if is_command {
                listing = false;
            } else {
                let delimited: Vec<&str> = line.split(' ').collect();
                if !is_dir {
                    let size: u32 = delimited[0].parse().unwrap();
                    cwd.borrow_mut().add_file(delimited[1].to_string(), size);
                }
            }
        }

        // run command
        if !listing && is_command {
            match delimited[1] {
                "cd" => {
                    let dest = delimited[2];
                    if dest == "/" {
                        cwd = root.clone();
                    }
                    else if dest == ".." {
                        // move up a dir
                        cwd = path.pop().unwrap().clone();
                    } else {
                        // add dir to cwd, then move cwd to new dir
                        let dir = cwd.borrow_mut().add_dir(dest.to_string());
                        path.push(cwd.clone());
                        cwd = dir;
                    }
                },
                "ls" => {
                    // set listing flag
                    listing = true;
                },
                _ => unreachable!()
            };
        }
    }
    root
}

pub fn create_dir_queue(root: Rc<RefCell<Directory>>) -> Vec<Rc<RefCell<Directory>>> {
    let mut q = vec![root.clone()];
    for dir in root.borrow().get_dirs().iter() {
        q.append(&mut create_dir_queue(dir.clone()));
    }
    q
}
