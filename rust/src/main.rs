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
    let mut primes: Vec<Option<u32>> = (2..=size).map(|s| Option::Some(s)).collect();

    let now = Instant::now();
    sieve(&mut primes);
    let duration = now.elapsed();

    for i in primes {
        if let Some(pi) = i {
            println!("{}", pi);
        }
    }

    eprintln!("Time: {:.6} ms.", duration.as_nanos() as f64 / 1e6);
}

fn sieve(primes: &mut Vec<Option<u32>>) {
    let bound = (primes.last().unwrap().unwrap() as f64).sqrt() as u32;

    for i in 0..primes.len() {
        if let Some(pi) = primes[i] {
            if pi > bound {
                break;
            }

            for j in i+1..primes.len() {
                if let Some(pj) = primes[j] {
                    if pj % pi == 0 {
                        primes[j] = Option::None;
                    }
                }
            }
        }
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
