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
    std::strftime(&s[0], s.size(), "%Y-%m-%d_%H:%M:%S", std::localtime(&now));
    return s;
}

string getTime(){
    time_t now = system_clock::to_time_t(system_clock::now());
    string s(30, '\0');
    strftime(&s[0], s.size(), "%Y_%m_%d_%H_%M_%S", localtime(&now));
    return s;
}

int main()
{
    //Edit these variables with your file name
    string base = "cs120";
    string second = "Assignment";
    string third = "Labs";
    string secondChild = "assignment";
    string thirdChild = "lab";
    string secondCapital = "A";//First letter of the second variable Uppercase
    string secondLower = "a"; //First letter of the second variable Lowercase
    string thirdCapital = "L"; //First letter of the third variable Uppercase
    string thirdLower = "l"; // First letter of the third variable Lowercase
    //Dont touch the rest
    string folder;
    string former = "cs120/";
    bool retry = true;
    int number;
    string filename1, filename2;
    int firstTime = 0;
    string logName;
    const char * logs = "logs";
    const char * back = "..";
    auto timeLog = getTime();

    system("clear");
    system("clear");
    cout<<"What folder would you like to go to ("<<secondCapital <<"\\" <<thirdCapital<<"): ";
    cin>>folder;

    do
    {
        if (folder ==  secondCapital|| folder == secondLower)
        {
            former = former + second +"/";
            retry = false;
        }else if(folder == thirdCapital || folder == thirdLower)
        {
            former = former + third + "/";
            retry = false;
        }else
        {
            retry = true;
        }
    } while (retry == true);
    
    cout<<"what is the lab or assignment number?: ";
    cin>>number;

    if (folder == secondCapital || folder == secondLower)
    {
        former = former + (secondChild + to_string(number));
    }else
    {
        former = former + (thirdChild + to_string(number));
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
        //system(compile);
            if (chdir(logs) != 0)
        {
            cout << "creating logs folder" << endl;
            system("mkdir logs");
        }else
        {
            chdir(back);
        }

        logName = "./logs/log_" + filename1 + timeLog + ".txt";
        fstream myFile1;
        
        if (firstTime == 0)
        {
            myFile1.open(logName,ios::out);
            if (myFile1.is_open())
            {
                myFile1<<"Error codes displyed here if there are any: ";
                myFile1<<system(compile)<<endl;
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
                myFile1<<"Error codes displyed here if there are any: ";
                myFile1<<system(compile)<<endl;
                cout<<"compiled at "<< getTimeStr()<<endl;
                myFile1<<"compiled at "<< getTimeStr()<<endl;
                myFile1.close();
            }
        }
        
        
        
        
        

        sleep_for(seconds(5));
    }
    
    

}