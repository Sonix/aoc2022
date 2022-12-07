//
// Created by Johannes Loepelmann on 07.12.22.
//

#include "util.h"

bool each_char_unique(const std::string_view section) {
    for(size_t i = 0; i < section.size(); ++i) {
        for(size_t j = i+1; j < section.size(); ++j) {
            if(section[i]==section[j]) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    const auto line = read_strings_from_file("day6.input")[0];

    for(size_t i = 3; i < line.size(); ++i) {
        if(each_char_unique(line.substr(i-3, 4))) {
            std::cout << "Index 1: " << i + 1 << std::endl;
            break;
        }
    }

    for(size_t i = 13; i < line.size(); ++i) {
        if(each_char_unique(line.substr(i-13, 14))) {
            std::cout << "Index 2: " << i + 1 << std::endl;
            break;
        }
    }
}