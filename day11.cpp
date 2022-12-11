//
// Created by Johannes Loepelmann on 11.12.22.
//

#include <numeric>

#include "util.h"

enum Operation {
    ADD, MULT
};

std::ostream & operator << (std::ostream& out, const Operation op) {
    return out << (op==MULT? "MULT" : "ADD");
}


struct Monkey{
    std::vector<long> items;
    Operation op;
    int arg = 0;
    int div;
    int target_true, target_false;
    long interactions = 0;

    explicit Monkey(std::vector<std::string>& input) {
        std::istringstream sstream(input[0].substr(input[0].find_first_of(':')+1));
        std::string s;
        while(getline(sstream, s, ',')) {
            items.push_back(std::stoi(s));
        }
        op = input[1].find('*') != std::string::npos? MULT : ADD;
        if(input[1][input[1].find_last_of(' ')+1] != 'o') {
            arg = std::stoi(input[1].substr(input[1].find_last_of(' ')));
        }
        div = std::stoi(input[2].substr(input[2].find_last_of(' ')));
        target_true = std::stoi(input[3].substr(input[3].find_last_of(' ')));
        target_false = std::stoi(input[4].substr(input[4].find_last_of(' ')));
    }

    bool operator < (const Monkey& other) const {
        return interactions < other.interactions;
    }
};

std::ostream & operator << (std::ostream& out, const Monkey& monkey) {
    out << "Items: " ;
    for(const auto item : monkey.items) {
        out << item << ", ";
    }
    out << "Op: " << monkey.op << " Arg: " << monkey.arg << " Div: " << monkey.div << " True: " << monkey.target_true << " False: " << monkey.target_false << " Int: " << monkey.interactions;
    return out;
}

int main() {
    const auto lines = read_strings_from_file("day11.input");
    std::vector<Monkey> monkeys;

    auto current = std::find_if(lines.begin(), lines.end(), [](const auto &item) {
        return item[0]=='M';
    });

    while(current != lines.end()) {
        const auto begin = current+1;
        const auto end = std::find_if(begin, lines.end(), [](const auto &item) {
            return item[0]=='M';
        });
        std::vector<std::string> input(begin, end);
        monkeys.emplace_back(input);
        current = end;
    }
    std::vector<Monkey> monkeys2 = monkeys;

    for(int round = 0; round < 20; ++round) {
        for(auto& monkey : monkeys) {
            while(!monkey.items.empty()) {
                monkey.interactions++;
                auto item = monkey.items.back();
                monkey.items.pop_back();
                long arg = monkey.arg;
                if(arg == 0) arg = item;
                if(monkey.op == MULT) {
                    item = item * arg;
                } else {
                    item = item + arg;
                }
                item = item / 3;
                if(item % monkey.div == 0) {
                    monkeys[monkey.target_true].items.push_back(item);
                } else {
                    monkeys[monkey.target_false].items.push_back(item);
                }
            }
        }
    }

    std::sort(monkeys.begin(), monkeys.end());
    std::cout << "Monkey business: " << monkeys[monkeys.size()-1].interactions * monkeys[monkeys.size()-2].interactions << std::endl;

    int magic = std::accumulate(monkeys.begin(), monkeys.end(), 1, [](const auto sum, const auto& monkey) {
        return sum * monkey.div;
    });

    for(int round = 0; round < 10000; ++round) {
        for(auto& monkey : monkeys2) {
            while(!monkey.items.empty()) {
                monkey.interactions++;
                auto item = monkey.items.back();
                monkey.items.pop_back();
                long arg = monkey.arg;
                if(arg == 0) arg = item;
                if(monkey.op == MULT) {
                    item = item * arg;
                } else {
                    item = item + arg;
                }
                item = item % magic;
                if(item % monkey.div == 0) {
                    monkeys2[monkey.target_true].items.push_back(item);
                } else {
                    monkeys2[monkey.target_false].items.push_back(item);
                }
            }
        }
    }

    std::sort(monkeys2.begin(), monkeys2.end());
    std::cout << "Monkey business: " << monkeys2[monkeys2.size()-1].interactions * monkeys2[monkeys2.size()-2].interactions << std::endl;
}