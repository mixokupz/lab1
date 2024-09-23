#include <iostream>
#include "CircularBuffer.h"
using namespace std;
int main(int, char**){
    CircularBuffer first = CircularBuffer(6);
    for(int i=0;i<6;i++){
        cout<<first[i];
    }cout<<endl;
    first.erase(0,2);
    for(int i=0;i<6;i++){
        cout<<first[i];
    }cout<<endl;
    
    return 0;
}
