# TASK A2 – UNDERSTAND RUNTIME BINDING

## A2.1 – Early and Late Binding (2 Marks)

**Early Binding (Compile-Time Binding):**

Early binding is the process in which the function call is decided during compilation. It is commonly used with non-virtual functions. The compiler determines the function based on the pointer or reference type.

**Late Binding (Run-Time Binding):**

Late binding is the process in which the function call is decided during program execution. It is achieved using virtual functions. The actual object type determines which function is executed.

**Example:**

```cpp
Bill* b = new OutPatientBill();
b->total();
```

Here, `Bill` is the base class and `OutPatientBill` is the derived class. Since `total()` is virtual, the derived class implementation is called at runtime.

**Difference between Early and Late Binding:**

| Early Binding | Late Binding |
|---|---|
| Decided during compilation | Decided during execution |
| Uses non-virtual functions | Uses virtual functions |
| Function selection is direct | Function selection uses virtual dispatch |
| Less flexible | Supports runtime polymorphism |

## A2.2 – The Virtual Table (2 Marks)

A virtual table (vtable) is a compiler-generated table that stores the addresses of virtual functions. Each polymorphic object generally contains a hidden pointer called a vptr, which points to its class's virtual table.

**1. Bill Vtable**

| Virtual Function | Entry |
|---|---|
| total() | Pure virtual function |
| Destructor | Bill destructor |

**2. OutPatientBill Vtable**

| Virtual Function | Entry |
|---|---|
| total() | OutPatientBill::total() |
| Destructor | OutPatientBill destructor |

**3. InPatientBill Vtable**

| Virtual Function | Entry |
|---|---|
| total() | InPatientBill::total() |
| Destructor | InPatientBill destructor |

**How Runtime Binding Works:**

1. A base-class pointer `b` points to an OutPatientBill object.
2. The object contains a hidden vptr that refers to its virtual table.
3. When `b->total()` is called, the corresponding virtual function entry is accessed.
4. The correct derived-class function is executed.

**Conceptual Diagram:**

```text
       Bill* b
          |
          v
  OutPatientBill Object
          |
          v
       OutPatientBill Vtable
          |
          v
  OutPatientBill::total()
```

The vtable layout is compiler-dependent. The above diagram represents the basic concept of runtime dispatch.

## A2.3 – Virtual Destructors (1 Mark)

A base class must have a virtual destructor when derived-class objects are deleted through base-class pointers.

Example:

```cpp
Bill* b = new OutPatientBill();
delete b;
```

If the destructor is virtual, the derived-class destructor executes first, followed by the base-class destructor.

If the destructor is not virtual, deleting a derived object through a base-class pointer causes undefined behavior.

Therefore, a virtual destructor is necessary to ensure proper object destruction and resource safety.

## PREDICT THE OUTPUT

**Predicted Output:**

```text
500 ~OPBill ~Bill
```

**Explanation:**

1. The pointer `b` refers to an OPBill object.
2. The function `show()` is non-virtual, but it internally calls the virtual function `total()`.
3. Therefore, `OPBill::total()` executes and returns 500.
4. When `delete b` is executed, the derived-class destructor `~OPBill()` runs first.
5. The base-class destructor `~Bill()` runs next.

Thus, the output is:

```text
500 ~OPBill ~Bill
```

**After Removing Virtual from the Base-Class Destructor:**

If the `virtual` keyword is removed from the base-class destructor, deleting an OPBill object through a Bill pointer causes undefined behavior. The derived-class destructor is not guaranteed to execute. A common observed output may be:

```text
500 ~Bill
```

However, the exact behaviour is not guaranteed because the program has undefined behaviour. AddressSanitizer may not necessarily detect this issue.

**Why did show() reach OPBill::total()?**

The `show()` function is non-virtual, so its implementation is selected using the base-class interface. However, the `total()` function called inside it is virtual. Therefore, runtime binding selects the derived-class implementation.

## ALTERNATIVE CONCEPT AND COMPLEXITY ANALYSIS

If `total()` were not virtual, the program could use `dynamic_cast` to identify the actual bill type and call the appropriate function.

**Alternative Pseudocode:**

```text
BEGIN

IF bill is OutPatientBill
    Calculate outpatient total

ELSE IF bill is InPatientBill
    Calculate inpatient total

ELSE IF bill is DayCareBill
    Calculate day-care total

ELSE IF bill is EmergencyBill
    Calculate emergency total

END IF

END
```

**Comparison:**

| Factor | Virtual Function | Dynamic Cast |
|---|---|---|
| Function selection | Virtual function call | Runtime type checking |
| Time per bill | O(1) | Up to O(k) |
| Space overhead | Usually one vptr per object | No virtual dispatch pointer required for this approach |
| Adding new types | Add a derived class | Modify type-checking code |
| Maintenance | Easier | More complex |

Here, `k` represents the number of bill types.

**Conclusion:**

Virtual functions provide efficient runtime binding through a single virtual call. Using multiple dynamic_cast operations requires repeated type checking. Therefore, virtual functions are more suitable for a hospital billing system with different types of bills because they improve flexibility, maintainability and extensibility.
