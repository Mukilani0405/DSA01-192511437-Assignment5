# TASK A1 – DESIGN THE POLYMORPHIC BILL HIERARCHY

## A1.1 – Identify the Common Interface

The hospital billing system generates different types of bills, such as Out-Patient, In-Patient, Day-Care Surgery and Emergency bills.

Every bill should provide the following common operations:

1. `total() const` – Calculates and returns the total bill amount.
2. `type() const` – Returns the type of bill.
3. `print() const` – Displays the bill details.

**Common data members:**
- Patient name
- Bill number

These common operations and data members provide a standard interface for processing different bills.

## A1.2 – Design the Hierarchy

An abstract base class named `Bill` is created with pure virtual functions. Four derived classes implement the bill calculation according to their requirements.

**Class hierarchy:**

- `Bill` – Abstract base class.
  - `OutPatientBill` – Calculates consultation and test charges.
  - `InPatientBill` – Calculates room charges, procedures and medicine charges.
  - `DayCareBill` – Calculates the fixed package price.
  - `EmergencyBill` – Calculates the base charge and time-based charges.

**Virtual functions:**
- `total() const` – Pure virtual function in `Bill`, overridden in all derived classes.
- `type() const` – Virtual function in `Bill`, overridden in all derived classes.
- `print() const` – Common function that uses the virtual functions.

**UML Class Diagram:**

```text
                 <<abstract>>
                     Bill
        -----------------------------
        - patientName
        - billNumber
        -----------------------------
        + total() const : double
          {pure virtual}
        + type() const : string
          {virtual}
        + print() const : void
        -----------------------------
                     |
       --------------|-------------------------
       |             |             |           |
       v             v             v           v
 OutPatientBill  InPatientBill  DayCareBill  EmergencyBill
 -------------   -------------  -----------  -------------
 - consultation  - days         - package    - baseCharge
 - testCharges   - roomRate     - price       - timeCharges
                 - procedures
                 - medicines
 -------------   -------------  -----------  -------------
 + total()       + total()      + total()     + total()
   override        override       override      override
 + type()        + type()       + type()      + type()
   override        override       override      override
```

**Bill calculation:**

- Out-Patient: Consultation charges + Test charges
- In-Patient: (Number of days × Room rate) + Procedure charges + Medicine charges
- Day-Care: Package price
- Emergency: Base charge + Time-based charges

## A1.3 – Process All Bills Together

**Pseudocode: Calculate the total amount of all bills**

```text
ALGORITHM Calculate_Day_Total

BEGIN
    DECLARE bills as array of Bill pointers
    DECLARE n, i as INTEGER
    DECLARE dayTotal as REAL

    SET dayTotal = 0

    FOR i = 0 TO n - 1 DO
        dayTotal = dayTotal + bills[i]->total()
    END FOR

    DISPLAY "Total collection for the day:", dayTotal
END
```

The array contains pointers to different derived bill objects. The `total()` function is called through the base-class pointer. Runtime polymorphism automatically executes the correct overridden function for each bill.

## Alternative Concept and Complexity Analysis

An alternative method is to use a single `Bill` structure with a type field and a `switch` statement inside the `total()` function.

**Example logic:**

```text
SWITCH bill.type
    CASE OUTPATIENT:
        Calculate consultation + tests
    CASE INPATIENT:
        Calculate room + procedure + medicine charges
    CASE DAYCARE:
        Calculate package price
    CASE EMERGENCY:
        Calculate base + time charges
END SWITCH
```

**Comparison:**

| Factor | Polymorphism | Structure with switch |
|---|---|---|
| Time complexity | O(n) | O(n) |
| Processing | Virtual function call | Switch statement |
| Space per bill | O(1) | O(1) |
| Adding a new bill type | Add a new derived class | Modify the structure and switch |
| Maintenance | Easier to extend | Becomes harder as types increase |

**Conclusion:**

The abstract base class with runtime polymorphism is a better design for the hospital billing system because it supports different bill types through a common interface. New bill types can be added by creating derived classes without modifying the existing bill-processing loop.
