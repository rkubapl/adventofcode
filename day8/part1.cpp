#include <fstream>
#include <iostream>
#include <map>

using namespace std;

struct Node {
    string key;
    Node *left_child;
    Node *right_child;
};

int main()
{
    string line;
    ifstream input ("../input.txt");

    map<string,Node> nodes;

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

            Node node;
            node.key = key;

            if(nodes.find(left_child) == nodes.end()) nodes[left_child] = Node();
            if(nodes.find(right_child) == nodes.end()) nodes[right_child] = Node();

            node.left_child = &nodes[left_child];
            node.right_child = &nodes[right_child];

            nodes[key] = node;
        }
    }

    int stepsCount = 0;
    int instructionIndex = 0;

    Node node = nodes["AAA"];
    while(node.key != "ZZZ") {
        stepsCount++;

        char ch = instructions[instructionIndex];

        if(ch == 'L') node = *node.left_child;
        if(ch == 'R') node = *node.right_child;

        if(instructionIndex == instructions.length()-1) {
            instructionIndex = 0;
        } else {
            instructionIndex++;
        }
    }

    cout << stepsCount << endl;

    return 0;
}
