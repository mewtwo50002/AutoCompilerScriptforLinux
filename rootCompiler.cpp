#include "basics.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <time.h>
#include <fstream>
#include <string>
#include <unistd.h>
#include <ctype.h>
#include <cstdlib>
#include <cstring>
#include <cerrno>
using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

// Class definers
class childFolder
{
public:
    string name;
};
class Folder
{
public:
    string name;
};

Folder baseFolder;
Folder assignmentFolder;
Folder labsFolder;
Folder examsFolder;
childFolder assignmentChild;
childFolder labsChild;
childFolder examsChild;

// Prototype Variables
string getTimeStr();
string getTime();
void dirChanger();
void secondaryGraber();
int childGraber();
int compiler();

// Change how long it will wait befor compiling again
int timer = 2;
// add more secondary files here

// add classes declerations

// variable definitions
vector<string> menuChoices;
string folderI;
string former = baseFolder.name + "/";
string filename1, filename2;
string logName;
bool retry = true;
string number;
int firstTime = 0;
auto timeLog = getTime();
const char *back = "..";
const char *logs = "logs";
const char *compile;
const char *folderChange;
int folderInput;

int main()
{
    baseFolder.name = "cs120";

    assignmentFolder.name = "Assignment";
    menuChoices.push_back(assignmentFolder.name);

    labsFolder.name = "Labs";
    menuChoices.push_back(labsFolder.name);

    examsFolder.name = "Exams";
    menuChoices.push_back(examsFolder.name);

    assignmentChild.name = "assignment";
    labsChild.name = "lab";
    examsChild.name = "exam";

    former = baseFolder.name + "/";
    dirChanger();
    if (childGraber() == 1)
    {
        return 1;
    }
    
    compiler();
}
string getTimeStr()
{
    time_t now = chrono::system_clock::to_time_t(chrono::system_clock::now());
    string s(30, '\0');
    strftime(&s[0], s.size(), "%Y-%m-%d_%H:%M:%S", localtime(&now));
    return s;
}
string getTime()
{
    time_t now = system_clock::to_time_t(system_clock::now());
    string s(30, '\0');
    strftime(&s[0], s.size(), "%Y-%m-%d-%H-%M-%S", localtime(&now));
    return s;
}

void dirChanger()
{
    bool retry = false;
    system("clear");
    system("clear");
    do
    {
        folderInput = menuCreator(menuChoices, "What Folder would you like to go to?:");
        switch (folderInput)
        {
        case 1:
            former = former + assignmentFolder.name + "/";
            retry = false;
            break;
        case 2:
            former = former + labsFolder.name + "/";
            retry = false;
            break;
        case 3:
            former = former + examsFolder.name + "/";
            retry = false;
            break;
        case 0:

            cout << "That is not a choice try again...";
            wait(5);
            retry = true;
            break;
        }
    } while (retry == true);
}
int childGraber()
{
    cout << endl;
    cout << endl;
    cout << endl;
    cout << "what is the lab, assignment, or exam number?: ";
    cin >> number;
    cout << endl;
    cout << endl;
    cout << endl;
    //----------------------------------------------
    // change this function below to add more else-if statments to make to add more folders and letters

    if (folderInput == 1)
    {
        former = former + assignmentChild.name + number +"/";
    }else if(folderInput == 2)
    {
        former = former + labsChild.name + number +"/";
    }else if (folderInput == 3)
    {
        former = former + assignmentChild.name + number + "/";
    }
    
    folderChange = former.c_str();
    cout << former << endl;
    if (chdir(folderChange) != 0)
    {
        cerr << "Error changing directory" << endl;
        return 1; // Exit with an error code
    }
}

int compiler()
{
    system("ls");
    cout << "What's the name of the file you want to compile without the .cpp: ";
    cin >> filename1;

    filename2 = filename1 + ".cpp";
    string command = "g++ " + filename2 + " -o " + filename1 + ".out 2>&1"; // Redirect stderr to stdout
    const char *compile = command.c_str();

    while (true)
    {
        if (chdir(logs) != 0)
        {
            cout << "creating logs folder" << endl;
            system("mkdir logs");
        }
        else
        {
            chdir(back);
        }
        FILE *pipe = popen(compile, "r");
        if (!pipe)
        {
            std::cerr << "Error opening pipe." << std::endl;
            return 1;
        }

        char buffer[128];
        std::string result = "";

        // Read the output of the command and store it in a string
        while (fgets(buffer, sizeof(buffer), pipe) != nullptr)
        {
            result += buffer;
        }

        // Close the pipe
        pclose(pipe);

        logName = ("./logs/log_" + filename1 + "_" + timeLog + ".txt").c_str();
        fstream logger;
        if (firstTime == 0)
        {
            logger.open(logName, ios::out);
            if (logger.is_open())
            {
                if (!result.empty())
                {
                    logger << "First attempted compile at " << getTimeStr() << endl;
                    cout << "Error code detected..." << endl;
                    cout << "File is not a cpp file, is not accessible, or has an error to begin with..." << endl;
                    cout << "Logging Errors..." << endl;
                    cout << "Check Log to see errors" << endl;
                    cout << "Terminating code" << endl;
                    logger << result << endl;
                    return 1;
                }

                logger << "First attempted compile at " << getTimeStr() << endl;
                logger.close();
            }
            firstTime++;
        }
        else
        {
            logger.open(logName, ios::app);
            if (logger.is_open())
            {
                if (!result.empty())
                {
                    cout << "error detected..." << endl;
                    cout << "Logging error" << endl;
                    logger << "Error displayed here if there are any: " << endl;
                    logger << result << endl;
                }
                cout << "Attempted compiled at " << getTimeStr() << endl;
                logger << "Attempted compiled at " << getTimeStr() << endl;
                logger.close();
            }
        }
        sleep_for(seconds(timer));
    }
}
