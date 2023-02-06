use std::fs;

fn main() {
    let input = parse_input();
    part1(&input);
    part2(&input);
}

fn parse_input() -> Vec<Vec<u32>> {
    fs::read_to_string("input.txt")
        .expect("Failed to open input.txt")
        .split('\n')
        .filter(|s| s.len() > 0)
        .map(|s| s.chars().map(|c| c.to_digit(10).unwrap()).collect())
        .collect()
}

fn part1(map: &Vec<Vec<u32>>) {
    // count visible trees
    let mut trees = 0u32;
    for y in 0..map.len() {
        for x in 0..map[0].len() {
            if is_visible(map, x, y) { trees += 1 }
        }
    }

    println!("[Part1] {trees}");
}

fn part2(map: &Vec<Vec<u32>>) {
    let mut score = 0u32;

    for y in 0..map.len() {
        for x in 0..map.len() {
            let tree = map[y][x];

            // vars for counting trees visible
            let mut l = 0u32;
            let mut r = 0u32;
            let mut t = 0u32;
            let mut b = 0u32;

            // get visible trees on left
            for i in (0..x).rev() {
                // count the tree
                l += 1;
                // if tree is as tall/taller than current tree, stop counting
                if map[y][i] >= tree { break; }
            }

            // get visible trees on right
            for i in x+1..map.len() {
                r += 1;
                if map[y][i] >= tree { break; }
            }

            // get visible trees on top
            for j in (0..y).rev() {
                t += 1;
                if map[j][x] >= tree { break; }
            }

            // get visible trees on bottom
            for j in y+1..map.len() {
                b += 1;
                if map[j][x] >= tree { break; }
            }

            // calculate score
            let current_score = l * r * t * b;
            // update max score
            if current_score > score {
                score = current_score;
            }
        }
    }

    println!("[Part2] {score}");
}

fn is_visible(map: &Vec<Vec<u32>>, x: usize, y: usize) -> bool {
    if x == 0 || y == 0 || x == map[0].len()-1 || y == map.len()-1 {
        true 
    } else {
        let tree = map[y][x];

        // check left
        let mut left = true;
        for i in 0..x {
            if map[y][i] >= tree {
                left = false;
                break;
            }
        }
        
        // check right
        let mut right = true;
        for i in (x+1)..map.len() {
            if map[y][i] >= tree {
                right = false;
                break;
            }
        }

        // check top
        let mut top = true;
        for j in 0..y {
            if map[j][x] >= tree {
                top = false;
                break;
            }
        }

        // check bottom
        let mut bottom = true;
        for j in (y+1)..map.len() {
            if map[j][x] >= tree {
                bottom = false;
                break;
            }
        }

        top || bottom || left || right
    }
}

