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

    int instructionIndex = 0;
    string instructions = "";

    if (input.is_open()) {
        while (getline(input,line)) {
            if(instructions == "") {
                instructions = line;
                continue;
            }

            if(line == "") continue;

            string key;
            key += line[0];
            key += line[1];
            key += line[2];

            string left_child;
            left_child += line[7];
            left_child += line[8];
            left_child += line[9];

            string right_child;
            right_child += line[12];
            right_child += line[13];
            right_child += line[14];

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
    Node startNode = nodes["AAA"];

    while(startNode.key != "ZZZ") {
        stepsCount++;

        char ch = instructions[instructionIndex];

        if(ch == 'L') {
            startNode = *startNode.left_child;
        }

        if(ch == 'R') {
            startNode = *startNode.right_child;
        }

        if(instructionIndex == instructions.length()-1) {
            instructionIndex = 0;
        } else {
            instructionIndex++;
        }
    }

    cout << stepsCount << endl;

    return 0;
}
