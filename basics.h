#ifndef BASICS_H
#define BASICS_H

#include "basics.cpp"
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <locale>

using namespace std;
using namespace std::chrono;
using namespace std::this_thread;

string lowercaseFirst(string input);
string lowercaseAll(string input);
string uppercaseAll(string input);
string uppercaseFirst(string input);
void newLine();
void clear();
int randomInt(int max);
int maxInput(int input, int max);
int minInput(int input, int min);
void wait(int timeToWait);
int menuCreator(vector<string> menuChoices, string prompt);
string searchParam(string input);

#endif
