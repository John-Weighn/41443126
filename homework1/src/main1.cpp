#include <iostream>
#include <cstdlib>
// 1. 遞迴版本
unsigned long long AckermannRecursive(unsigned long long m, unsigned long long n) {
    if (m == 0) {
        return n + 1;
    } 
    else if (n == 0) {
        return AckermannRecursive(m - 1, 1);
    } 
    else {
        return AckermannRecursive(m - 1, AckermannRecursive(m, n - 1));
    }
}
// 2. 非遞迴版本 
unsigned long long AckermannNonRecursive(unsigned long long m, unsigned long long n) {
    const int STACK_SIZE = 4000000;
    unsigned long long* my_stack = new unsigned long long[STACK_SIZE];
    int top_idx = -1;
    my_stack[++top_idx] = m;
    while (top_idx >= 0) {
        m = my_stack[top_idx--];
        if (m == 0) {
            n = n + 1;
        } 
        else if (n == 0) {
            my_stack[++top_idx] = m - 1;
            n = 1;
        } 
        else {
            my_stack[++top_idx] = m - 1; 
            my_stack[++top_idx] = m;     
            n = n - 1;
        }
    }
    delete[] my_stack;
    return n;
}

int main() {
    unsigned long long user_m, user_n;

    std::cout << "請輸入 m 的值: ";
    std::cin >> user_m;
    std::cout << "請輸入 n 的值: ";
    std::cin >> user_n;
    // 呼叫非遞迴版
    std::cout << "[非遞迴版] A(" << user_m << ", " << user_n << ") = ";
    std::cout << AckermannNonRecursive(user_m, user_n) << std::endl;
    // 呼叫遞迴版
    std::cout << "[遞迴版] A(" << user_m << ", " << user_n << ") = ";
    std::cout << AckermannRecursive(user_m, user_n) << std::endl;
    return 0;
}
