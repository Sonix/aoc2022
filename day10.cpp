//
// Created by Johannes Loepelmann on 10.12.22.
//

#include "util.h"

enum Command {
    NOOP, ADDX
};

struct Instruction {
    Command com;
    int arg;

    explicit Instruction(const std::string& input) {
        switch(input[0]) {
            case 'n':
                com = NOOP;
                break;
            case 'a':
                com = ADDX;
                arg = std::stoi(input.substr(4));
                break;
        }
    }
};

int state_at(const std::vector<Instruction>& program, int cycle) {
    int current_ins = 0;
    int current_cycle = 0;
    int x = 1;
    while(current_cycle < cycle) {
        const auto& ins = program[current_ins];
        if(ins.com == NOOP) {
            current_ins++;
            current_cycle++;
        } else if (ins.com == ADDX) {
            if(current_cycle+2 >= cycle)
                break;
            current_ins++;
            current_cycle+=2;
            x += ins.arg;
        }
    }
    return x;
}

int main() {
    std::vector<Instruction> program;
    for(const auto& line : read_strings_from_file("day10.input")){
        program.emplace_back(line);
    }

    std::cout << "Result: " << 20 * state_at(program, 20) + 60 * state_at(program, 60) +100 * state_at(program, 100) +140 * state_at(program, 140) +180 * state_at(program, 180) + 220 * state_at(program, 220) << std::endl;

    for(int row = 0; row < 6; ++row) {
        for(int col = 0; col < 40; ++col) {
            auto x = state_at(program, row*40+col+1);
            if(abs(col-x) < 2){
                std::cout << "██";
            } else {
                std::cout << "░░";
            }
        }
        std::cout << std::endl;
    }
}