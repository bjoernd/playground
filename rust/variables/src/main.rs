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

use std::cmp::Ordering;

fn cmp_numbers(a : i32, b : i32) -> Ordering {
    if a < b { Ordering::Less }
    else if a > b { Ordering::Greater }
    else { Ordering::Equal }
}

fn matching() {
    let foo : i32 = 15;
    let bar : i32 = 23;

    // variant A
    match cmp_numbers(foo, bar) {
        Ordering::Less    => println!("{} is less than {}", foo, bar),
        Ordering::Equal   => println!("{} is equal to {}", foo, bar),
        Ordering::Greater => println!("{} is greater than {}", foo, bar)
    }

    // variant B
    println!("{} is {} {}", bar,
             match cmp_numbers(bar, foo) {
                 Ordering::Less => "less than",
                 Ordering::Equal => "equal to",
                 Ordering::Greater => "greather than",
             },
             foo);
}


fn looping() {
    for x in 1..10 {
        println!("x = {}", x);
    }
}


/*
   Write a program that prints the numbers from 1 to 100. But for multiples of three print "Fizz"
   instead of the number and for the multiples of five print "Buzz". For numbers which are
   multiples of both three and five print "FizzBuzz".
*/
fn fizzbuzz() {
    for i in 1..101 {
        if i % 15 == 0 { println!("Fizzbuzz"); }
        else if i % 5 == 0 { println!("Buzz"); }
        else if i % 3 == 0 { println!("Fizz"); }
        else { println!("{}", i); }
    }
}


fn vectors() {
    let mut v = vec!["a", "b", "c"];
    v.push("d");
    for c in v {
        println!("{}", c);
    }
}

fn main() {
    println!("============================================================");
    formatting();
    println!("============================================================");
    tuples();
    println!("============================================================");
    structs();
    println!("============================================================");
    matching();
    println!("============================================================");
    looping();
    println!("============================================================");
    fizzbuzz();
    println!("============================================================");
    vectors();
    println!("============================================================");
}
