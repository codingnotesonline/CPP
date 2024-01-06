#include <iostream>
using namespace std;

template <typename DataType1, typename DataType2, typename DataType3>
class triplet
{
public:
    DataType1 first;
    DataType2 second;
    DataType3 third;

    void make_triplet(DataType1 first, DataType2 second, DataType3 third)
    {
        this->first = first;
        this->second = second;
        this->third = third;
    }
};

// int main(){

//     return 0;
// }