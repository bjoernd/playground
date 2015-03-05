// XXX: template fn would be nice...
fn dec_val(x : u32) -> u32 {
    println!("Decrementing");
    x-1 // No ; at the end for return value reasons...
}

fn print_x_y(x :u32, y :i32) {
    println!("x = {}, y = {}", x, y);
}

fn formatting() {
    let mut x : u32 = 1;
    let mut y : i32 = 1;
    print_x_y(x, y);
    x = dec_val(x);
    x = dec_val(x);
    y = y - 2;
    print_x_y(x, y);
    println!("Hello, world {:x} {:x}!", x, y);
    println!("Hello, world {1:x} {0:x}!", x, y); // order modified
}


fn reverse_three_tuple(a:i32, b:i32, c:i32) -> (i32, i32, i32) {
    (c, b, a)
}


fn tuples() {
    let x = reverse_three_tuple(1,2,3);
    let y = reverse_three_tuple(22,5,7);
    let z = x;

    if x == y {
        println!("x == y");
    } else {
        println!("x != y");
    }

    if x == z {
        println!("x == z");
    } else {
        println!("x != z");
    }
}

struct FooBarBaz {
    foo : i32,
    bar : i32,
    baz : i32
}

fn print_foobarbaz(fb : FooBarBaz) {
    println!("FOOBARBAZ [foo={}, bar={}, baz={}]", fb.foo, fb.bar, fb.baz);
}

fn structs() {
    let f = FooBarBaz { foo : 1, bar : 2, baz : 42 };
    print_foobarbaz(f);
}

fn main() {
    println!("============================================================");
    formatting();
    println!("============================================================");
    tuples();
    println!("============================================================");
    structs();
    println!("============================================================");
}
