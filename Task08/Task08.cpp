
#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
using namespace std;
using namespace chrono;

struct Bill {
    virtual double total() const = 0;
    virtual ~Bill() = default;
};

struct OPBill : Bill {
    double amount;
    OPBill(double a) : amount(a) {}
    double total() const override { return amount; }
};

struct IPBill : Bill {
    double amount;
    IPBill(double a) : amount(a) {}
    double total() const override { return amount; }
};

double switchTotal(int type, double amount) {
    switch (type) {
        case 0: return amount;
        case 1: return amount;
        default: return 0;
    }
}

int main() {
    vector<OPBill> op;
    vector<IPBill> ip;

    const int n = 1000000;

    for (int i = 0; i < n; i++) {
        op.emplace_back(100 + i % 100);
        ip.emplace_back(200 + i % 100);
    }

    vector<Bill*> bills;
    vector<int> types;
    vector<double> amounts;

    for (int i = 0; i < n; i++) {
        bills.push_back(&op[i]);
        types.push_back(0);
        amounts.push_back(op[i].amount);

        bills.push_back(&ip[i]);
        types.push_back(1);
        amounts.push_back(ip[i].amount);
    }

    volatile double result = 0;

    auto start = steady_clock::now();
    for (Bill* b : bills)
        result += b->total();
    auto end = steady_clock::now();

    cout << "Virtual time: "
         << duration_cast<milliseconds>(end - start).count()
         << " ms\n";

    start = steady_clock::now();
    for (size_t i = 0; i < amounts.size(); i++)
        result += switchTotal(types[i], amounts[i]);
    end = steady_clock::now();

    cout << "Switch time: "
         << duration_cast<milliseconds>(end - start).count()
         << " ms\n";

    cout << "Check total: " << result << '\n';

    return 0;
}
