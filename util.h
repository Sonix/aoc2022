//
// Created by Johannes Loepelmann on 01.12.22.
//

#ifndef AOC2022_UTIL_H
#define AOC2022_UTIL_H

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

void print_string_array(const std::vector<std::string>& strings) {
    for (auto &s : strings) {
        std::cout << s << std::endl;
    }
}

std::vector<std::string> read_strings_from_file(std::string_view filename){
    std::vector<std::string> result;
    std::string current;

    std::ifstream input_file(filename);

    if(!input_file.is_open()) {
        std::cerr << "Cant open file." << std::endl;
        throw;
    }

    while(std::getline(input_file, current)) {
        result.push_back(current);
    }
    return result;
}

std::vector<int> read_integers_from_file(std::string_view filename) {
    std::vector<int> result;
    int number;

    std::ifstream input_file(filename);

    if(!input_file.is_open()) {
        std::cerr << "Cant open file." << std::endl;
        throw;
    }

    while(input_file >> number) {
        result.push_back(number);
    }

    return result;
}

const std::string WHITESPACE = " \n\r\t\f\v";

std::string ltrim(const std::string &s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}

std::string rtrim(const std::string &s)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

std::string trim(const std::string &s) {
    return rtrim(ltrim(s));
}


#endif //AOC2022_UTIL_H
