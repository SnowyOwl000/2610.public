#include <iostream>
#include <cstdlib>

using namespace std;

void usage(char *name) {

    cout << "Usage: " << name << " -k" << endl;
    cout << "       " << name << " -e n e input-file output-file" << endl;
    cout << "       " << name << " -d n d input-file output-file" << endl;

    exit(1);
}

void keyGen() {

    cout << "You have called keyGen()" << endl;
}

void encrypt(char *inFileName,char *outFileName,int64_t n,int64_t e) {

    cout << "You have called encrypt()" << endl;
    cout << "Input file: " << inFileName << endl;
    cout << "Output file: " << outFileName << endl;
    cout << "n: " << n << "   e: " << e << endl;
}

void decrypt(char *inFileName,char *outFileName,int64_t n,int64_t d) {

    cout << "You have called decrypt()" << endl;
    cout << "Input file: " << inFileName << endl;
    cout << "Output file: " << outFileName << endl;
    cout << "n: " << n << "   d: " << d << endl;
}

int main(int argc,char *argv[]) {
    int64_t
        n,e,d;

    // make sure we have at least two cmd-line parameters

    if (argc < 2)
        usage(argv[0]);

    // in position 1, make sure first char is '-'

    if (argv[1][0] != '-')
        usage(argv[0]);

    // if position 1 second char is k, do key generation

    if (argv[1][1] == 'k') {
        // key generation

        // for key generation, only two things on cmd line

        if (argc != 2)
            usage(argv[0]);

        keyGen();

    } else if (argv[1][1] == 'e') { // check for encryption
        // encrypt

        // make sure there are six things on cmd line

        if (argc != 6)
            usage(argv[0]);

        // convert n and e to number form
        n = atoi(argv[2]);
        e = atoi(argv[3]);

        encrypt(argv[4],argv[5],n,e);

    } else if (argv[1][1] == 'd') { // check for decryption
        // decrypt

        // make sure there are six things on cmd line

        if (argc != 6)
            usage(argv[0]);

        // convert n and e to number form
        n = atoi(argv[2]);
        d = atoi(argv[3]);

        decrypt(argv[4],argv[5],n,d);

    } else
        usage(argv[0]);

    return 0;
}