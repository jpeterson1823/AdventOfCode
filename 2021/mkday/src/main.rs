const MAIN_STR: &[u8] = "use std::fs;\nuse std::io;\n\nmod part1;\nmod part2;\n\nfn main() {\n\t// get input data from file\n\tlet input = parse_input()\n\t\t.expect(\"Failed to read input from file. Does 'input.txt' exist in root?\");\n\tpart1::run(&input);\n\tpart2::run(&input);\n}\n\nfn parse_input() -> Result<String, io::Error>{\n\tfs::read_to_string(\"input.txt\")\n}".as_bytes();
const PART_STR: &[u8] = "pub fn run(input: &String){\n\t\n}".as_bytes();

use std::{
    fs,
    io::{self, Write},
    process,
};


fn main() {
    // get name of crate
    let day_name = format!("day{}", get_day());
    
    // create new cargo crate
    process::Command::new("cargo")
        .args(["new", day_name.as_str()])
        .status()
        .expect("Failed to run cargo command");

    // fill main with MAIN_STR
    fs::write(format!("./{}/src/main.rs", day_name), MAIN_STR)
        .expect("Failed to write data to 'main.rs'");

    // create input.txt
    fs::File::create(format!("./{}/input.txt", day_name)).expect("Failed to create 'input.txt'");

    // create part1 and part2 directories
    fs::create_dir(format!("./{}/src/part1", day_name)).expect("Failed to create 'src/part1' directory");
    fs::create_dir(format!("./{}/src/part2", day_name)).expect("Failed to create 'src/part2' directory");

    // create and fill part1 and part2 mod files
    let mut part1 = fs::File::create(format!("./{}/src/part1/mod.rs", day_name)).expect("Failed to create 'src/part1/mod.rs'");
    let mut part2 = fs::File::create(format!("./{}/src/part2/mod.rs", day_name)).expect("Failed to create 'src/part2/mod.rs'");
    part1.write_all(PART_STR).expect("Failed to write data to 'src/part1/mod.rs'");
    part2.write_all(PART_STR).expect("Failed to write data to 'src/part2/mod.rs'");
}


fn get_day() -> u8 {
    print!("Please enter a day number: ");
    io::stdout().flush().expect("Failed to flush stdout!");

    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();

    input.replace('\n', "").parse().expect("Invalid day number provided!")
}
