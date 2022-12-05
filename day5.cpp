//
// Created by Johannes Loepelmann on 05.12.22.
//

#include "util.h"

class Stack {
private:
    std::vector<char> crates;

public:
    void put(char crate) {
        crates.push_back(crate);
    }

    void flip() {
        std::reverse(crates.begin(), crates.end());
    }

    bool empty() {
        return crates.empty();
    }

    char pop() {
        char result = crates.back();
        crates.pop_back();
        return result;
    }

    char at(int index) {
        return crates[crates.size() - index];
    }

    char top() {
        return crates.back();
    }

    friend std::ostream &operator<<(std::ostream &out, const Stack &val);
};

std::ostream& operator<<(std::ostream& out, const Stack& val) {
    for(const auto crate : val.crates) {
        out << '[' << crate << ']';
    }
    return out;
}

struct Instruction {
    int from, to, amount;

    explicit Instruction(const std::string& input) {
        amount = std::stoi(input.substr(input.find_first_of('e') + 1, input.find_first_of('f') - input.find_first_of('e') -1));
        from = std::stoi(input.substr(input.find("om") + 2, input.find_first_of('t') - input.find("om") - 2));
        to = std::stoi(input.substr(input.find_last_of('o') +1));
    }
};

std::ostream& operator<<(std::ostream& out, const Instruction& val) {
    return out << val.amount << " from " << val.from << " to " << val.to;
}

void print_stacks(const std::vector<Stack>& stacks) {
    for(auto& s : stacks) {
        std::cout << s << std::endl;
    }
}

int main() {
    const auto lines = read_strings_from_file("day5.input");
    std::vector<Stack> stacks;
    std::vector<Instruction> instructions;

    for(const auto& line : lines) {
        if(line[0]=='m') break;

        const auto needed_stacks = (line.length() / 4) + 1;
        if(stacks.size() < needed_stacks) {
            for(size_t i=0; i < stacks.size() - needed_stacks; ++i) {
                stacks.emplace_back();
            }
        }

        for(size_t i = 0; i < line.size(); ++i) {
            int stack_number = (int)(i / 4);
            char current = line[i];
            if(current == '[' || current == ']' || current == ' ') continue;
            if(isdigit(current)) break;
            stacks[stack_number].put(current);
        }
    }

    for(auto& s : stacks) {
        s.flip();
    }

    const auto instructions_start = std::find_if(lines.begin(), lines.end(),[](const auto& line) {
        return line[0] == 'm';
    });

    std::for_each(instructions_start, lines.end(), [&instructions] (const auto line) {
        instructions.emplace_back(line);
    });

    auto part_one = stacks;
    for(const auto& instruction : instructions) {
        for (int i = 0; i < instruction.amount; ++i) {
            const auto crate = part_one[instruction.from - 1].pop();
            part_one[instruction.to - 1].put(crate);
        }
    }

    std::cout << "Part One Tops: ";
    for(auto& s : part_one) {
        std::cout << s.top();
    }
    std::cout << std::endl;

    for(const auto& instruction : instructions) {
        std::vector<char> crates;
        for (int i = 0; i < instruction.amount; ++i) {
            crates.push_back(stacks[instruction.from - 1].pop());
        }
        std::reverse(crates.begin(), crates.end());
        for(const auto crate : crates) {
            stacks[instruction.to - 1].put(crate);
        }
    }

    std::cout << "Part Two Tops: ";
    for(auto& s : stacks) {
        std::cout << s.top();
    }
    std::cout << std::endl;
}