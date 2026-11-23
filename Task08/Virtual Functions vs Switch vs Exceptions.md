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

The billing methods were tested using two million bills (one million of each bill type) with compiler optimization.

| Number of bills | Virtual functions | Switch statement |
|---|---:|---:|
| 2,000,000 | 104 ms | 14 ms |

The switch statement was faster in this particular experiment. Actual performance depends on the compiler, processor, and system load.

### 4. Exception vs Return Code Benchmark

One million claims were tested with different invalid-claim percentages.

| Invalid claims | Exceptions | Return codes |
|---|---:|---:|
| 0% | 28 ms | 73 ms |
| 1% | 102 ms | 21 ms |
| 50% | 1595 ms | 55 ms |

The results show that exceptions become expensive when errors occur frequently. Return codes performed better at 1% and 50% invalid claims. At 0%, exceptions were faster in this particular run.

### 5. Engineering Trade-off

| Method | Advantages | Limitations |
|---|---|---|
| Virtual functions | Flexible and easy to extend | Has virtual dispatch overhead |
| Switch statement | Simple and direct | Requires modification when adding new types |
| Exceptions | Separates error handling from normal logic | Error handling can be costly |
| Return codes | Suitable for frequent predictable errors | Requires checking every result |

### 6. Alternative Approach – `std::variant` and `std::visit`

`std::variant` can store different bill types, and `std::visit` can select the appropriate calculation.

It provides type safety and avoids traditional virtual inheritance. Its performance and memory usage can be measured using the same billing test data.

### Result

Virtual functions provide flexibility for extending the hospital billing system. Switch statements performed faster in our measured test. Exceptions are useful for unexpected errors, while return codes are suitable for frequent predictable errors.
### Result

Virtual functions provide better flexibility for extending the hospital billing system. Switch statements can be useful for a small fixed set of bill types. Exceptions are suitable for unexpected errors, while return codes can be considered for frequent predictable errors.
