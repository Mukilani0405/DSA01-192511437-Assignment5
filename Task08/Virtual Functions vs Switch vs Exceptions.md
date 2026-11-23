# Task B3 – Virtual Functions vs Switch vs Exceptions

### 1. Comparison of Billing Methods

The hospital billing system can calculate bills using three approaches:

1. **Virtual functions:** Each derived bill class implements its own `total()` function. Runtime polymorphism selects the correct function.
2. **Switch statement:** A single function checks the bill type and calculates the amount using different cases.
3. **Exceptions:** Exceptions handle invalid billing data and unexpected errors.

### 2. Correctness Testing

The same set of 10 bills is tested using virtual functions and switch statements.

Both approaches should produce the same billing totals when implemented correctly.

### 3. Performance Benchmarking

The billing methods are tested with different numbers of bills using compiler optimization.

| Number of bills | Virtual functions | Switch statement |
|---|---|---|
| 1,000 | Measure execution time | Measure execution time |
| 1,000,000 | Measure execution time | Measure execution time |
| 10,000,000 | Measure execution time | Measure execution time |

Command used:

```bash
g++ -std=c++17 -O2 -Wall -Wextra benchmark.cpp -o benchmark
```

The execution time is recorded for each test. Actual timings depend on the processor, compiler, and system load.

### 4. Exception vs Return Code Benchmark

One million claims are tested with different invalid-claim percentages.

| Invalid claims | Exceptions | Return codes |
|---|---|---|
| 0% | Measure time | Measure time |
| 1% | Measure time | Measure time |
| 50% | Measure time | Measure time |

When errors are rare, exceptions can keep normal program logic simple. When errors are frequent, return codes may perform better because exception handling requires stack unwinding.

### 5. Engineering Trade-off

| Method | Advantages | Limitations |
|---|---|---|
| Virtual functions | Flexible and easy to extend | Has virtual dispatch overhead |
| Switch statement | Simple and direct | Requires modification when adding new types |
| Exceptions | Separates error handling from normal logic | Error handling can be costly |
| Return codes | Suitable for frequent predictable errors | Requires checking every result |

### 6. Alternative Approach – `std::variant` and `std::visit`

`std::variant` can store different bill types, and `std::visit` can select the appropriate calculation.

It provides type safety and avoids traditional virtual inheritance. Its performance and memory usage should be measured with the same 10-million-bill test.

### Result

Virtual functions provide better flexibility for extending the hospital billing system. Switch statements can be useful for a small fixed set of bill types. Exceptions are suitable for unexpected errors, while return codes can be considered for frequent predictable errors.
