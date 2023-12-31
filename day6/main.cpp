#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

struct Game {
    long long time, distance = 0;

    long long calcHoldButtonTimeToWin() {
        int a = -1, b = time, c = -distance;

        double determinant = pow(b,2)-4*a*c;

        if(determinant <= 0) return 1; //above x = 0 are distances higher than record, searching for x in f(x) > 0

        double sqrtDeterminant = sqrt(determinant);

        double min = (-b+sqrtDeterminant)/(2*a);
        double max = (-b-sqrtDeterminant)/(2*a);

        if(fmod(max, 1.0) == 0.0) {
            max--;
        } else {
            max = floor(max);
        }

        if(fmod(min, 1.0) == 0.0) {
            min++;
        } else {
            min = ceil(min);
        }

        return max-min+1;
    }
};

vector<int> getIntsFromString(string line, long long *wholeNum) {
    vector<int> ints;

    int num = 0;
    for(int i = 0; i < line.length(); i++) {
        char ch = line[i];

        if(isdigit(ch)) {
            int digit = ch - '0';

            num = (num*10)+digit;
            *wholeNum = (*wholeNum*10)+digit;
        } else {
            if(num > 0) {
                ints.push_back(num);
                num = 0;
            }
        }
    }
    if(num != 0) ints.push_back(num);

    return ints;
}

int main()
{
    string line;
    ifstream input ("../input.txt");

    string lines[2];

    if (input.is_open()) {
        int i = 0;
        while (getline(input,line)) {
            lines[i] = line;
            i++;
        }
    }

    vector<int> times, distances;

    long long timeSum = 0, distanceSum = 0;

    times = getIntsFromString(lines[0], &timeSum);
    distances = getIntsFromString(lines[1], &distanceSum);

    if(times.size() != distances.size()) return 0;

    int beatSum = 1;

    for(int i = 0; i < times.size(); i++) {
        Game game;
        game.distance = distances[i];
        game.time = times[i];

        beatSum = beatSum*game.calcHoldButtonTimeToWin();
    }

    cout << "Task 1: " << beatSum << endl;

    Game game;
    game.distance = distanceSum;
    game.time = timeSum;

    cout << "Task 2: " << game.calcHoldButtonTimeToWin() << endl;

    return 0;
}
