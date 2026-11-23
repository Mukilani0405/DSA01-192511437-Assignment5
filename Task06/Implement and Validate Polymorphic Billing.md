# B1 – Implement and Validate Polymorphic Billing

### 1. Implementation and Validation

The hospital billing system uses an abstract base class `Bill` and derived classes for different bill types. The `total()` and `type()` functions are virtual, allowing runtime polymorphism.

The program uses base-class pointers to process different bill objects through a common interface.

### 2. Expected Test Results

| Patient | Bill Type | Calculation | Total |
|---|---|---|---:|
| Ravi | Out-patient | 500 + 1200 | 1700 |
| Meena | In-patient | (3 × 2500) + 40000 | 47500 |
| | **Combined Total** | 1700 + 47500 | **49200** |

### 3. Comparison with Part A Design

The implementation follows the Part A design by using an abstract `Bill` class, derived bill classes, virtual functions and a virtual destructor.

The program uses `Bill*` pointers to access derived-class objects. This confirms that different bill types can be processed using one common interface.

### 4. Runtime Binding Test

When `virtual` is removed from `total()`, the function no longer supports runtime polymorphism. The derived classes cannot correctly override the base-class function, and the program produces a compilation error because the base-class function is still pure virtual.

### 5. Virtual Destructor Test

The virtual destructor ensures that the derived-class destructor is called when a derived object is deleted through a base-class pointer.

Removing `virtual` from the base destructor makes deletion through a base-class pointer undefined behaviour. The AddressSanitizer test is used to investigate this issue.

### 6. Alternative Concept – Templates

Templates can process each bill type at compile time without virtual function calls.

- **Time:** O(1) dispatch per bill, without a virtual call.
- **Space:** Separate containers may be required for different bill types.
- **Limitation:** Keeping all bill types together in one common list becomes more difficult.

### Result

The implementation demonstrates runtime polymorphism through base-class pointers. The virtual destructor supports safe object destruction, and the calculated bill totals are verified against the expected values.
