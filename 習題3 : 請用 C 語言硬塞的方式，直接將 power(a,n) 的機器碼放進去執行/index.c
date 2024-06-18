#include <stdio.h>

int power(int a, int n) {
    int result;

    __asm__ (
        "movl $1, %%eax\n\t"      // 初始化 result 為 1
        "movl %1, %%ecx\n\t"      // 將 n 放入 ecx
        "movl %2, %%ebx\n\t"      // 將 a 放入 ebx
        "start_loop:\n\t"
        "cmpl $0, %%ecx\n\t"      // 比較 ecx 是否為 0
        "je end_loop\n\t"         // 如果 ecx 為 0，跳轉到 end_loop
        "imull %%ebx, %%eax\n\t"  // result *= a
        "decl %%ecx\n\t"          // ecx--
        "jmp start_loop\n\t"      // 跳轉回 start_loop
        "end_loop:\n\t"
        "movl %%eax, %0\n\t"      // 將結果放入 result
        : "=r" (result)           // 輸出部分
        : "r" (n), "r" (a)        // 輸入部分
        : "%eax", "%ebx", "%ecx"  // 告訴編譯器哪些暫存器會被用到
    );

    return result;
}

int main() {
    int a = 2;
    int n = 3;
    int result = power(a, n);
    printf("%d^%d = %d\n", a, n, result);
    return 0;
}
