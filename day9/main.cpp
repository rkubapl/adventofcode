#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

vector<int> stringToInts(string &input) {
    vector<int> layer;
    int num = 0;
    bool negative = false;

    for(int i = 0; i < input.length(); i++) {
        char ch = input[i];

        if(!isdigit(ch)) {
            if(ch == '-') {
                negative = true;
                continue;
            }

            if(negative) num *= -1;

            layer.push_back(num);
            num = 0;
            negative = false;
        } else {
            int digit = ch - '0';
            num = (num*10)+digit;
        }
    }

    if(negative) num *= -1;
    layer.push_back(num);

    return layer;
}


vector<int> getDiffBetweenInts(vector<int> &nums) {
    vector<int> diffs;

    for (int j = 1; j < nums.size(); j++) {
        diffs.push_back(nums[j]-nums[j-1]);
    }

    return diffs;
}

bool checkIfZeros(vector<int> &nums) {
    if(nums.empty() || nums.size() == 1) return false;

    int begin = *nums.begin();
    if(begin != 0) return false;

    for (int i = 1; i < nums.size(); i++) {
        if(nums[i] != begin) return false;
    }

    return true;
}

pair<int, int> getBeginAndNextValue(string input) {
    vector<int> nums = stringToInts(input);

    vector<vector<int>> layers;
    layers.push_back(nums);

    vector<int> diffs = getDiffBetweenInts(nums);

    while(!checkIfZeros(diffs)) {
        layers.push_back(diffs);
        diffs = getDiffBetweenInts(diffs);
    }
    layers.push_back(diffs);

    vector<int> backNumbers = {0};

    for (int i = layers.size()-2; i >= 0; i--) {
        int j = i+1;
        int endBelowVal = layers[j].back();
        int beginBelowVal = backNumbers.back();

        int endThisLine = layers[i].back();
        int beginThisLine = *layers[i].begin();

        layers[i].push_back(endThisLine+endBelowVal);
        backNumbers.push_back(beginThisLine-beginBelowVal);
    }

    return {backNumbers.back(), layers[0].back()};
}

int main() {
    string line;
    ifstream input ("../input.txt");

    int sumBegin = 0;
    int sumEnd = 0;

    if (input.is_open()) {
        while (getline(input, line)) {
            pair<int,int> values = getBeginAndNextValue(line);
            sumBegin += values.first;
            sumEnd += values.second;
        }
    }

    cout << "Part 1: " << sumEnd << endl;
    cout << "Part 2: " << sumBegin << endl;

    return 0;
}
