#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
 * Calculate number of bits in a number
 */
int numOfBits(int num){
    int size = 0;

    while(num != 0){
        num = num >> 1;
        size++;
    }

    return size;
}

/*
 * Calculate a^b mod n
 */
long long square_multiply(long long base, long long exp, long long mod) {
    int size = numOfBits(exp);
    vector<int> bits;

    for (int i = 0; i < size; i++) {
        bits.push_back((exp >> i) & 1);
    }
    reverse(bits.begin(), bits.end());

    long long c = 0;
    long long d = 1;

    for(int i = 0; i < size; i++){
        c = 2 * c;
        d = (d * d) % mod;
        if(bits[i] == 1){
            c = c + 1;
            d = (d * base) % mod;

        }
    }

    return d;
}

/*
 * The extended Euclidean algorithm
 */
int gcdExtended(int a, int b, int *x, int *y) {
    if (a == 0)
    {
        *x = 0;
        *y = 1;
        return b;
    }

    int x1, y1;
    int gcd = gcdExtended(b%a, a, &x1, &y1);

    *x = y1 - (b/a) * x1;
    *y = x1;

    return gcd;
}

/*
 * Calculate Modular inverse
 */
int  modInverse(int d, int mod) {
    int x, y;

    gcdExtended(d, mod, &x, &y);

    int res = (x % mod + mod) % mod;

    return res;
}

/*
 * Check if a number is a prime number
 */
bool checkPrime(int p) {
    if (p <= 1) {
        return false;
    }

    for (int i = 2; i < p; i++) {
        if ((p % i) == 0) {
            return false;
        }
    }

    return true;
}

/*
 * Returns true if the gcd of a and phi is 1 to
 * calc e
 */
bool calcE(int a, int phi) {
    int x = 0, y;
    if (gcdExtended(a, phi, &x, &y) == 1) {
        return true;
    }

    return false;
}

/*
 * Set p based on whether in auto or manual mode
 */
int setp(int mode) {
    int p = 0;

    if (mode == 1) { //Auto
        while (true) {
            p = rand() % 100 + 3;

            if (checkPrime(p)) {
                break;
            }
        }
    } else if (mode == 2) { //Manual
        while (true) {
            cout << "Enter first prime num:" << endl;
            cin >> p;

            if (checkPrime(p) && p <= 100) {
                break;
            }

            cout << "Num entered is not a prime num!" << endl;
        }
    }

    return p;
}

/*
 * Set q based on whether in auto or manual mode
 */
int setq(int mode, int p) {
    int q = 0;

    if (mode == 1) { //Auto
        while (true) {
            q = rand() % 100 + 3;

            if (checkPrime(q) && q != p) {
                break;
            }
        }
    } else if (mode == 2) { //Manual
        while (true) {
            cout << "Enter second prime num:" << endl;
            cin >> q;

            if (checkPrime(q) && q != p && q <= 100) {
                break;
            }

            cout << "Num entered is not a prime num or is equal to first num!" << endl;
        }
    }

    return q;
}

/*
 * Set e value
 */
int sete(int phi) {
    vector<int> eList;

    //Create list of all valid e values
    for (int i = 0; i < phi; i++) {
        if (calcE(i, phi)) {
            eList.push_back(i);
        }
    }

    int option, e;

    //Choose whether to choose e randomly from the list or manually
    while (true) {
        cout << "1) Random" << endl;
        cout << "2) Manual" << endl;
        cout << "Choose mode: " << endl;

        bool flag = false;
        cin >> option;

        switch (option) {
            case 1: { //Random mode
                int i = rand() % eList.size();

                e = eList[i];

                flag = true;
                break;
            }
            case 2: { //Manual mode
                for (int i = 0; i < eList.size(); i++) {
                    cout << "Valid Values of e:" << endl;
                    cout << "\t" << eList[i] << endl;
                }

                while (true) {
                    bool f = false;

                    cout << "Choose a valid num of e from the list:" << endl;
                    cin >> e;

                    for (int i = 0; i < eList.size(); i++) {
                        if (e == eList[i]) {
                            f = true;
                        }
                    }

                    if (f) {
                        break;
                    }

                    cout << "Num entered is not a valid num!" << endl;
                }
                flag = true;
                break;
            }
            default:
                cout << "Incorrect option choosen!" << endl << endl;
                break;
        }

        if (flag) {
            break;
        }
    }

    return e;
}

/*
 * Set message to encrypt randomly or manually
 */
int setm(int n) {
    int m;
    int option;

    while (true) {
        cout << "1) Random" << endl;
        cout << "2) Manual" << endl;
        cout << "Choose mode: " << endl;

        bool flag = false;
        cin >> option;

        switch (option) {
            case 1: { //Randomly
                m = rand() % n + 1;

                flag = true;
                break;
            }
            case 2: { //Manually
                while (true) {
                    bool f = false;

                    cout << "Enter message in decimal no larger then " << n << endl;
                    cin >> m;

                    if (0 < m && m < n) {
                        f = true;
                    }

                    if (f) {
                        break;
                    }

                    cout << "Message entered is not valid!" << endl;
                }
                flag = true;
                break;
            }
            default:
                cout << "Incorrect option choosen!" << endl << endl;
                break;
        }

        if (flag) {
            break;
        }
    }

    return m;
}

