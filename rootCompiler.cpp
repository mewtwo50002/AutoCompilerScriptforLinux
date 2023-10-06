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
    char firstinitial;
};

Folder baseFolder;
Folder assignmentFolder;
Folder labsFolder;
childFolder assignmentChild;
childFolder labsChild;

// Prototype Variables
string getTimeStr();
string getTime();
void dirChanger();
void secondaryGraber();
int childGraber();
int compiler();

// Change how long it will wait befor compiling again
int timer = 5;
// add more secondary files here

// add classes declerations

// variable definitions
string folderI;
string former = baseFolder.name + "/";
string filename1, filename2;
string logName;
bool retry = true;
int number;
int firstTime = 0;
auto timeLog = getTime();
const char *back = "..";
const char *logs = "logs";
const char *compile;
const char *folderChange;
char folderInput;

int main()
{
    baseFolder.name = "cs120";
    baseFolder.firstinitial = 'c';

    assignmentFolder.name = "Assignment";
    assignmentFolder.firstinitial = 'a';

    labsFolder.name = "Labs";
    labsFolder.firstinitial = 'l';

    assignmentChild.name = "assignment";
    labsChild.name = "lab";

    former = baseFolder.name + "/";
    
    dirChanger();
    secondaryGraber();

    childGraber();
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
    string former = baseFolder.name + "/";

    system("clear");
    system("clear");
    cout << "What folder would you like to go to (" << assignmentFolder.firstinitial << "\\" << labsFolder.firstinitial << "): ";
    cin >> folderI;

    folderInput = folderI[0];
}
void secondaryGraber()
{
    do
    {
        if (folderInput == toupper(assignmentFolder.firstinitial) || folderInput == assignmentFolder.firstinitial)
        {
            former = former + assignmentFolder.name + "/";
            retry = false;
        }
        else if (folderInput == toupper(labsFolder.firstinitial) || folderInput == labsFolder.firstinitial)
        {
            former = former + labsFolder.name + "/";
            retry = false;
        }
        else // Add more if statements for secondary folders
        {
            retry = true;
        }
    } while (retry == true);
}
int childGraber()
{
    cout << endl;
    cout << endl;
    cout << endl;
    cout << "what is the lab or assignment number?: ";
    cin >> number;
    cout << endl;
    cout << endl;
    cout << endl;
    //----------------------------------------------
    // change this function below to add more else-if statments to make to add more folders and letters
    if (folderInput == toupper(assignmentFolder.firstinitial) || folderInput == assignmentFolder.firstinitial)
    {
        former = former + (assignmentChild.name + to_string(number));
    }
    else if (folderInput == toupper(labsFolder.firstinitial) || folderInput == labsFolder.firstinitial)
    {
        former = former + (labsChild.name + to_string(number));
    }
    folderChange = former.c_str();
    cout<<former<<endl;
    if (chdir(folderChange) != 0)
    {
        cerr << "Error changing directory" << endl;
        return 1; // Exit with an error code
    }
}
int compiler()
{
    system("ls");
    cout << "Whats the name of the file you want to compile without the .cpp: ";
    cin >> filename1;
    //----------------------------------------------
    filename2 = filename1 + ".cpp";
    string command = "g++ " + filename2 + " -o " + filename1 + ".out";
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

        logName = ("./logs/log_" + filename1 + "_" + timeLog + ".txt").c_str();
        fstream logger;
        if (firstTime == 0)
        {
            logger.open(logName, ios::out);
            if (logger.is_open())
            {
                if (system(compile) != 0)
                {
                    logger << "Error code detected..." << endl;
                    logger << "File is not a cpp  file or is not accessible" << endl;
                    logger<< "Terminating code" << endl;
                    logger << system(compile) << endl;
                    return (1);
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
                logger << "Error codes displyed here if there are any: ";
                logger << system(compile) << endl;
                cout << "Attempted compiled at " << getTimeStr() << endl;
                logger << "Attempted compiled at " << getTimeStr() << endl;
                logger.close();
            }
        }
        sleep_for(seconds(timer));
    }
}
