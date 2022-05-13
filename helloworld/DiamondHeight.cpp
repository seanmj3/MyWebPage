#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

int main()
{
    int height = 6;  
    int filler = height / 2;
    int incr = filler;
    int width2 = filler + 2;  
    for (int i = 1; i <= filler; i++) {
        int width;
        if (i > 1) {
            width = (i * 2) - 1; 
        }
        cout << setw(incr);
        cout << "/" << setw(width) << "\\"; 
        cout << endl; 
        incr -= 1;
    }

    for (int i = filler; i >= 1; i--) { 
        // if (i < filler) {
        //     width2 = (i * 2); 
        // }
        cout << setw(incr + 1);
        cout << "\\" << setw(width2) << "/"; 
        cout << endl; 
        incr += 1;
        width2-=2;
    }
    
    return 0; 
}