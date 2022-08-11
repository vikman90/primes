// Sieve of Eratosthenes
// Rust version
// Copyleft 2022 Vikman Fernandez-Castro - All rights revoked.
// August 11, 2022

use super::Sieve;

/// Sieve of Eratosthenes.
pub struct Eratosthenes {
    numbers: Vec<bool>
}

impl Eratosthenes {
    /// Constructor.
    pub fn new(n: usize) -> Self {
        Self { numbers: vec![true; n + 1] }
    }
}

impl Sieve for Eratosthenes {
    /// Applies sieve.
    fn sieve(&mut self) {
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
}

impl IntoIterator for Eratosthenes {
    /// The type of the elements being iterated.
    type Item = usize;

    /// The kind of iterator.
    type IntoIter = std::vec::IntoIter<Self::Item>;

    /// Creates an iterator.
    fn into_iter(self) -> Self::IntoIter {
        let v: Vec<usize> = (2..self.numbers.len()).filter(|&s| self.numbers[s]).collect();
        v.into_iter()
    }
}
