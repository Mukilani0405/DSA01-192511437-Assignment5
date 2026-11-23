# Task B4 – Final Engineering Decision

### 1. Adding New Bill and Payer Types

The system uses abstract base classes named `Bill` and `Payer`.

A new bill type can be added by creating a derived class and implementing the `total()` function.

A new payer type can be added by creating a derived class and implementing the `amountCovered()` function.

For example:

- `LaboratoryBill` can be added as a new bill type.
- `CorporatePayer` can be added as a new payer type.

Existing classes do not need to be modified. This demonstrates extensibility through runtime polymorphism.

### 2. Reliability and Memory Safety

The system uses exception handling to manage invalid charges and claim errors.

AddressSanitizer is used to detect memory-related problems such as memory leaks and invalid memory access.

A virtual destructor in the base classes ensures safe destruction of derived objects through base-class pointers.

RAII helps release resources automatically when exceptions occur.

### 3. Production Engineering Decision

For a system used by 15 hospitals, processing 200,000 bills per day, and adding two bill types and three payer types every year, the following design is selected:

- Use abstract base classes and virtual functions for bill and payer types.
- Use custom exceptions for unexpected errors and invalid operations.
- Use return codes for frequent predictable validation failures when appropriate.
- Use RAII for safe resource management.
- Store package rates and policy limits in configuration or database tables.
- Perform testing and benchmarking before deployment.

### 4. Alternative Approach – Plugins and Configuration

A plugin-based design can load new bill and payer types dynamically. Configuration files or database tables can store package prices and insurance limits.

This reduces the need to modify the main application for changes in rates. However, plugin management and validation require additional care.

### Result

The polymorphic billing system provides flexibility, extensibility, and reliable error handling. It is suitable as a foundation for a multi-hospital billing application when combined with proper testing, security, and database management.
