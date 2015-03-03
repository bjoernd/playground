fn formatting() {
    let mut x : u32 = 1;
    let mut y : i32 = 1;
    println!("Hello, world {} {}!", x, y);
    x = x - 2;
    y = y - 4;
    println!("Hello, world {} {}!", x, y);
    println!("Hello, world {:x} {:x}!", x, y);
    println!("Hello, world {1:x} {0:x}!", x, y);
}

fn main() {
    formatting();
}
