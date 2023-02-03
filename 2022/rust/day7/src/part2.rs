use super::part1;

pub fn run(input: &Vec<String>) {
    let root = part1::parse_file_tree(input);

    // disk info
    let disk_size   = 70000000u32;
    let update_size = 30000000u32;
    let used_space = root.borrow().calculate_size();

    let mut min_dir_size = disk_size;
    let mut dir_q = part1::create_dir_queue(root.clone());
    while dir_q.len() != 0 {
        let dir_size = dir_q.pop().unwrap().borrow().calculate_size();
        let available_space = disk_size - (used_space - dir_size);
        if available_space >= update_size && min_dir_size > dir_size {
            min_dir_size = dir_size;
        }
    }

    println!("[Part2] {min_dir_size}");
}
