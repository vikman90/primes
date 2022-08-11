# Sieve methods for finding prime numbers (Rust)

## Set up environment

- Install Rust:
```sh
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
```

## Build

```sh
cargo build --release
```

## Synopsis

```
sieve [-e] [-s] [MAX]
```

<dl>
  <dt>MAX</dt>
  <dd>Maximum number (default: 1000000)</dd>
  <dt>-e, --eratosthenes</dt>
  <dd>Use sieve of Eratosthenes (default)</dd>
  <dt>-s, --sundram</dt>
  <dd>Use sieve of Sundram</dd>
</dl>

### Examples

```
$ target/release/sieve -e | wc -l | echo $(cat -) "primes found."
Time: 16.606588 ms.
664579 primes found.
```

```
$ target/release/sieve -s | wc -l | echo $(cat -) "primes found."
Time: 17.683411 ms.
664579 primes found.
```
