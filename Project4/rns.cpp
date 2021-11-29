//
// Created by bob on 11/25/18.
//

#include <cstring>
#include "rns.h"

int64_t findInverse(int64_t a,int64_t b) {
    int64_t
        q,tmp,x,lastX,bTmp;

    x = 0;
    lastX = 1;
    bTmp = b;

    while (b) {
        q = a / b;

        tmp = b;
        b = a % b;
        a = tmp;

        tmp = x;
        x = lastX - q * x;
        lastX = tmp;
    }

    if (lastX < 0)
        lastX += bTmp;

    return lastX;
}

void rnsToAmrs(const int64_t u[],int64_t v[],int64_t moduli[],uint32_t nModuli) {
    int64_t
        *amrsInv,
        s;

    amrsInv = new int64_t[nModuli];

    for (uint32_t i=0;i<nModuli;i++)
        amrsInv[i] = 1;

    for (uint32_t j=1;j<nModuli;j++) {
        for (int i=0;i<j;i++) {
            amrsInv[j] = (amrsInv[j] * moduli[i]) % moduli[j];
        }
        amrsInv[j] = findInverse(amrsInv[j],moduli[j]);
    }

    for (uint32_t i=0;i<nModuli;i++) {
        s = 1;
        for (uint32_t j=0;j<i;j++)
            s = (s * moduli[j]) % moduli[i];
        s = (s * amrsInv[i]) % moduli[i];
        if (s != 1)
            printf("Error in inverse %d\n",i);
    }

    v[0] = u[0];
    v[1] = (((u[1] - v[0] + moduli[1]) % moduli[1]) *
            amrsInv[1]) % moduli[1];
    for (uint32_t i=2;i<nModuli;i++) {
        v[i] = v[i-1];
        for (int j=i-2;j>=0;j--) {
            v[i] = ((v[i] * moduli[j]) % moduli[i] + v[j]) %
                   moduli[i];
        }
        v[i] = (((u[i] - v[i] + moduli[i]) % moduli[i]) *
                amrsInv[i]) % moduli[i];
    }

    delete[] amrsInv;
}

std::string rnsToString(int64_t data[],int64_t moduli[],uint32_t nModuli) {
    uint32_t
        i,j,
        nBlocks = nModuli+4;
    int64_t
        carry,
        *amrsVal[2],
        *strAccumulator[2],
        *strTerm;
    char
        //block[9],
        *numStr;
    bool isNegative = false;
    std::string s;

    amrsVal[0] = new int64_t[nModuli];
    amrsVal[1] = new int64_t[nModuli];

    strAccumulator[0] = new int64_t[nModuli+4];
    strAccumulator[1] = new int64_t[nModuli+4];

    strTerm = new int64_t[nModuli+4];

    numStr = new char[10*nModuli+1];

    for (i=0;i<nModuli;i++)
        amrsVal[0][i] = 0;
    rnsToAmrs(data,amrsVal[0],moduli,nModuli);

    // negative number
    if (amrsVal[0][nModuli-1] > moduli[nModuli] / 2) {
        for (i=0;i<nModuli;i++)
            amrsVal[0][i] = moduli[i] - 1 - amrsVal[0][i];
        amrsVal[0][0]++;
        carry = 0;
        for (i=0;i<nModuli;i++) {
            amrsVal[0][i] += carry;
            carry = amrsVal[0][i] / moduli[i];
            if (!carry)
                break;
            amrsVal[0][i] %= moduli[i];
        }
        isNegative = true;
    }

    strAccumulator[0][0] = amrsVal[0][nModuli-1] % 100000000;
    strAccumulator[0][1] = (amrsVal[0][nModuli-1] / 100000000) % 100000000;
    strAccumulator[0][2] = (amrsVal[0][nModuli-1] / 100000000) /
                           100000000;
    for (i=3;i<nBlocks;i++)
        strAccumulator[0][i] = 0;

    for (i=nModuli-2;i<nModuli;i--) {
        // multiply accumulator by primes[i]
        carry = 0;
        for (j=0;j<nBlocks;j++) {
            strAccumulator[1][j] = strAccumulator[0][j] * (moduli[i] % 100000000) +
                                   carry;
            carry = strAccumulator[1][j] / 100000000;
            strAccumulator[1][j] %= 100000000;
        }

        strTerm[0] = 0;
        for (j=0;j<nBlocks-1;j++) {
            strTerm[j+1] = strAccumulator[0][j] *
                           ((moduli[i] / 100000000) % 100000000) + carry;
            carry = strTerm[j+1] / 100000000;
            strTerm[j+1] %= 100000000;
        }
        carry = 0;
        for (j=0;j<nBlocks;j++) {
            strAccumulator[1][j] += strTerm[j] + carry;
            carry = strAccumulator[1][j] / 100000000;
            strAccumulator[1][j] %= 100000000;
        }

        strTerm[0] = strTerm[1] = 0;
        for (j=0;j<nBlocks-2;j++) {
            strTerm[j+2] = strAccumulator[0][j] * ((moduli[i] / 100000000) / 100000000) +
                           carry;
            carry = strTerm[j+2] / 100000000;
            strTerm[j+2] %= 100000000;
        }
        carry = 0;
        for (j=0;j<nBlocks;j++) {
            strAccumulator[1][j] += strTerm[j] + carry;
            carry = strAccumulator[1][j] / 100000000;
            strAccumulator[1][j] %= 100000000;
        }

        for (j=0;j<nBlocks;j++)
            strAccumulator[0][j] = strAccumulator[1][j];

        // add amrsVal[0][i] to accumulator

        strAccumulator[0][0] += amrsVal[0][i];
        carry = strAccumulator[0][0] / 100000000;
        strAccumulator[0][0] %= 100000000;
        for (j=1;j<nBlocks;j++) {
            strAccumulator[0][j] += carry;
            carry = strAccumulator[0][j] / 100000000;
            strAccumulator[0][j] %= 100000000;
        }
    }

    size_t pos;
    for (i=nBlocks-1;i>=0;i--)
        if (strAccumulator[0][i])
            break;

    if (i == -1)
        strcpy(numStr,"0");
    else {
        if (isNegative)
            sprintf(numStr,"-%llu",strAccumulator[0][i]);
        else
            sprintf(numStr,"%llu",strAccumulator[0][i]);
        pos = strlen(numStr);
        while (--i < nBlocks) {
            sprintf(numStr+pos,"%08llu",strAccumulator[0][i]);
            pos += 8;
        }
    }

    s = numStr;

    delete[] numStr;

    delete[] strTerm;

    delete[] strAccumulator[1];
    delete[] strAccumulator[0];

    delete[] amrsVal[1];
    delete[] amrsVal[0];

    return s;
}
