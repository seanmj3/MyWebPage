#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    int height; 
    cin >> height;  
    for (int i = 1; i <= height; i++) {
        for (int j = 1; j <= i; j++) {
            cout << "\\"; 
        }
        cout << endl; 
    }

    for (int i = height - 1; i >= 1; i--) {
        for (int j = 1; j <= i; j++) {
            cout << "\\"; 
        }
        cout << endl; 
    }

    return 0; 
}