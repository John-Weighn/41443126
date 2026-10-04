# 41443126

資料結構作業：阿克曼函數與冪集

---

# 題目一：阿克曼函數 (Ackermann Function)

## 解題說明
本題要求實作阿克曼函數 \(A(m, n)\)，並分別提供遞迴（Recursive）與非遞迴（Non-recursive）兩種演算法。

### 解題策略
1. **遞迴版本**：完全依照定義的分段函式進行實作。
   - 基準條件：當 \(m = 0\) 時，返回 \(n + 1\)。
   - 當 \(n = 0\) 時，遞迴呼叫 \(A(m-1, 1)\)。
   - 其餘情況（巢狀遞迴），呼叫 \(A(m-1, A(m, n-1))\)。
2. **非遞迴版本**：採用自訂的**動態陣列堆疊（my_stack）**來手動模擬系統遞迴呼叫的 Push 與 Pop 過程，將計算壓力從系統 Stack 轉移到 Heap，有效防止堆疊溢位（Stack Overflow）。

## 程式實作
以下為主要程式碼（僅使用 `<iostream>` 與 `<cstdlib>` 標頭檔）：

```cpp
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
```

## 效能分析
1. **時間複雜度**：阿克曼函數的時間複雜度呈爆炸性增長。對於特定的 \(m\)，其複雜度與超運算（Hyperoperation）相關。例如 \(m=3\) 時為 \(O(2^{n+3})\)，而 \(m=4\) 時時間複雜度呈塔式冪次（Tower of powers），屬於不可原始遞迴的極高複雜度。
2. **空間複雜度**：
   - 遞迴版：系統堆疊深度隨計算規模急遽增加，最壞情況下為 \(O(A(m, n))\)。
   - 非遞迴版：人為限制動態陣列空間，空間複雜度為固定分配的 \(O(\text{STACK\_SIZE})\)。

## 測試與驗證
### 測試案例

| 測試案例 | 輸入參數 (\(m, n\)) | 預期輸出 | 實際輸出 |
| :--- | :--- | :--- | :--- |
| 測試一 | \(m = 1, n = 1\) | 3 | 3 |
| 測試二 | \(m = 2, n = 2\) | 7 | 7 |
| 測試三 | \(m = 3, n = 3\) | 61 | 61 |
| 測試四 | \(m = 4, n = 0\) | 13 | 13 |

---

# 題目二：冪集 (Powerset)

## 解題說明
本題要求實作一個遞迴函式，用來計算一個包含 \(n\) 個元素的集合 \(S\) 的所有可能子集（即冪集 Powerset）。若集合有 \(n\) 個元素，其冪集的元素個數必定為 \(2^n\) 個（包含空集合）。

### 解題策略
1. **二分抉擇思想**：對於集合中的每一個元素，在建立子集時都面臨兩種選擇：「包含此元素」或「不包含此元素」。
2. **遞迴展開**：使用一個 `index` 變數追蹤當前決策的元素。當 `index` 達到集合總長度時，表示完成了一組子集的決策，將其輸出。
3. 透過將 `index + 1` 傳入下一層，分別執行不加入元素的遞迴分支與加入元素的遞迴分支，即可自然遍歷出所有的 \(2^n\) 種組合。

## 程式實作
以下為主要程式碼（僅使用 `<iostream>` 與 `<string>` 標頭檔）：

```cpp
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
```

## 效能分析
1. **時間複雜度**：因為集合中的每個元素都有 2 種選擇，總共會展開成一棵擁有 \(2^n\) 個葉子節點的遞迴樹，因此時間複雜度為 \(O(2^n)\)。
2. **空間複雜度**：遞迴樹的最大深度等於集合內元素的總數 \(n\)，因此系統堆疊的空間複雜度為 \(O(n)\)。

## 測試與驗證
### 測試案例

| 測試案例 | 輸入參數 (\(S\)) | 預期輸出 | 實際輸出 |
| :--- | :--- | :--- | :--- |
| 測試一 | `a` | {} {a} | {} {a} |
| 測試二 | `ab` | {} {b} {a} {ab} | {} {b} {a} {ab} |
| 測試三 | `abc` | {} {c} {b} {bc} {a} {ac} {ab} {abc} | {} {c} {b} {bc} {a} {ac} {ab} {abc} |

---

# 共通編譯與執行指令
```bash
\$ g++ -std=c++17 -o main main.cpp
\$ ./main
```

## 結論
1. 程式能精確模擬阿克曼函數的雙重遞迴，並透過手動建置堆疊成功繞過傳統遞迴帶來的 Stack Overflow 問題。
2. 冪集演算法成功運用二分決策樹的概念，直觀、精簡地輸出所有的子集組合，完全符合數學上的冪集定義。
3. 兩題程式皆在高度限制標頭檔的情況下順利實作完成，程式結構具有良好的強健性與記憶體釋放機制。

## 申論及開發報告

### 選擇遞迴與非遞迴優化的考量

在本作業中，我們深入探討了遞迴在不同場景下的應用與限制：

1. **語意結構的直觀性**  
   不論是阿克曼函數還是冪集問題，它們在數學上的定義本身就是高度遞迴的。使用遞迴實作可以使程式碼與數學公式高度對應，提高程式碼的閱讀性與開發效率。
2. **堆疊溢位的致命傷與優化**  
   阿克曼函數展示了遞迴最嚴重的缺陷——記憶體堆疊消耗極快。當 $m \ge 4$ 時，系統預設的 Stack 空間根本無法承受。因此，我們在非遞迴版本中手動配置了 Heap 上的大陣列來模擬 Stack。這不僅證明了「所有遞迴都可以改寫為迭代」，也提供了解決大規模遞迴問題的工程實務方案。
3. **二分樹的決策極限**  
   在冪集問題中，遞迴展現了處理樹狀結構（選或不選）的強大優勢。相較於非遞迴的位元遮罩（Bitmask）寫法，遞迴回溯（Backtracking）的邏輯更加純粹，也更適合延伸到更複雜的排列組合題目中。
