#include <bits/stdc++.h>

int Sum(int n) {
    int res = n % 10;
    if(n == 0) return 0;
    n = n / 10;
    return Sum(n) + res;
}

int main() {
    int num;
    std::cin >> num;
    std::cout << Sum(num);
}