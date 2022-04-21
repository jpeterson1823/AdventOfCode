pub fn run(input: &str) {
    // convert input to vec<i32>
    let mut data: Vec<i32> = Vec::new();
    for line in input.lines() {
        data.push(line.trim().parse().unwrap());
    }

    println!("Data Length: {}", data.len());

    let step  = 3;
    let mut n = 0;
    let mut l = calc_window(&data[0..step]);

    for i in 1..data.len()-(step-1) {
        let k = calc_window(&data[i..i+step]);
        if k > l {
            n += 1;
        }
        l = k;
    }

    println!("Number of Window Increases: {}", n);
}

fn calc_window(slice: &[i32]) -> i32 {
    slice[0] + slice[1] + slice[2]
}
