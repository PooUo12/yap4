#include "mem.h"
#include "tests.h"
#include <stdint.h>
#include <string.h>

int main() {
    int32_t counter = 0;
    counter += test1();
    counter += test2();
    counter += test3();
    counter += test4();
    counter += test5();

    printf("%d/%d tests passed", counter, TESTS);
    return 0;
}