/*
 * Set encrypted message to decrypted randomly or manually
 */
int setc(int n) {
    int c;
    int option;

    while (true) {
        cout << "1) Random" << endl;
        cout << "2) Manual" << endl;
        cout << "Choose mode: " << endl;

        bool flag = false;
        cin >> option;

        switch (option) {
            case 1: { //Random
                c = rand() % n + 1;

                flag = true;
                break;
            }
            case 2: { //Manually
                while (true) {
                    bool f = false;

                    cout << "Enter encrypted message in decimal no larger then " << n << endl;
                    cin >> c;

                    if (0 < c < n) {
                        f = true;
                    }

                    if (f) {
                        break;
                    }

                    cout << "Encrypted message entered is not valid!" << endl;
                }
                flag = true;
                break;
            }
            default:
                cout << "Incorrect option choosen!" << endl << endl;
                break;
        }

        if (flag) {
            break;
        }
    }

    return c;
}

/*
 * Menu to choose auto or manual
 */
int autoMenu() {
    int option;

    while (true) {
        cout << "1) Auto" << endl;
        cout << "2) Manual" << endl;
        cout << "Choose mode: " << endl;

        bool flag = false;
        cin >> option;

        switch (option) {
            case 1:
            case 2:
                flag = true;
                break;
            default:
                cout << "Incorrect option choosen!" << endl << endl;
                break;
        }

        if (flag) {
            break;
        }
    }

    return option;
}

/*
 * Encrypt and decrypt message
 */
void both() {
    int mode = autoMenu();

    int p = setp(mode);
    int q = setq(mode, p);

    cout << "p = " << p << endl;
    cout << "q = " << q << endl;

    int n = p * q;

    cout << "n = " << n << endl;

    int phi = (p - 1) * (q - 1);

    cout << "phi(n) = " << phi << endl;

    int e = sete(phi);

    cout << "e = " << e << endl;

    int d = modInverse(e, phi);

    cout << "d = " << d << endl;

    int m = setm(n);

    cout << "m = " << m << endl;

    int c = square_multiply(m, e, n);

    cout << "Encrypted Message: " << c << endl;

    m = square_multiply(c, d, n);

    cout << "Decrypted Message: " << m << endl;
}

/*
 * Encryption mode
 */
void encrypt() {
    int mode = autoMenu();

    int p = setp(mode);
    int q = setq(mode, p);

    cout << "p = " << p << endl;
    cout << "q = " << q << endl;

    int n = p * q;

    cout << "n = " << n << endl;

    int phi = (p - 1) * (q - 1);

    cout << "phi(n) = " << phi << endl;

    int e = sete(phi);

    cout << "e = " << e << endl;

    int d = modInverse(e, phi);

    cout << "d = " << d << endl;

    int m = setm(n);

    cout << "m = " << m << endl;

    int c = square_multiply(m, e, n);

    cout << "Encrypted Message: " << c << endl;
}

/*
 * Decryption mode
 */
void decrypt() {
    int mode = autoMenu();

    int p = setp(mode);
    int q = setq(mode, p);

    cout << "p = " << p << endl;
    cout << "q = " << q << endl;

    int n = p * q;

    cout << "n = " << n << endl;

    int phi = (p - 1) * (q - 1);

    cout << "phi(n) = " << phi << endl;

    int e = sete(phi);

    cout << "e = " << e << endl;

    int d = modInverse(e, phi);

    cout << "d = " << d << endl;

    int c = setc(n);

    cout << "c = " << c << endl;

    int m = square_multiply(c, d, n);

    cout << "Decrypted Message: " << m << endl;
}

/*
 * Main menu to choose what to do
 */
int mainMenu() {
    int option;

    while (true) {
        cout << "0) Both" << endl;
        cout << "1) Encrypt" << endl;
        cout << "2) Decrypt" << endl;
        cout << "Choose mode: " << endl;

        bool flag = false;
        cin >> option;

        switch (option) {
            case 0:
            case 1:
            case 2:
                flag = true;
                break;
            default:
                cout << "Incorrect option choosen!" << endl << endl;
                break;
        }

        if (flag) {
            break;
        }
    }

    return option;
}

int exitMenu() {
    int option;

    while(true){
        cout << "0) Restart" << endl;
        cout << "1) Exit" << endl;

        bool flag = false;
        cin >> option;

        switch (option) {
            case 0:
            case 1:
                flag = true;
                break;
            default:
                cout << "Incorrect option choosen!" << endl << endl;
                break;
        }

        if (flag) {
            break;
        }
    }

    return option;
}

int main() {
   srand(time(NULL));

   while(true) {
       switch (mainMenu()) {
           case 0:
               both();
               break;
           case 1:
               encrypt();
               break;
           case 2:
               decrypt();
               break;
       }

       if(exitMenu() == 1){
           break;
       }

       cout << endl;
   }

    return 0;
}