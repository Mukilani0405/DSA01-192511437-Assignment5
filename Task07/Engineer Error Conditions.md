# Task B2 – Engineer Error Conditions

### 1. Error Conditions

The hospital billing system must handle the following errors:

1. **Negative amount:** Rejects negative billing amounts.
2. **Claim exceeds cover:** Rejects insurance claims above the policy limit.
3. **Unknown package:** Displays an error when a package is unavailable.
4. **Invalid numeric input:** `std::stod()` throws `std::invalid_argument` when the input is not a valid number.
5. **Memory allocation failure:** `std::bad_alloc` is thrown when memory allocation fails.

### 2. Exception Handling

The system uses `try`, `throw`, and `catch` statements to detect and handle errors.

- `approve()` checks whether a claim is within the allowed cover.
- `settle()` processes the approved claim.
- Specific catch blocks handle known exceptions.
- A final `catch(...)` block handles unexpected exceptions.

### 3. Expected Output Prediction

```text
approved 40000
audit: exceeds cover
claim rejected: exceeds cover
error: negative amount
```

The first claim is approved. The second claim exceeds the insurance limit and is rejected. The negative amount is also rejected.

### 4. Difference Between `throw;` and `throw e;`

| `throw;` | `throw e;` |
|---|---|
| Rethrows the original exception. | Throws the exception object again. |
| Preserves the original exception type. | May cause object slicing when using a base-class exception reference. |
| Useful for logging and forwarding errors. | Creates a new exception object. |

### 5. Testing and Validation

The following test cases are performed:

- Valid claim within the cover limit.
- Claim exceeding the cover limit.
- Negative billing amount.
- Invalid text input instead of a number.
- Unknown treatment package.
- Memory allocation failure using a very large allocation request.

### 6. Alternative Approach – Optional and Return Codes

Return codes or `std::optional` can be used instead of exceptions for predictable errors.

For a large number of claims, return codes may be efficient when invalid claims are frequent because they avoid exception stack unwinding. Exceptions are useful for unexpected or exceptional failures.

### Result

The billing system uses exception handling to reject invalid claims, report errors, and prevent incorrect billing operations.
