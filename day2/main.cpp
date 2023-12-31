#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<string> split(string str, char splitter, bool skipNextChar = true) {
    vector<string> splitted;
    string temp = "";

    for(int i = 0; i < str.length(); i++) {
        char charAt = str[i];

        if(charAt != splitter) {
            temp += charAt;
        } else {
            splitted.push_back(temp);
            temp = "";
            if(skipNextChar) i++; //skip space, can cause an error if string ends with splitter char, but for our input data this isn't a problem
        }
    }
    if(!temp.empty()) splitted.push_back(temp);

    return splitted;
}
int main() {
    std::string line;
    std::ifstream myfile ("../input.txt");

    if (myfile.is_open()) {
        int sumOfIds = 0;
        int sumOfPowers = 0;

        vector<int> invalidGames;

        int gameid = 1;
        while (getline(myfile,line)) {
            vector<string> splitted = split(line, ':');

            string game_data = splitted[1];

            vector<string> setsRevealed = split(game_data, ';');

            bool valid = true;
            int redMin, blueMin, greenMin = 0;

            for(int i = 0; i < setsRevealed.size(); i++) {
                string set = setsRevealed[i];

                vector<string> cubes = split(set, ',');;

                for(int j = 0; j < cubes.size(); j++) {
                    vector<string> cube = split(cubes[j], ' ', false);

                    int amount = stoi(cube[0]);
                    string color = cube[1];

                    if(color == "red") {
                        if(amount > 12) valid = false;
                        if(amount > redMin) redMin = amount;
                    }

                    if(color == "green") {
                        if(amount > 13) valid = false;
                        if(amount > greenMin) greenMin = amount;
                    }

                    if(color == "blue") {
                        if(amount > 14) valid = false;
                        if(amount > blueMin) blueMin = amount;
                    }
                }
            }
            if(valid) {
                sumOfIds += gameid;
            }

            gameid++;
            sumOfPowers += redMin*blueMin*greenMin;
        }

        cout << "(Task1) Sum of IDs: " <<  sumOfIds << endl;
        cout << "(Task2) Sum of powers: " <<  sumOfPowers << endl;
    }

    return 0;
}
