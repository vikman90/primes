// Sieve of Eratosthenes
// Rust version
// Copyleft 2022 Vikman Fernandez-Castro - All rights revoked.
// August 8, 2022

pub struct Sieve {
    numbers: Vec<bool>
}

impl Sieve {
    pub fn new(n: usize) -> Self {
        Self { numbers: vec![true; n + 1] }
    }

    pub fn find_primes(&mut self) {
        let size = self.numbers.len() - 1;
        let bound= (size as f64).sqrt() as usize;

        for i in 2..=bound {
            if self.numbers[i] {
                let mut j = i * i;

                while j <= size {
                    self.numbers[j] = false;
                    j += i;
                }
            }
        }
    }

    pub fn as_vec(&self) -> Vec<usize> {
        (2..self.numbers.len()).filter(|&s| self.numbers[s]).collect()
    }
}
