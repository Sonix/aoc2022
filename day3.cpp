//
// Created by Johannes Loepelmann on 03.12.22.
//

#include "util.h"

class Rucksack {

public:
    explicit Rucksack(std::string_view input) {
        middle = (int)input.length() / 2;

        for (char current : input) {
            items.push_back(current);
        }
    }

    [[nodiscard]] char common_item() const {
        auto result = std::find_if(items.begin(), items.begin()+middle, [this](const auto c) {
            return std::count(items.begin()+middle, items.end(),c);
        });
        return *result;
    }

    [[nodiscard]] const std::vector<char> & get_items() const {
        return items;
    }

private:
    std::vector<char> items;
    int middle;
};

int priority(const char c) {
    if(c >= 'a' && c <= 'z') {
        return 1 + (c-'a');
    } else {
        return 27 + (c-'A');
    }
}

char badge_for_items(const std::vector<Rucksack>& rucksacks) {
    int counts[52] = {0};
    for(const auto& rucksack : rucksacks) {
        int current_counts[52] = {0};
        for(const auto item : rucksack.get_items()){
            current_counts[priority(item)-1]++;
        }
        for (int i = 0; i < 52; ++i) {
            if(current_counts[i]) counts[i]++;
        }
    }
    for (int i = 0; i < 52; ++i) {
        if(counts[i]==3){
            return i < 26 ? ('a'+i) :  'A'+i-26;
        }
    }
    return 'a';
}

int main() {
    const auto lines = read_strings_from_file("day3.input");
    std::vector<Rucksack> rucksacks;

    int sum_prios = 0;
    int sum_badges = 0;
    std::vector<Rucksack> current_group;

    for(const auto& line : lines) {
        const auto current = rucksacks.emplace_back(line);
        current_group.push_back(current);

        const auto common = current.common_item();
        sum_prios += priority(common);

        if(current_group.size() == 3) {
            const auto badge = badge_for_items(current_group);
            sum_badges += priority(badge);
            current_group.clear();
        }
    }

    if(current_group.size() == 3) {
        const auto badge = badge_for_items(current_group);
        sum_badges += priority(badge);
    }

    std::cout << "Sum Prios: " << sum_prios << std::endl;
    std::cout << "Sum Badges: " << sum_badges << std::endl;


}