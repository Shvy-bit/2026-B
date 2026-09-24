#include <iostream>
int fib(int n) {
    long long  ant = 1, out = 1;
    for (int i = 1; i < n; i++) {
        out += ant;
        ant -= out;
        ant *= -1;
    }
    return out;
}
int main () {

    for (int i = -5; i < 50; i++) {
        std::cout << i << ": " << fib(i - 1) << std::endl;

    }
    return 0;
}