/*
 * File: textGenerator.cpp
 * Author: Maria Alexis Sales, CS 251
 */

#include <iostream>
#include "myrandom.h"
#include <string>
#include <map>
#include <queue>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;
/* Function Declarations */
void startPrompt(); // This is the starting prompt 
void menu(string filename, int nValue, int totalWords); // This has the choices and the functions they execute
void buildMap(string filename, int nValue, int totalWords, map<queue<string>, vector<string>>& textMap); // This function builds the map 
void printMap(map<queue<string>, vector<string>>& textMap); // This function prints out the map
void clear(queue<string>& keyQ); // Clear helper funcion

int main() {
    startPrompt();
    return 0;
}

/* Function Definitions */
void startPrompt() {
    string filename;
    int nValue, totalWords;
    
    cout << "Welcome to the Text Generator." << endl;
    cout << "This program makes random text based on a document" << endl;
    cout << "Input file name? ";
    cin >> filename;
    cout << "Value of N? ";
    cin >> nValue;
    cout << "Total words you'd like to generate? ";
    cin >> totalWords;
    menu(filename, nValue, totalWords);
}

void menu(string filename, int nValue, int totalWords) {
    char choice;
    map<queue<string>, vector<string>> textMap;

    while(choice != 'x') {
        cout << "Type b-build map, p-print map, g-generate text, s-start over, x-to exit: ";
        cin >> choice;
        switch(choice) {
            case 'b':
                buildMap(filename, nValue, totalWords, textMap);
                break;
            case 'p':
                printMap(textMap);
                break;
            case 'g':
                // generateText(textMap);
                break;
        }
    }
}

void buildMap(string filename, int nValue, int totalWords, map<queue<string>, vector<string>>& textMap) {
    string word;
    ifstream inFS;
    vector<string> textFile;
    queue<string> emptyQ, keyQ;

    cout << "...Building map: " << filename << "...\n" << endl;
    inFS.open(filename);
    while(!inFS.eof()) {
        inFS >> word;
        textFile.push_back(word);
    }

    // go through every n group starting with 0
    // when you get to n-1, add that as the value to the map
    // empty out the temp key container every time
    // Keep cycling through all the words...remember, once you reach the end, wrap around!
    for(size_t i = 0; i < textFile.size(); i++) {
        for(size_t j = 0; j < nValue; j++) {
            int pos = i+j;
            if(pos >= textFile.size())
                pos = textFile.size() - pos;
            if(j < nValue-1) {
                keyQ.push(textFile[pos]);
            } else {
                textMap[keyQ].push_back(textFile[pos]);
                clear(keyQ);
            }
        }
        
    }
    
    inFS.close();
}

//Fast clearing of queue
void clear(queue<string>& keyQ) {
    while(!keyQ.empty())
        keyQ.pop();
}

void printMap(map<queue<string>, vector<string>>& textMap) {
    queue<string> tempQ;
    vector<string> tempV;

    /* This will output the map when n = 3, filename = tiny.txt, and total words = 10:
    {be just} -> {be}
    {be or} -> {not not}
    {be who} -> {you} 
    ... etc. */
    for(auto& e: textMap) {
        tempQ = e.first;
        cout << "{";
        while(!tempQ.empty()) {
            cout << tempQ.front() << " ";
            tempQ.pop();
        }
        cout << "} -> {";
        tempV = e.second;
        for(int i = 0; i < tempV.size(); i++) {
            cout << tempV[i] << " ";
        }
        cout << "}" << endl;
    }

}

// void generateText(map<queue<string>, vector<string>>& textMap)