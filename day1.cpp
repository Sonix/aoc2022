//
// Created by Johannes Loepelmann on 01.12.22.
//

#include "util.h"

int main() {
    std::vector<int> calories;

    const auto lines = read_strings_from_file("day1.input");

    int current = 0;

    for(const auto &line : lines) {
        if(line.empty()) {
            calories.push_back(current);
            current = 0;
            continue;
        }
        current += std::stoi(line);
    }

    std::sort(calories.begin(), calories.end());

    std::cout << "Best: " << calories.back() << std::endl;

    int sum = 0;

    for(int i = 1; i <= 3; ++i) {
        current = calories.at(calories.size() - i);
        std::cout << "Number " << i << ": " << current << std::endl;
        sum += current;
    }

    std::cout << "Sum: " << sum << std::endl;
}