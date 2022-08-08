// Sieve of Eratosthenes
// Rust version
// Copyleft 2022 Vikman Fernandez-Castro - All rights revoked.
// August 6, 2022

use std::env;
use std::process::exit;
use std::time::{Instant};

mod sieve;
use sieve::Sieve;

const DEFAULT_SIZE: usize = 1000000;

fn main() {
    let size = parse_args();
    let mut sieve = Sieve::new(size);

    let now = Instant::now();
    sieve.find_primes();
    let duration = now.elapsed();

    for i in sieve.as_vec() {
        println!("{}", i);
    }

    eprintln!("Time: {:.6} ms.", duration.as_nanos() as f64 / 1e6);
}

fn parse_args() -> usize {
    let mut size = DEFAULT_SIZE;

    for arg in env::args() {
        if arg == "-h" || arg == "--help" {
            println!("Syntax: sieve [SIZE]");
            exit(0);
        } else if let Ok(v) = arg.parse::<usize>() {
            if v < 2 {
                eprintln!("WARNING: The minimum size is 2. Ignoring argument.");
            } else {
                size = v;
            }
        }
    }

    size
}
