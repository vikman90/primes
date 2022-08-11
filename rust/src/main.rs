// Sieve of Eratosthenes and Sundram
// Rust version
// Copyleft 2022 Vikman Fernandez-Castro - All rights revoked.
// August 6, 2022

use std::env;
use std::process::exit;
use std::time::{Instant};

mod sieve;
use sieve::*;

/// Type of sieve, for user's choice.
enum SieveType {
    Eratosthenes,
    Sundram,
}

/// Default table size.
const DEFAULT_SIZE: usize = 1000000;

fn main() {
    let (sieve_type, size) = parse_args();

    match sieve_type {
        SieveType::Eratosthenes => {
            let sieve = Eratosthenes::new(size);
            sieve_and_print(sieve);
        },

        SieveType::Sundram => {
            let sieve = Sundram::new(size);
            sieve_and_print(sieve);
        },
    }
}

/// Run sieve, print results and runtime.
fn sieve_and_print<T: Sieve + IntoIterator<Item = usize>>(mut s: T) {
    let now = Instant::now();
    s.sieve();
    let duration = now.elapsed();

    for n in s {
        println!("{}", n);
    }

    eprintln!("Time: {:.6} ms.", duration.as_nanos() as f64 / 1e6);
}

/// Parse input arguments.
fn parse_args() -> (SieveType, usize) {
    let mut sieve_type = SieveType::Eratosthenes;
    let mut size = DEFAULT_SIZE;

    for arg in env::args() {
        if arg == "-h" || arg == "--help" {
            println!("Usage: {} [-e] [-s] [MAX]", env::args().nth(0).unwrap());
            println!("  MAX                 Maximum number (default: 1000000)");
            println!("  -e, --eratosthenes  Use sieve of Eratosthenes (default)");
            println!("  -s, --sundram       Use sieve of Sundram");

            exit(0);
        } else if arg == "-e" || arg == "--eratosthenes" {
            sieve_type = SieveType::Eratosthenes;
        } else if arg == "-s" || arg == "--sundram" {
            sieve_type = SieveType::Sundram;
        } else if let Ok(v) = arg.parse::<usize>() {
            if v < 2 {
                eprintln!("WARNING: The minimum size is 2. Ignoring argument.");
            } else {
                size = v;
            }
        }
    }

    (sieve_type, size)
}
