
#include <iostream>
#include <vector>
#include <chrono>
#include <stdexcept>
using namespace std;
using namespace chrono;

volatile long long checksum = 0;

bool validateReturn(bool invalid) {
    return !invalid;
}

void validateException(bool invalid) {
    if (invalid)
        throw runtime_error("Invalid claim");
}

long long benchmark(bool useException, int invalidPercent) {
    const int n = 1000000;
    int invalidCount = n * invalidPercent / 100;
    vector<bool> claims(n, false);

    for (int i = 0; i < invalidCount; i++)
        claims[i] = true;

    auto start = steady_clock::now();

    for (bool invalid : claims) {
        if (useException) {
            try {
                validateException(invalid);
                checksum++;
            }
            catch (const exception&) {
                checksum--;
            }
        } else {
            if (validateReturn(invalid))
                checksum++;
            else
                checksum--;
        }
    }

    auto end = steady_clock::now();

    return duration_cast<milliseconds>(end - start).count();
}

int main() {
    int percentages[] = {0, 1, 50};

    for (int p : percentages) {
        cout << "Invalid claims: " << p << "%\n";

        cout << "Exceptions: "
             << benchmark(true, p) << " ms\n";

        cout << "Return codes: "
             << benchmark(false, p) << " ms\n\n";
    }

    return 0;
}
