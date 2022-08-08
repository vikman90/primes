// Sieve of Eratosthenes and Sundram
// Rust version
// Copyleft 2022 Vikman Fernandez-Castro - All rights revoked.
// August 8, 2022

pub struct Eratosthenes {
    numbers: Vec<bool>
}

pub struct Sundram {
    numbers: Vec<bool>
}

impl Eratosthenes {
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

impl Sundram {
    pub fn new(n: usize) -> Self {
        Self { numbers: vec![true; (n - 1) / 2 + 1] }
    }

    pub fn find_primes(&mut self) {
        let k = self.numbers.len() - 1;
        let bound= (k as f64).sqrt() as usize;

        for i in 1..=bound {
            let mut j = i;

            while i + j + 2 * i * j <= k {
                self.numbers[i + j + 2 * i * j] = false;
                j += 1;
            }
        }
    }

    pub fn as_vec(&self) -> Vec<usize> {
        let mut v: Vec<usize> = (1..self.numbers.len()).filter(|&s| self.numbers[s]).collect();
        let mut w: Vec<usize> = v.iter().map(|&s| s * 2 + 1).collect();
        v = vec![2];
        v.append(&mut w);
        v
    }
}
