#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string searchForArr[20] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0"};

int substringToDigit(string substring) {
    if(substring.length() > 1) {
        auto itr = find(searchForArr, searchForArr+10, substring); //10 because we check only for strings
        return distance(searchForArr, itr);
    }
    return int(substring[0] - '0');
}

int getNum(string line) {
    int firstIndex = INT_MAX;
    int lastIndex = -2;

    string firstSubstring;
    string lastSubstring;

    for(int i = 0; i < 20; i++) {
        string searchFor = searchForArr[i];

        int index_first = line.find(searchFor);
        int index_last = line.rfind(searchFor);

        if(index_first != -1 && index_first < firstIndex) {
            firstIndex = index_first;
            firstSubstring = searchFor;
        }

        if(index_last != -1 && index_last > lastIndex) {
            lastIndex = index_last;
            lastSubstring = searchFor;
        }
    }

    int firstNum = substringToDigit(firstSubstring);
    int lastNum = substringToDigit(lastSubstring);

    return firstNum*10+lastNum;
}

int main()
{
    string line;
    ifstream myfile ("../input.txt");

    int sum = 0;
    if (myfile.is_open()) {
        while (getline(myfile,line)) {
            sum += getNum(line);
        }
        myfile.close();
        std::cout << sum << endl;
        return 0;
    }

    std::cout << "Failed to open the file." << endl;
    return 0;
}
