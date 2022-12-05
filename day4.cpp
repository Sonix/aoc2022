//
// Created by Johannes Loepelmann on 04.12.22.
//

#include "util.h"

struct Range {
    int start, end;
};

Range range_from_line(const std::string& line) {
    Range result{};
    result.start = std::stoi(line.substr(0,line.find('-')));
    result.end = std::stoi(line.substr(line.find('-')+1));
    return result;
}

bool overlap_completely(const Range left, const Range right) {
    if((left.start >= right.start && left.end <= right.end) || (right.start >= left.start && right.end <= left.end)) {
        return true;
    }
    return false;
}

bool overlap_partially(const Range left, const Range right) {
    if((left.start <= right.end && left.start >= right.start) ||  (left.end >= right.start && left.end <= right.end)) {
        return true;
    } else if((right.start <= left.end && right.start >= left.start) ||  (right.end >= left.start && right.end <= left.end)) {
        return true;
    }
    return false;
}

int main() {
    const auto lines = read_strings_from_file("day4.input");
    int sum_completely = 0;
    int sum_partially = 0;

    for(const auto& line : lines) {
        const auto left = range_from_line(line.substr(0, line.find(',')));
        const auto right = range_from_line(line.substr(line.find(',')+1));
        if(overlap_completely(left, right)){
            sum_completely++;
        }
        if(overlap_partially(left, right)){
            sum_partially++;
        }
    }

    std::cout << "Sum Completely: " << sum_completely << std::endl;
    std::cout << "Sum Partially: " << sum_partially << std::endl;
}