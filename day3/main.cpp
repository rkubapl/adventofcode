#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <vector>

using namespace std;

int getIntLength(int num) {
    int length = 0;
    while (num != 0) {
        length++;
        num = num/10;
    }
    return length;
}

bool isSymbol(char ch) {
    //! $ & % @ / - + = # *
    // return ch == 33 || ch == 36 || ch == 38 || ch == 37 || ch == 64 || ch == 47 || ch == 45 || ch == 43 || ch == 61 || ch == 35 | ch == 42;
    return ch != 46;
}

bool checkForSymbol(int length, int numBegin, int numEnd, bool symbol[]) {
    // int length = line->length();
    int searchBegin = 0;

    if(numBegin > 0) {
        searchBegin = numBegin-1;
    } else {
        searchBegin = numBegin;
    }

    int searchEnd = 0;

    if(numEnd < length) {
        searchEnd = numEnd+1;
    } else {
        searchEnd = numEnd;
    }

    for (int i = searchBegin; i <= searchEnd; i++) {
        if(symbol[i]) return true;
    }
    return false;
}

int main() {
    std::string line;
    std::ifstream input ("../input3.txt");

    string lines[200];

    if (input.is_open()) {
        int i = 0;
        while (getline(input,line)) {
            lines[i] = line;
            i++;
        }
        input.close();
    }

    int lineLength = lines[0].length();
    bool symbol[lines->length()][lineLength];


    for (int i = 0; i < lines->length(); i++) {
        for (int j = 0; j < lineLength; j++) {
            char ch = lines[i][j];

            if (isSymbol(ch)) {
                symbol[i][j] = true;
            } else {
                symbol[i][j] = false;
            }
        }
    }

    int sum = 0;

    for (int lineIndex = 0; lineIndex < lines->length(); lineIndex++) {
        int startIndex = -1;
        int number = 0;

        for (int pos = 0; pos < lineLength; pos++) {
            char ch = lines[lineIndex][pos];

            if(isdigit(ch)) {
                int digit = ch - '0';
                if(startIndex == -1) {
                    startIndex = pos;
                    number = digit;
                } else {
                    number *= 10;
                    number += digit;
                }

            } else {
                if(startIndex != -1) {
                    int endIndex = pos-1;

                    //CHECK IN LINE
                    //BEFORE
                    if(0 < startIndex) {
                        if(symbol[lineIndex][startIndex-1]) {
                            sum += number;
                            startIndex = -1;
                            continue;
                        }
                    }

                    //AFTER
                    if(lineLength-1 > endIndex) { //-1 to get maximum index
                        if(symbol[lineIndex][endIndex+1]) {
                            sum += number;
                            startIndex = -1;
                            continue;
                        }
                    }

                    //CHECK HIGHER LINE
                    if(0 < lineIndex) {
                        bool found = checkForSymbol(lineLength, startIndex, endIndex, symbol[lineIndex-1]);

                        if(found) {
                            sum += number;
                            startIndex = -1;
                            continue;
                        }
                    }

                    //CHECK LOWER LINE
                    if(lines->length()-1 > lineIndex) {
                        bool found = checkForSymbol(lineLength, startIndex, endIndex, symbol[lineIndex+1]);

                        if(found) {
                            sum += number;
                            startIndex = -1;
                            continue;
                        }
                    }

                    startIndex = -1;
                }
            }
        }
    }

    cout << "Part 1: " << sum << endl;
    return 0;
}
