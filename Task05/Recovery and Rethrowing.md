# Task A5 – Recovery and Rethrowing

### 1. Exception Handling and Recovery

Exceptions should be caught at the appropriate level:

- **Validation functions:** Detect invalid charges and billing data.
- **Billing service:** Catch billing-related exceptions, record the error, and rethrow when higher-level handling is required.
- **Main function:** Catch the exception and display a user-friendly error message.

The `throw;` statement rethrows the currently handled exception without changing its original type.

### 2. Stack Unwinding and RAII

Stack unwinding occurs when an exception moves out of a function. Local objects are automatically destroyed in reverse order of their creation.

RAII (Resource Acquisition Is Initialization) manages resources using object constructors and destructors. It helps release memory and other resources automatically, even when an exception occurs.

### 3. Predict the Output

When `f()` throws the integer `42`:

1. The local object `Guard g("f")` is destroyed.
2. The local object `Guard m("main")` is destroyed.
3. The `catch` block handles the exception and prints `caught 42`.
4. The statement `not printed` is skipped.

**Expected output:**

```text
~f ~main caught 42
```

### 4. Alternative Approach – Manual Resource Management

| RAII | Manual Resource Management |
|---|---|
| Resources are released automatically. | Resources must be released manually. |
| Uses constructors and destructors. | Uses explicit cleanup statements. |
| Reduces memory leaks. | May cause memory leaks if cleanup is missed. |
| Requires less error-handling code. | Requires cleanup in multiple catch blocks. |

Both approaches have similar basic execution-time complexity, but RAII reduces code duplication and makes resource management safer.

### Result

Exception recovery and rethrowing help the billing system handle errors at the correct level. Stack unwinding and RAII ensure that resources are released safely when exceptions occur.
