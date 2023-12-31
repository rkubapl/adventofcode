#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <numeric>
#include <iterator>

using namespace std;

struct Node {
    string key;
    Node *left_child;
    Node *right_child;

    Node(string k) {
        key = k;
    }
};

template<typename Number, typename Input>
Number lcm(Input const &in) {
    return std::accumulate(std::begin(in), std::end(in),
                           Number(1), std::lcm<Number, Number>);
}

int main()
{
    string line;
    ifstream input ("../input.txt");

    map<string,Node*> nodes;

    string instructions = "";

    if (input.is_open()) {
        while (getline(input,line)) {
            if(instructions == "") {
                instructions = line;
                continue;
            }
            if(line == "") continue;

            string key = {line[0], line[1], line[2]};
            string left_child = {line[7], line[8], line[9]};
            string right_child = {line[12], line[13], line[14]};

            if(nodes.find(left_child) == nodes.end()) {
                nodes[left_child] = new Node(left_child);
            }

            if(nodes.find(right_child) == nodes.end()) {
                nodes[right_child] = new Node(right_child);
            }

            if(nodes.find(key) == nodes.end()) {
                nodes[key] = new Node(key);
            }

            nodes[key]->left_child = nodes[left_child];
            nodes[key]->right_child = nodes[right_child];
        }
    }

    int stepsCount, stepsCount2 = 0;
    int instructionIndex = 0;

    Node *node = nodes["AAA"];

    map<string, Node*> nodesWithA;
    vector<int> nodesMinSteps;

    for (pair<string,Node*> n : nodes) {
        if(n.first[2] == 'A') {
            nodesWithA.insert({n.first, n.second});
        }
    }

    while(true) {
        bool task1 = node->key != "ZZZ";
        bool task2 = nodesWithA.size() != 0;
        if(!task1 && !task2) break;

        char ch = instructions[instructionIndex];

        if(task1) {
            stepsCount++;

            if(ch == 'L') node = node->left_child;
            if(ch == 'R') node = node->right_child;
        }

        if(task2) {
            stepsCount2++;

            vector<string> toremove;
            for (auto node : nodesWithA) {
                if(ch == 'L') {
                    nodesWithA[node.first] = node.second->left_child;
                }
                if(ch == 'R') {
                    nodesWithA[node.first] = node.second->right_child;
                }


                if(nodesWithA[node.first]->key[2] == 'Z') {
                    nodesMinSteps.push_back(stepsCount2);
                    toremove.push_back(node.first);
                }
            }
            for(string removeKey : toremove) nodesWithA.erase(removeKey);
            toremove.clear();
        }

        if(instructionIndex == instructions.length()-1) {
            instructionIndex = 0;
        } else {
            instructionIndex++;
        }
    }

    cout << "Part 1: " << stepsCount << endl;
    cout << "Part 2: " << lcm<long long>(nodesMinSteps) << endl;

    return 0;
}
