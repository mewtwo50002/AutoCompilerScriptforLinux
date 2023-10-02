#include <iostream>
#include <chrono>
#include <thread>
#include <time.h>
#include <fstream>
#include <string>
#include <unistd.h>

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

std::string getTimeStr(){
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::string s(30, '\0');
    std::strftime(&s[0], s.size(), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    return s;
}

int main()
{
    string folder;
    string former = "cs120/";
    bool retry = true;
    int number;
    string filename1, filename2;
    int firstTime = 0;
    string logName;

    system("clear");
    system("clear");
    cout<<"What folder would you like to go to(A/L): ";
    cin>>folder;

    do
    {
        if (folder == "a" || folder == "A")
        {
            former = former + "Assignment/";
            retry = false;
        }else if(folder == "l" || folder == "L")
        {
            former = former + "Labs/";
            retry = false;
        }else
        {
            retry = true;
        }
    } while (retry == true);
    
    cout<<"what is the lab or assignment number?: ";
    cin>>number;

    if (folder == "a" || folder == "A")
    {
        former = former + ("assignment" + to_string(number));
    }else
    {
        former = former + ("lab" + to_string(number));
    }
    
    const char * consoleCommand = former.c_str();
    if (chdir(consoleCommand) != 0)
    {
        cerr << "Error changing directory" << endl;
        return 1; // Exit with an error code
    }

    system("ls");
    cout<<"Whats the name of the file you want to compile without the .cpp: ";
    cin>>filename1;
    
    filename2 = filename1 + ".cpp";
    string command = "g++ " + filename2 + " -o " + filename1;
    const char * compile = command.c_str();
    
    while (true)
    {
        system(compile);
        
        logName = "log_" + filename1 + ".txt";
        fstream myFile1;
        
        if (firstTime == 0)
        {
            myFile1.open(logName,ios::out);
            if (myFile1.is_open())
            {
                cout<<"First compiled at "<< getTimeStr()<<endl;
                myFile1<<"compiled at "<< getTimeStr()<<endl;
                myFile1.close();
            }
            firstTime++;
        }else
        {
            myFile1.open(logName, ios::app);
            if (myFile1.is_open())
            {
                cout<<"compiled at "<< getTimeStr()<<endl;
                myFile1<<"compiled at "<< getTimeStr()<<endl;
                myFile1.close();
            }
        }
        
        
        
        
        

        sleep_for(seconds(5));
    }
    
    

}