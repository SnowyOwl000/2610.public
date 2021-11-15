#include <iostream>
#include <cstdlib>
#include <random>
#include <sys/stat.h>
#include <fstream>
#include "codec64.h"

using namespace std;

void usage(char *name) {

    cout << "Usage: " << name << " -k" << endl;
    cout << "       " << name << " -e n e input-file output-file" << endl;
    cout << "       " << name << " -d n d input-file output-file" << endl;

    exit(1);
}

bool isPrime(int64_t n) {

    // if n < 2, it's not prime

    // 2 is prime

    // the other even numbers are not prime

    // loop over odd integers 3 ... sqrt(n)
    for (int64_t f=3;f*f<=n;f+=2)
        // if it's a factor, n is not prime

    // n is prime
    return true;
}

//=============================================================
// int64_t modInverse(int64_t a,int64_t n)
//  calculate b such that (a * b) % n == 1
//
// Parameters
// a - value to find the inverse of
// n - the modulus
//
// returns
// b such that (a * b) % n == 1
//
// see Wikipedia article on Extended Euclidean Algorithm
// for more info
//

int64_t modInverse(int64_t a,int64_t n) {
    int64_t
        r=n,rNew=a,
        t=0,tNew=1,
        q,
        tmp;

    while (rNew != 0) {
        q = r / rNew;

        // (r,rNew) = (rNew,r-rNew*q)
        tmp = rNew;
        rNew = r - rNew * q;
        r = tmp;

        // (t,tNew) = (tNew,t-tNew*q)
        tmp = tNew;
        tNew = t - tNew * q;
        t = tmp;
    }

    if (r != 1)
        cout << "Error" << endl;

    if (t < 0)
        t += n;

    return t;
}

int32_t getFileSize(char *fileName) {
    struct stat
        st{};

    stat(fileName,&st);

    return st.st_size;
}

int64_t modExp(int64_t base,int64_t exp,int64_t mod) {
    int64_t
        ans = 1;

    while (exp != 0) {
        if (exp % 2 == 1)
            ans = (ans * base) % mod;

        base = (base * base) % mod;

        exp = exp / 2;
    }

    return ans;
}

void keyGen() {
    random_device
        rd;         // source of randomness
    mt19937
        mt(rd());   // random number generator
    uniform_int_distribution<>
        dis(4096,65535);           // the range we want
    int64_t
        p,q,
        n,f,
        d,e;

    cout << "keyGen()" << endl;

    // choose prime number p with 4096 <= p < 65536
    do {
        p = dis(mt);
    } while (!isPrime(p));

    // choose prime number q with 4096 <= q < 65536 and p != q

    // calculate n = p * q

    // calculate f = (p - 1) * (q - 1)

    // choose e such that (a) 4096 <= e < 65536 and
    // (b) gcd(e,f) == 1

    // calculate d such that (d * e) % f == 1
    d = modInverse(e,f);

    // output
}

void encrypt(char *inFileName,char *outFileName,int64_t n,int64_t e) {
    ifstream
        inFile;
    Codec64
        codec;
    uint32_t
        fileSize,
        plain,
        cipher;
    uint8_t
        c1,c2,c3;

    // open input file... and make sure that worked
    inFile.open(inFileName);

    // 3 ways to verify:
    // if (!inFile) ... open failed
    // if (!inFile.is_open()) ... open failed
    // if (inFile.fail()) ... open failed
    if (!inFile) {
        cout << "Error: Cannot open input file '"
            << inFileName << "'" << endl;
        return;
    }

    // use codec to open output and prepare for encoding
    codec.beginEncode(outFileName);

    // get file size, encode it and send to output
    fileSize = getFileSize(inFileName);
    codec.put32(fileSize);

    // loop until all bytes read... for loop
    for (uint32_t count=0;count<fileSize;count+=3) {

        // read three bytes
        c1 = inFile.get();
        // read the other two bytes
        c2 = inFile.get();
        c3 = inFile.get();

        // encrypt the three bytes
        plain = c1 + 256 * c2 + 65536 * c3;
        cipher = modExp(plain,e,n);

        // feed encrypted value to codec
        codec.put32(cipher);

    // end of loop
    }

    // tell codec we're done
    codec.endEncode();

    // close input file
    inFile.close();
}

void decrypt(char *inFileName,char *outFileName,int64_t n,int64_t d) {

    cout << "decrypt()" << endl;
    cout << "Input: " << inFileName << endl;
    cout << "Output: " << outFileName << endl;
    cout << "n: " << n << "   d: " << d << endl;

    // open output file and verify

    // tell codec to prepare for decoding

    // get file size from codec

    // loop until all bytes written back... use for loop

        // get cipher from codec

        // decrypt cipher

        // split plain into c1, c2, c3
        c1 = plain % 256;
        plain /= 256;

        c2 = plain % 256;
        plain /= 256;

        c3 = plain % 256;

        // output c1

        // maybe output c2

        // maybe output c3

    // end loop

    // tell codec we're done

    // close output file
}

int main(int argc,char *argv[]) {
    int64_t
        n,e,d;

    // make sure there are at least two things on cmd line

    if (argc < 2)
        usage(argv[0]);

    // second item first char must be -
    if (argv[1][0] != '-')
        usage(argv[0]);

    // what's the second item second char?
    switch (argv[1][1]) {
        case 'k':
            // key generation

            // only two things on cmd line
            if (argc != 2)
                usage(argv[0]);

            keyGen();

            break;
        case 'e':
            // encryption

            // must have 6 things on cmd line
            if (argc != 6)
                usage(argv[0]);

            // convert numbers to numeric form
            n = atoi(argv[2]);
            e = atoi(argv[3]);

            encrypt(argv[4],argv[5],n,e);

            break;
        case 'd':
            // decryption

            // must have 6 things on cmd line
            if (argc != 6)
                usage(argv[0]);

            // convert numbers to numeric form
            n = atoi(argv[2]);
            d = atoi(argv[3]);

            decrypt(argv[4],argv[5],n,d);

            break;
        default:
            usage(argv[0]);
    }

    return 0;
}