#include <iostream>

using namespace std;

bool isPrime(int64_t n) {

    // if n < 2, it's not prime
    if (n < 2)
        return false;

    // 2 is prime
    if (n == 2)
        return true;

    // the other even numbers are not prime
    if (n % 2 == 0)
        return false;

    // loop over odd integers 3 ... sqrt(n)
    for (int64_t f=3;f*f<=n;f+=2)
        // if it's a factor, n is not prime
        if (n % f == 0)
            return false;

    // n is prime
    return true;
}

int main() {
    int
      n = 2147483647,
      nPrimes;

    for (nPrimes=0;nPrimes<32;) {
        if (isPrime(n)) {
            cout << n << ", ";
            nPrimes++;
        }

        n -= 2;
    }
    return 0;
}
