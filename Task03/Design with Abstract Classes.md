# TASK A3 – DESIGN WITH ABSTRACT CLASSES

## A3.1 – Payer Interface (3 Marks)

An abstract class `Payer` is designed to represent different payment methods in the hospital billing system.

It contains a pure virtual function:

```cpp
virtual double amountCovered(const Bill& bill) const = 0;
```

**Derived Classes:**

1. **SelfPay:** The patient pays the entire bill amount.
2. **Insurance:** Pays according to the policy cover limit and co-payment percentage.
3. **GovernmentScheme:** Pays according to fixed package rates.

**Class Design:**

```text
             Payer (Abstract)
                    |
        -------------------------
        |           |           |
     SelfPay    Insurance   GovernmentScheme
```

**Explanation:**

The `Payer` class provides a common interface for all payment methods. Each derived class implements `amountCovered()` according to its payment rules.

## A3.2 – Extension (2 Marks)

A new payer such as `CorporatePayer` can be added by inheriting the `Payer` class and implementing the `amountCovered()` function.

No changes are required in the existing `SelfPay`, `Insurance` or `GovernmentScheme` classes.

**Example:**

```cpp
class CorporatePayer : public Payer {
public:
    double amountCovered(const Bill& bill) const override {
        return bill.total() * 0.80;
    }
};
```

This payer covers 80% of the bill amount.

## ALTERNATIVE CONCEPT AND COMPLEXITY ANALYSIS

Instead of an abstract Payer class, function pointers or `std::function` can be used to select the payment policy at runtime.

**Alternative Pseudocode:**

```text
BEGIN

SELECT payment policy

IF SelfPay
    Pay full bill amount

ELSE IF Insurance
    Apply cover limit and co-payment

ELSE IF GovernmentScheme
    Apply fixed package rate

END IF

END
```

**Comparison:**

| Factor | Abstract Payer Class | Function Pointer / std::function |
|---|---|---|
| Time per call | O(1) | O(1) |
| Space | Object and virtual table pointer | Function object and stored data |
| Data storage | Stored in derived-class objects | Stored separately with the function |
| Extension | Add a derived class | Add a new policy function |

**Conclusion:**

Both approaches support runtime selection of payment policies. However, an abstract Payer class provides better organization and makes it easier to manage different payment methods in a large hospital system.
