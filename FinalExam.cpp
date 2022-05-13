#include <iostream> 

using namespace std; 

int mystery2(int x, int y) {
    if (y == 0) {
        return x; 
    } else {
        cout << "X: " << x << " Y: " << y << endl; 
        return mystery2((y*10) + (x%10), (x/10)); 
    }
}

int main() {
    
    cout << mystery2(0, 41) / 2 << endl; 
    return 0; 
}