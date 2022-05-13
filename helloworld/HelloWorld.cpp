#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    int numSteps = 3;
    cin >> numSteps; 
    int num = 1; 
 

    for (int i = 1; i <= numSteps; i++) {
        for (int j = 1; j <= i; j++) {
            cout << j; 
        }
        cout << endl;  
    }
    
    
    return 0; 
}