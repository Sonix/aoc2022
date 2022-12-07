//
// Created by Johannes Loepelmann on 07.12.22.
//

#include <numeric>

#include "util.h"

struct FSNode {
    int size = 0;
    std::string name;
    std::vector<FSNode> children;
    FSNode* parent = nullptr;
};

int tree_size(const FSNode& node) {
    if(node.size) return node.size;
    return std::accumulate(node.children.begin(), node.children.end(), 0, [&](const auto sum, const auto& node) {
        return sum + tree_size(node);
    });
}

void print_tree(const FSNode& node, int depth) {
    for(int i = 0; i < depth * 4; ++i) {
        std::cout << ' ';
    }
    std::cout << node.name;
    if(node.size!=0) {
        std::cout << "(" << node.size << ")";
    } else {
        std::cout << "(" << tree_size(node) << ")";
    }
    std::cout << std::endl;
    for(const auto& child : node.children) {
        print_tree(child, depth + 1);
    }
}

std::vector<FSNode> nodes_under_size(const FSNode& node, int max) {
    std::vector<FSNode> result;
    if(tree_size(node) < max && node.size == 0) {
        result.push_back(node);
    }
    for(const auto& child : node.children) {
        const auto child_result = nodes_under_size(child, max);
        result.insert(result.end(), child_result.begin(), child_result.end());
    }
    return result;
}

int main() {
    const auto lines = read_strings_from_file("day7.input");

    FSNode root;
    root.name = "/";

    FSNode* current = &root;

    for(auto lines_it = lines.begin(); lines_it < lines.end(); ++lines_it) {
        const auto& line = *lines_it;
        if(line[0] == '$') {
            if(line[2] == 'c') {
                std::string target = line.substr(line.find_last_of(' ') + 1);
                if(target=="/") {
                    current = &root;
                } else if(target=="..") {
                    current = current->parent;
                } else {
                    current = &*std::find_if(current->children.begin(), current->children.end(),[target](const auto& child){
                        return child.name==target;
                    });
                }
            } else if(line[2] == 'l') {
                for(auto it = lines_it + 1; it < lines.end(); ++it) {
                    const auto& current_line = *it;
                    if(current_line[0]== '$') {
                        break;
                    }
                    FSNode child;
                    if(current_line[0]!='d') {
                        child.size = std::stoi(current_line.substr(0, current_line.find_first_of(' ')));
                    }
                    child.name = current_line.substr(current_line.find_first_of(' ')+1);
                    child.parent = current;
                    current->children.push_back(child);
                }
            }
        }
    }
    print_tree(root, 0);

    const auto under100k = nodes_under_size(root, 100000);

    std::cout << "Sum < 100000: " << std::accumulate(under100k.begin(), under100k.end(), 0, [](const auto sum, const auto& node) {
        return sum + tree_size(node);
    }) << std::endl;

    std::vector<FSNode> flat_dirs =  nodes_under_size(root, INT32_MAX);
    std::sort(flat_dirs.begin(), flat_dirs.end(), [](const auto& left, const auto& right) {
        return tree_size(left) < tree_size(right);
    });

    const auto needed = 30000000- (70000000 - tree_size(root));
    std::cout << "Smallest fitting directory size: " << tree_size(*std::find_if(flat_dirs.begin(), flat_dirs.end(),[needed](const auto& node) {
        return tree_size(node) > needed;
    })) << std::endl;
}