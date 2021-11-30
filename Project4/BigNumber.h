//
// Created by rwkramer on 11/30/21.
//

#ifndef PROJECT4_BIGNUMBER_H
#define PROJECT4_BIGNUMBER_H

#include <cstdint>
#include <string>

const int N_MODULI = 32;

class BigNumber {
public:
    BigNumber();
    ~BigNumber();

    void set(int64_t v);

    void add3(const BigNumber &a, const BigNumber &b);
    void add2(const BigNumber &a);

    void sub3(const BigNumber &a, const BigNumber &b);
    void sub2(const BigNumber &a);

    void mul3(const BigNumber &a, const BigNumber &b);
    void mul2(const BigNumber &a);

    void divide(int64_t d);

    std::string toString();

private:
    int64_t
        data[N_MODULI];
};


#endif //PROJECT4_BIGNUMBER_H
