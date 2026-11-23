
#include <iostream>
#include <stdexcept>
using namespace std;

class ClaimError : public runtime_error {
public:
    ClaimError(const string& msg) : runtime_error(msg) {}
};

void approve(double amount, double cover) {
    if (amount < 0)
        throw invalid_argument("negative amount");

    if (amount > cover)
        throw ClaimError("exceeds cover");

    cout << "approved " << amount << '\n';
}

void settle(double amount, double cover) {
    try {
        approve(amount, cover);
    }
    catch (const ClaimError& e) {
        cout << "audit: " << e.what() << '\n';
        throw;
    }
}

int main() {
    try {
        settle(40000, 50000);
        settle(60000, 50000);
    }
    catch (const ClaimError& e) {
        cout << "claim rejected: " << e.what() << '\n';
    }

    try {
        approve(-500, 50000);
    }
    catch (const exception& e) {
        cout << "error: " << e.what() << '\n';
    }

    return 0;
}
