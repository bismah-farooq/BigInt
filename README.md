# BigInt (C++)

This project implements a BigInt class in C++ that supports arbitrarily large integers beyond the limits of built-in data types. The program demonstrates operator overloading, dynamic storage using vectors, and mathematical computations such as Fibonacci and factorial for very large numbers.

## Description
Standard C++ integer types are limited in size and cannot handle extremely large values. This project introduces a custom BigInt class that stores digits using a vector of characters, allowing numbers of unlimited length.

The BigInt class supports:
- Construction from integers and strings
- Arithmetic operations using overloaded operators
- Fibonacci and factorial calculations for large values
- Custom output formatting for large numbers

## Features
- Stores digits using vector<char>
- Operator overloading for arithmetic (+, -, *, /, %, ++)
- Comparison and indexing support
- Fibonacci calculation using tail recursion
- Factorial calculation for large numbers
- Automatic exponential notation when numbers exceed 12 digits
- Full digit output using a print() function

## How to Compile
```text
g++ bigint.cpp -o bigint
```
## How to Run
```text
./bigint
```
The program runs a built-in testUnit function that demonstrates:
- BigInt construction
- Arithmetic operations
- Fibonacci and factorial calculations
- Overflow-safe large number handling
- Output formatting for very large values

## Output Notes
- Numbers with 12 or fewer digits are printed normally
- Numbers with more than 12 digits are printed in exponential notation
- The print() function always prints all digits

## Learning Objectives
- Understand operator overloading in C++
- Implement arbitrary-precision arithmetic
- Use vectors for dynamic digit storage
- Apply recursion for mathematical algorithms
- Practice system-level programming concepts
