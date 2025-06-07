void byValue(int *p) {
    cout << "Address of p in byValue: " << &p << endl;  // address of local pointer variable
    cout << "Value stored in p (should be address of a): " << p << endl;
    *p = 1;
}

int main() {
    int a = 3;
    int *p2 = &a;

    cout << "Address of p2 in main: " << &p2 << endl;   // address of main's pointer variable
    cout << "Value stored in p2 (address of a): " << p2 << endl;

    byValue(p2);

    return 0;
}

/**
 * Address of p2 in main: 0x7ffeefbff5c8
 * Value stored in p2 (address of a): 0x7ffeefbff5bc
 * Address of p in byValue: 0x7ffeefbff588
 * Value stored in p (should be address of a): 0x7ffeefbff5bc
 */