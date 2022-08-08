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

    for i in primes {
        println!("{}", i);
    }

    eprintln!("Time: {:.6} ms.", duration.as_nanos() as f64 / 1e6);
}

fn sieve(primes: &mut Vec<u32>) {
    let bound = (*primes.last().unwrap() as f64).sqrt() as u32;

    for i in 0..primes.len() {
        let p_i = primes[i];

        if primes[i] > bound {
            break;
        }

        primes.retain(|&x| x == p_i || x % p_i != 0);
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
