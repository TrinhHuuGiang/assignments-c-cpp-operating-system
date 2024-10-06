
/********************************************************************************
* Definitions
********************************************************************************/
#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;
/********************************************************************************
* Code
********************************************************************************/
// argc : argument cout
// argv : argument vector
int main(int argc, const char** argv)
{
    int check = argc>1?0:1;
    /*
    * [check]
    * - if nothing input -> check = 1
    * - else -> check = 0
    */
    if(check)
    {
        cout << "File input nothing\n";
        return -1;
    }
    //else if user input something, print ignore $0
    for(int i = 1; i < argc; i++)
    {
        cout << setw(4) << i << ". " << argv[i] << '\n';
    }
    int number;
    while (true) {
        cout << "Enter the number in the menu to delete."<<endl;
        cout << "(Enter 0 if you don't want)\n->";
        cin >> number;

        if(cin.fail() || number == 0)
        {
            return 0;//user don't want to delete anything
        }
        // Check if the number is valid
        else if (cin.fail() || number < 1 || number >= argc) {
            cin.clear(); // Reset cin status
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the remaining characters
            cout << "Re-enter valid number 1 - " << argc - 1 << ".\n";
        } else {
            break; // Exit the loop when entered correctly
        }
    }
    cout << argv[number] << endl;

    return number; // anything ok

}