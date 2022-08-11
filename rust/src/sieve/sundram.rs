// Sieve of Sundram
// Rust version
// Copyleft 2022 Vikman Fernandez-Castro - All rights revoked.
// August 11, 2022

use super::Sieve;

/// Sieve of Sundram.
pub struct Sundram {
    numbers: Vec<bool>
}

impl Sundram {
    /// Constructor.
    pub fn new(n: usize) -> Self {
        Self { numbers: vec![true; (n - 1) / 2 + 1] }
    }
}

impl Sieve for Sundram {
    /// Applies sieve.
    fn sieve(&mut self) {
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
}

impl IntoIterator for Sundram {
    /// The type of the elements being iterated.
    type Item = usize;

    /// The kind of iterator.
    type IntoIter = std::vec::IntoIter<Self::Item>;

    /// Creates an iterator.
    fn into_iter(self) -> Self::IntoIter {
        let mut v: Vec<usize> = (1..self.numbers.len()).filter(|&s| self.numbers[s]).map(|s| s * 2 + 1).collect();
        let mut w = vec![2usize];
        w.append(&mut v);
        w.into_iter()
    }
}
