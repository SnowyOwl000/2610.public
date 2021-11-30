//
// Created by rwkramer on 11/30/21.
//

#include "BigNumber.h"
#include "rns.h"

int64_t
    moduli[] = {
        2147483647, 2147483629, 2147483587, 2147483579,
        2147483563, 2147483549, 2147483543, 2147483497,
        2147483489, 2147483477, 2147483423, 2147483399,
        2147483353, 2147483323, 2147483269, 2147483249,
        2147483237, 2147483179, 2147483171, 2147483137,
        2147483123, 2147483077, 2147483069, 2147483059,
        2147483053, 2147483033, 2147483029, 2147482951,
        2147482949, 2147482943, 2147482937, 2147482921
    };


BigNumber::BigNumber() {

    for (long & i : data)
        i = 0;
}

BigNumber::~BigNumber() { }

void BigNumber::set(int64_t v) {

    for (int i=0;i<N_MODULI;i++)
        data[i] = v % moduli[i];
}

void BigNumber::add3(const BigNumber &a, const BigNumber &b) {

    for (int i=0;i<N_MODULI;i++)
        data[i] = (a.data[i] % moduli[i] + b.data[i] % moduli[i])
                % moduli[i];
}

void BigNumber::add2(const BigNumber &a) {

    for (int i=0;i<N_MODULI;i++)
        data[i] = (data[i] % moduli[i] + a.data[i] % moduli[i])
                  % moduli[i];
}

void BigNumber::sub3(const BigNumber &a, const BigNumber &b);
void BigNumber::sub2(const BigNumber &a);

void BigNumber::mul3(const BigNumber &a, const BigNumber &b);
void BigNumber::mul2(const BigNumber &a);

void BigNumber::divide(int64_t d) {

    for (int i=0;i<N_MODULI;i++)
        data[i] = ((data[i] % moduli[i]) * findInverse(d,moduli[i]))
                  % moduli[i];
}

std::string BigNumber::toString() {

    return rnsToString(data,moduli,N_MODULI);
}
