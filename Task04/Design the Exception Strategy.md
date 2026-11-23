# Task A4 – Design the Exception Strategy

### 1. Errors in the Hospital Billing System

The following errors may occur:

1. **Negative charges:** Bill amount or service charge is less than zero.
2. **Claim above cover:** Insurance claim exceeds the patient's policy limit.
3. **Unknown package:** Requested treatment package is not available.
4. **Missing patient record:** Patient details are not found in the database.
5. **Memory allocation failure:** Memory allocation fails, causing `std::bad_alloc`.

### 2. Exception Hierarchy

The system uses custom exceptions derived from `std::exception`.

```text
std::exception
      |
  BillingError
   /    |      \
InvalidChargeError
MissingPatientError
UnknownPackageError

std::exception
      |
  ClaimError
      |
 ClaimLimitError
```

This hierarchy helps identify and handle different billing errors separately.

### 3. Functions That May Throw Exceptions

- `validateCharge()` – throws an exception for negative charges.
- `findPatient()` – throws an exception if the patient record is missing.
- `calculateTotal()` – may throw an exception for invalid billing data.
- `approveClaim()` – throws an exception if the claim exceeds the insurance limit.
- Memory allocation – may throw `std::bad_alloc`.

Destructors and cleanup functions should not throw exceptions. Destructors should be non-throwing because throwing during stack unwinding may terminate the program.

### 4. Alternative Approach – Return Codes

Instead of exceptions, the system can use return codes such as:

```cpp
enum Status {
    SUCCESS,
    INVALID_CHARGE,
    CLAIM_EXCEEDED,
    PATIENT_NOT_FOUND
};
```

| Exceptions | Return Codes |
|---|---|
| Error handling uses `try` and `catch`. | Error handling uses status values. |
| Error path involves stack unwinding. | Error path avoids exception unwinding. |
| Normal code is easier to read. | Every function call must be checked. |
| Useful for handling unexpected errors. | Useful for predictable errors. |

Both approaches can perform validation in O(1) time. Exceptions may have additional cost when an error occurs, while return codes require checking and passing error information between functions.

### Result

A structured exception hierarchy makes the hospital billing system easier to maintain and helps handle invalid charges, claim errors, and missing records safely.
