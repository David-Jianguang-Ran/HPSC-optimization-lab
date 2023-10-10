//
// Created by dran on 10/9/23.
//
#include <iostream>

#include "../src/ContiguousArray.h"

void test_array_read() {
    // test one, all zero
    Contiguous2DArray<int> test_obj(10, 10, true);

    for (int i = 1; i <= 10; ++i) {
        for (int j = 1; j <= 10; ++j) {
            if (test_obj.at(i, j) != 0) {
                std::cout << "[test_array_read] Test Failed, value should be 0 but is:" << test_obj.at(i, j) << std::endl;
            }
        }
    }

    // test two, sequential
    Contiguous2DArray<int> test_obj_again(10, 10);
    for (int i = 0; i < 100; ++i) {
        test_obj_again.content[i] = i;
    }

    for (int i = 1; i <= 10; ++i) {
        for (int j = 1; j <= 10; ++j) {
            if (test_obj_again.at(i, j) != (j - 1) + (i - 1) * 10) {
                std::cout << "[test_array_read] Test Failed, value should be " << ((j - 1) + (i - 1) * 10) << " but is:" << test_obj_again.at(i, j) << std::endl;
            }
        }
    }
}

void test_array_write() {
    // test two, sequential
    Contiguous2DArray<int> test_obj_again(10, 10);

    for (int j = 1; j <= 10; ++j) {
        for (int i = 1; i <= 10; ++i) {
            test_obj_again.at(j,i) = (i - 1) + (j - 1) * 10;
        }
    }

    for (int i = 0; i < 100; ++i) {
        if (test_obj_again.content[i] != i) {
            std::cout << "[test_array_write] Test Failed, value should be " << i << " but is:" << test_obj_again.content[i] << std::endl;
        }
    }
}

int main(int argc, char** argv) {
    test_array_write();
    test_array_read();
    return 0;
}