// Sieve of Eratosthenes and Sundram
// Rust version
// Copyleft 2022 Vikman Fernandez-Castro - All rights revoked.
// August 8, 2022

mod eratosthenes;
mod sundram;

pub use eratosthenes::Eratosthenes;
pub use sundram::Sundram;

/// Represents types of sieves.
pub trait Sieve {
    /// Applies sieve.
    fn sieve(&mut self);
}
