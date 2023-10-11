//
// Created by dran on 10/10/23.
// copy file into src directory then #include "debug_utils.h"
// then you can call the functions to print out matrix or vectors
//

#ifndef HPSC_OPTIMIZATION_LAB_DEBUG_UTILS_H
#define HPSC_OPTIMIZATION_LAB_DEBUG_UTILS_H

#include <vector>
#include <string>
#include <iostream>

void print_2d(std::vector<std::vector<double>>& to_print, std::string& title = "") {
    std::cout << "----------------------------------------------" <<std::endl;
    std::cout << title <<std::endl;
    for (auto &each_row: to_print) {
        for (auto each_element : each_row) {
            std::cout << std::setw(5) << each_element << ", ";
        }
        std::cout << std::endl;
    }
    std::cout << "----------------------------------------------" <<std::endl;
}

void print_2d(std::vector<std::vector<int>>& to_print, std::string& title = "") {
    std::cout << "----------------------------------------------" <<std::endl;
    std::cout << title <<std::endl;
    for (auto &each_row: to_print) {
        for (auto each_element : each_row) {
            std::cout << std::setw(5) << each_element << ", ";
        }
        std::cout << std::endl;
    }
    std::cout << "----------------------------------------------" <<std::endl;
}

void print_as_2d(std::vector<double>& to_print, std::string& title = "", int row_width = 1) {
    std::cout << "----------------------------------------------" <<std::endl;
    std::cout << title <<std::endl;
    int i = 0;
    for (auto each_element : to_print) {
        std::cout << std::setw(5) << each_element << ", ";
        if ((i + 1) % row_width == 0) {
            std::cout << std::endl;
        }
        ++i;
    }
    std::cout << std::endl;
    std::cout << "----------------------------------------------" <<std::endl;
}

#endif //HPSC_OPTIMIZATION_LAB_DEBUG_UTILS_H
