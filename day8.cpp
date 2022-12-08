//
// Created by Johannes Loepelmann on 08.12.22.
//
#include <numeric>

#include "util.h"

bool visible_from_sides(const std::vector<std::vector<int>>& map, size_t x, size_t y) {
    //edge
    if(x==0 || y == 0 || x==map.size()-1 || y==map[x].size()-1)
        return true;
     //left
     bool visible_from_left = true;
     for(size_t c_col = y; c_col > 0; --c_col) {
        if(map[x][c_col-1] >= map[x][y]) visible_from_left = false;
     }
    //right
    bool visible_from_right = true;
    for(size_t c_col = y+1; c_col < map[x].size(); ++c_col) {
        if(map[x][c_col] >= map[x][y]) visible_from_right = false;
    }
    //top
    bool visible_from_top = true;
    for(size_t c_row = x; c_row > 0; --c_row) {
        if(map[c_row-1][y] >= map[x][y]) visible_from_top = false;
    }
    //bottom
    bool visible_from_bottom = true;
    for(size_t c_row = x+1; c_row < map.size(); ++c_row) {
        if(map[c_row][y] >= map[x][y]) visible_from_bottom = false;
    }

    return visible_from_left || visible_from_right || visible_from_top || visible_from_bottom;
}

int score(const std::vector<std::vector<int>>& map, size_t x, size_t y) {
    //left
    int visible_from_left = 0;
    for(size_t c_col = y; c_col > 0; --c_col) {
        visible_from_left++;
        if(map[x][c_col-1] >= map[x][y]) break;
    }
    //right
    int visible_from_right = 0;
    for(size_t c_col = y+1; c_col < map[x].size(); ++c_col) {
        visible_from_right++;
        if(map[x][c_col] >= map[x][y]) break;
    }
    //top
    int visible_from_top = 0;
    for(size_t c_row = x; c_row > 0; --c_row) {
        visible_from_top++;
        if(map[c_row-1][y] >= map[x][y]) break;
    }
    //bottom
    int visible_from_bottom = 0;
    for(size_t c_row = x+1; c_row < map.size(); ++c_row) {
        visible_from_bottom++;
        if(map[c_row][y] >= map[x][y]) break;
    }

    return visible_from_top * visible_from_bottom * visible_from_left * visible_from_right;
}

int main() {
    const auto lines = read_strings_from_file("day8.input");
    std::vector<std::vector<int>> map;

    for(const auto& line : lines) {
        std::vector<int> row;

        for (char i : line) {
            row.push_back(i - '0');
        }
        map.push_back(row);
    }

    int sum = 0;
    int best_score = 0;

    for(size_t row = 0; row < map.size(); ++ row) {
        for(size_t col = 0; col < map[row].size(); ++col) {
            sum += visible_from_sides(map, row, col);
            if(score(map, row, col) > best_score) best_score = score(map, row, col);
        }
    }
    std::cout << "Sum: " << sum << " Score: " << best_score << std::endl;
}