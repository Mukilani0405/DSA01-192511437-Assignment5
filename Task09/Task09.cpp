
#include <iostream>
#include <memory>
#include <stdexcept>
using namespace std;

class Bill {
public:
    virtual double total() const = 0;
    virtual ~Bill() = default;
};

class Payer {
public:
    virtual double amountCovered(const Bill& b) const = 0;
    virtual ~Payer() = default;
};

// New bill type
class LaboratoryBill : public Bill {
    double testCharge;

public:
    LaboratoryBill(double amount) : testCharge(amount) {
        if (amount < 0)
            throw invalid_argument("Invalid lab charge");
    }

    double total() const override {
        return testCharge;
    }
};

// New payer type
class CorporatePayer : public Payer {
public:
    double amountCovered(const Bill& b) const override {
        return b.total() * 0.80;
    }
};

int main() {
    try {
        unique_ptr<Bill> bill =
            make_unique<LaboratoryBill>(10000);

        CorporatePayer payer;

        cout << "Bill amount: " << bill->total() << '\n';
        cout << "Corporate coverage: "
             << payer.amountCovered(*bill) << '\n';
        cout << "Remaining amount: "
             << bill->total() - payer.amountCovered(*bill)
             << '\n';
    }
    catch (const exception& e) {
        cout << "Billing error: " << e.what() << '\n';
    }

    return 0;
}
