#include <iostream>
#include <string>

void computePowerset(const std::string& S, size_t index, std::string current) {
    if (index == S.length()) {
        std::cout << "{" << current << "} ";
        return;
    }
    // 選擇 1：不包含目前的元素 S[index]，直接進入下一個元素的決定
    computePowerset(S, index + 1, current);
    // 選擇 2：包含目前的元素 S[index]，將其加入目前子集後再進入下一個元素
    computePowerset(S, index + 1, current + S[index]);
}

int main() {
    std::string S;
    std::cout << "請輸入集合元素（例如 abc）：";
    std::cin >> S;
    std::cout << "集合 {" << S << "} 的冪集為：" << std::endl;
    // 從第 0 個元素開始，初始子集為空字串 ""
    computePowerset(S, 0, "");
    std::cout << std::endl;
    return 0;
}
