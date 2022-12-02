//
// Created by Johannes Loepelmann on 02.12.22.
//

#include "util.h"

int main() {
    const auto lines = read_strings_from_file("day2.input");
    int sum = 0;

    for(const auto& line : lines) {
        char opp = line.at(0);
        char me = line.at(2);
        if(opp == 'A' && me == 'X') {
            sum += 4;
        } else if(opp == 'A' && me == 'Y') {
            sum += 8;
        } else if(opp == 'A' && me == 'Z') {
            sum += 3;
        } else if(opp == 'B' && me == 'X') {
            sum += 1;
        } else if(opp == 'B' && me == 'Y') {
            sum += 5;
        } else if(opp == 'B' && me == 'Z') {
            sum += 9;
        } else if(opp == 'C' && me == 'X') {
            sum += 7;
        } else if(opp == 'C' && me == 'Y') {
            sum += 2;
        } else if(opp == 'C' && me == 'Z') {
            sum += 6;
        }
    }

    std::cout << "Sum 1: " << sum << std::endl;

    sum = 0;
    for(const auto& line : lines) {
        char opp = line.at(0);
        char res = line.at(2);
        if(opp == 'A' && res == 'X') {
            sum += 3;
        } else if(opp == 'A' && res == 'Y') {
            sum += 4;
        } else if(opp == 'A' && res == 'Z') {
            sum += 8;
        } else if(opp == 'B' && res == 'X') {
            sum += 1;
        } else if(opp == 'B' && res == 'Y') {
            sum += 5;
        } else if(opp == 'B' && res == 'Z') {
            sum += 9;
        } else if(opp == 'C' && res == 'X') {
            sum += 2;
        } else if(opp == 'C' && res == 'Y') {
            sum += 6;
        } else if(opp == 'C' && res == 'Z') {
            sum += 7;
        }
    }

    std::cout << "Sum 2: " << sum << std::endl;
}