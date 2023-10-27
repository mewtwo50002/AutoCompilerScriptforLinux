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

string lowercaseFirst(string input)
{
    input[0] = tolower(input[0]);
    return input;
}

string lowercaseAll(string input)
{
    for (int i = 0; i < input.size(); i++)
    {
        input[i] = tolower(input[i]);
    }

    return input;
}

string uppercaseAll(string input)
{
    for (int i = 0; i < input.size(); i++)
    {
        input[i] = toupper(input[i]);
    }

    return input;
}

string uppercaseFirst(string input)
{
    if (!input.empty())
        input[0] = toupper(input[0]);
    return input;
}

void newLine()
{
    cout << endl;
}

void clear()
{
    cout << "\x1B[2J\x1B[H";
}

int randomInt(int max)
{
    static bool seeded = false;
    if (!seeded)
    {
        srand(time(NULL));
        seeded = true;
    }
    int random = (rand() % max) + 1;
    return random;
}

int maxInput(int input, int max)
{
    if (input > max)
    {
        return max;
    }
    else
    {
        return input;
    }
}

int minInput(int input, int min)
{
    if (input < min)
    {
        return min;
    }
    else
    {
        return min;
    }
}

void wait(int timeToWait)
{
    sleep_for(seconds(timeToWait));
}

int menuCreator(vector<string> menuChoices, string prompt)
{
    string find;
    int choice;
    cout << prompt << endl;
    for (int i = 0; i < menuChoices.size(); i++)
    {
        cout << menuChoices[i] << endl;
    }
    cin >> find;
    for (int i = 0; i < menuChoices.size(); i++)
    {
        if (uppercaseFirst(lowercaseAll(find)) == uppercaseFirst(lowercaseAll(menuChoices[i])))
        {
            return (i + 1);
        }
    }
    choice = 0;
    return (choice);
}

string searchParam(string input)
{
    return uppercaseFirst(lowercaseAll(input));
}

