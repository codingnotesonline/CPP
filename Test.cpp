#include <iostream>
using namespace std;

template<typename T1> 
T1 max(T1 first, T1 second){
    if(first > second){
        return first; 
    }
    else{
        return second;
    }
}

int main(){
    return 0;
}