// Sieve of Eratosthenes
// Rust version
// Copyleft 2022 Vikman Fernandez-Castro - All rights revoked.
// August 6, 2022

use std::env;
use std::process::exit;
use std::time::{Instant};

const DEFAULT_SIZE: u32 = 1000000;

fn main() {
    let size = parse_args();
    let mut primes: Vec<u32> = (2..=size).collect();

    let now = Instant::now();
    sieve(&mut primes);
    let duration = now.elapsed();
    primes.sort();

    for i in primes {
        println!("{}", i);
    }

    eprintln!("Time: {:.6} ms.", duration.as_nanos() as f64 / 1e6);
}

fn sieve(primes: &mut Vec<u32>) {
    // Bug: leaks some values due to swapping and j=i+1.

    let bound = (*primes.last().unwrap() as f64).sqrt() as u32;

    let mut i = 0;
    while i < primes.len() {
        if primes[i] > bound {
            i += 1;
            continue;
        }

        let mut j = i + 1;
        while j < primes.len() {
            if primes[j] % primes[i] == 0 {
                primes.swap_remove(j);
            } else {
                j += 1;
            }
        }

        i += 1;
    }
}

fn parse_args() -> u32 {
    let mut size = DEFAULT_SIZE;

    for arg in env::args() {
        if arg == "-h" || arg == "--help" {
            println!("Syntax: sieve [SIZE]");
            exit(0);
        } else if let Ok(v) = arg.parse::<u32>() {
            if v < 2 {
                eprintln!("WARNING: The minimum size is 2. Ignoring argument.");
            } else {
                size = v;
            }
        }
    }

    size
}
