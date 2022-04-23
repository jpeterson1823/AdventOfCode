use day2::{
    common::parse_input,
    part1,
    part2,
};

fn main() {
    // get input data from file
    let input = parse_input("input.txt");

    // run part1
    part1::run(&input);
    // run part2
    part2::run(&input);
}
