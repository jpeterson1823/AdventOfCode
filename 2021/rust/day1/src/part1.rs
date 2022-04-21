pub fn run(input: &str) {
    // convert input to vec<int>
    let mut data: Vec<i32> = Vec::new();
    for line in input.lines() {
        data.push(line.trim().parse().unwrap());
    }

    // count number of times the measurement increases
    let mut n = 0;
    let mut l = data.get(0).unwrap();
    for d in &data[1..] {
        if d > l {
            n += 1;
        }
        l = d;
    }

    println!("Number of Increases: {}", n);
}
