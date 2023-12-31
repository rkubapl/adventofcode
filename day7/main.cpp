#include <iostream>
#include <map>
#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

char strengths[13] = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};

int getStrength(char ch) {
    auto it = find(strengths, strengths + 13, ch);
    return distance(strengths, it);
}

//Types
//7 - Five of a kind, where all five cards have the same label: AAAAA
//6 - Four of a kind, where four cards have the same label and one card has a different label: AA8AA
//5 - Full house, where three cards have the same label, and the remaining two cards share a different label: 23332
//4 - Three of a kind, where three cards have the same label, and the remaining two cards are each different from any other card in the hand: TTT98
//3 - Two pair, where two cards share one label, two other cards share a second label, and the remaining card has a third label: 23432
//2 - One pair, where two cards share one label, and the other three cards have a different label from the pair and each other: A23A4
//1 - High card, where all cards' labels are distinct: 23456
class Hand {
    public:
        string cards = "";
        int bid = 0;

        int type;

        Hand(string cards, int bid) {
            this->cards = cards;
            this->bid = bid;

            type = getType();
        }

        Hand(string input) {
            for(int i = 0; i < input.length(); i++) {
                char ch = input[i];
                if(i < 5) {
                    cards += ch;
                    continue;
                }
                if(i == 5) continue;
                int digit = ch - '0';

                bid = (bid*10)+digit;
            }

            type = getType();
        }

        int getType() {
            map<char, int> uniqueCards; //unique

            for(int i = 0; i < 5; i++) {
                char ch = cards[i];
                uniqueCards[ch]++;
            }

            if(uniqueCards.size() == 1) {
                return 7;
            }
            if (uniqueCards.size() == 2) {
                int v = uniqueCards.begin()->second;

                if(v == 4 || v == 1) { //4:1
                    return 6;
                }
                return 5; //3:2
            }

            if (uniqueCards.size() == 3) {
                int values[3];

                int i = 0;
                for(auto it : uniqueCards) {
                    values[i] = it.second;
                    i++;
                }

                if(values[0] == 3 || values[1] == 3 || values[2] == 3) { //3:1:1
                        return 4;
                }
                return 3; //2:2:1, 2:2:2
            }
            if (uniqueCards.size() == 4) {
                return 2;
            }
            return 1;
        }

        bool operator < (const Hand& hand2) {
            if(hand2.type != type) {
                return type < hand2.type;
            }

            for(int i = 0; i < 5; i++) {
                char ch1 = cards[i];
                char ch2 = hand2.cards[i];
                int strength1 = getStrength(ch1);
                int strength2 = getStrength(ch2);

                if(strength1 == strength2) continue;

                return strength1 < strength2;
            }
            return true; //idk what i have to return
        };

};




int main() {
    Hand h = Hand("T55J5", 500);

    string line;
    ifstream input ("../input.txt");

    vector<Hand> hands;

    if (input.is_open()) {
        while (getline(input,line)) {
            hands.push_back(Hand(line));
        }
    }

    sort(hands.begin(), hands.end());

    int sum = 0;

    for (int i = 0; i < hands.size(); i++) {
        int bid = hands[i].bid;
        sum += (i+1)*bid;
    }


    cout << "Task 1: " << sum << endl;

    // if(h > h)
    return 0;
}
