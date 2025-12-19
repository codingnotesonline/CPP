#include <iostream>
using namespace std;

template <typename KeyDataType, typename ValueDataType>
class HashMapElement
{
public:
    KeyDataType Key;
    ValueDataType Value;

    HashMapElement(KeyDataType key, ValueDataType value){
        this->Key = key;
        this->Value = value;
    }
};