//
// Created by Johannes Loepelmann on 09.12.22.
//

#include <set>

#include "util.h"

const int max_width = 1024;

enum Direction {
    UP, DOWN, LEFT, RIGHT
};

struct Instruction {
    Direction dir;
    int steps;

    explicit Instruction(const std::string &input) {
        switch (input[0]) {
            case 'U':
                dir = UP;
                break;
            case 'D':
                dir = DOWN;
                break;
            case 'L':
                dir = LEFT;
                break;
            case 'R':
                dir = RIGHT;
        }
        steps = std::stoi(input.substr(1));
    }
};

struct Position {
    int x = 0, y = 0;

    bool operator<(const Position &lhs) const {
        return x * max_width + y < lhs.x * max_width + lhs.y;
    }
};

bool touching(const Position first, const Position second) {
    return (abs(first.x - second.x) < 2 && abs(first.y - second.y) < 2);
}

std::vector<Position> move(const Instruction ins, std::vector<Position> &snake) {
    std::vector<Position> result;
    auto &h = snake.front();

    for (int i = 0; i < ins.steps; ++i) {
        switch (ins.dir) {
            case UP:
                h.y += 1;
                break;
            case DOWN:
                h.y -= 1;
                break;
            case LEFT:
                h.x -= 1;
                break;
            case RIGHT:
                h.x += 1;
                break;
        }
        for (auto it = snake.begin(); it < snake.end() - 1; ++it) {
            auto &front = *it;
            auto &back = *(it + 1);
            auto x_dir = std::clamp(front.x - back.x, -1, 1);
            auto y_dir = std::clamp(front.y - back.y, -1, 1);
            if (!touching(front, back)) {
                back.x += x_dir;
                back.y += y_dir;
            }
        }
        result.push_back(snake.back());
    }

    return result;
}


int main() {
    const auto lines = read_strings_from_file("day9.input");
    std::set<Position> visited_short;
    std::set<Position> visited_long;

    Position s;
    visited_short.insert(s);
    visited_long.insert(s);
    std::vector<Position> short_snake = {s, s};
    std::vector<Position> long_snake = {s, s, s, s, s, s, s, s, s, s};
    for (const auto &line: lines) {
        Instruction current(line);
        const auto vis_short = move(current, short_snake);
        visited_short.insert(vis_short.begin(), vis_short.end());
        const auto vis_long = move(current, long_snake);
        visited_long.insert(vis_long.begin(), vis_long.end());
    }

    std::cout << "Count short: " << visited_short.size() << " Count long: " << visited_long.size() << std::endl;
}