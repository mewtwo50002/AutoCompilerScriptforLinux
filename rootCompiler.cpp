#include <iostream>
#include <chrono>
#include <thread>
#include <time.h>
#include <fstream>
#include <string>
#include <unistd.h>
#include <ctype.h>
using namespace std;
using namespace std::this_thread;
using namespace std::chrono;






//
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


//Change how long it will wait befor compiling again
int timer = 5;


/* Templates
------------------------
child folders
------------------------
if (folderInput ==  ::toupper(class.firstinitial)|| folderInput == class.firstinitial)
    {
        former = former + class.name +"/";
        retry = false;
    }
------------------------
*/




//Prototype Variables
string getTimeStr();
string getTime();

//Dont touch the rest
string folderI;
string former = baseFolder.name + "/";
string filename1, filename2;
string logName;
bool retry = true;
int number;
int firstTime = 0;
auto timeLog = getTime();
const char * back = "..";
const char * logs = "logs";
const char * folderChange;

//variable definitions
int main()
{
    //add classes declerations
    baseFolder.name = "cs120";
    baseFolder.firstinitial = 'c';

    
    assignmentFolder.name = "Assignment";
    assignmentFolder.firstinitial = 'a';

    
    labsFolder.name = "Labs";
    labsFolder.firstinitial = 'l';

    
    assignmentChild.name = "assignment";
    labsChild.name = "lab";

    string former = baseFolder.name + "/";
    
    system("clear");
    system("clear");
    cout<<"What folder would you like to go to ("<< assignmentFolder.firstinitial <<"\\" << labsFolder.firstinitial <<"): ";
    cin>>folderI;
    
    char folderInput = folderI[0];
    
    
    
    do
    {
        if (folderInput ==  toupper(assignmentFolder.firstinitial)|| folderInput == assignmentFolder.firstinitial)
        {
            former = former + assignmentFolder.name +"/";
            retry = false;
        }else if(folderInput == toupper(labsFolder.firstinitial) || folderInput == labsFolder.firstinitial)
        {
            former = former + labsFolder.name + "/";
            retry = false;
        }else //Add more if statements for secondary folders
        {
            retry = true;
        }
    } while (retry == true);

    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<"what is the lab or assignment number?: ";
    cin>>number;
    cout<<endl;
    cout<<endl;
    cout<<endl;

    //change this function below to add more else-if statments to make to add more folders and letters
    if (folderInput ==  toupper(assignmentFolder.firstinitial)|| folderInput == assignmentFolder.firstinitial)
    {
        former = former + (assignmentChild.name + to_string(number));

    }else if (folderInput == toupper(labsFolder.firstinitial)|| folderInput == labsFolder.firstinitial)
    {
        former = former + (labsChild.name + to_string(number));
    }
    folderChange = former.c_str();
    if (chdir(folderChange) != 0)
    {
        cerr << "Error changing directory" << endl;
        return 1; // Exit with an error code
    }

    system("ls");
    cout<<"Whats the name of the file you want to compile without the .cpp: ";
    cin>>filename1;

    filename2 = filename1 + ".cpp";
    string command = "g++ " + filename2 + " -o " + filename1 + ".out";
    const char *compile = command.c_str();
    
    while (true)
    {
        if (chdir(logs) != 0)
    {
        cout << "creating logs folder" << endl;
        system("mkdir logs");
    }else
    {
        chdir(back);
    }

    logName = "./logs/log_" + filename1 + "_" + timeLog + ".txt";
    fstream logger;
    if (firstTime == 0)
        {
            logger.open(logName,ios::out);
            if (logger.is_open())
            {
                logger<<"Error codes displyed here if there are any: ";
                logger<<system(compile)<<endl;
                cout<<"First atempted compile at "<< getTimeStr()<<endl;
                logger<<"atecompiled at "<< getTimeStr()<<endl;
                logger.close();
            }
            firstTime++;
    }else
        {
            logger.open(logName, ios::app);
            if (logger.is_open())
            {
                logger<<"Error codes displyed here if there are any: ";
                logger<<system(compile)<<endl;
                cout<<"compiled at "<< getTimeStr()<<endl;
                logger<<"compiled at "<< getTimeStr()<<endl;
                logger.close();
            }
        }
    sleep_for(seconds(timer));
    }
    
    

}
string getTimeStr(){
    time_t now = chrono::system_clock::to_time_t(chrono::system_clock::now());
    string s(30, '\0');
    strftime(&s[0], s.size(), "%Y-%m-%d_%H:%M:%S", localtime(&now));
    return s;
}
string getTime(){
    time_t now = system_clock::to_time_t(system_clock::now());
    string s(30, '\0');
    strftime(&s[0], s.size(), "%Y_%m_%d_%H_%M_%S", localtime(&now));
    return s;
}