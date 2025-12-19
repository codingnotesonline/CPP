#include <iostream>
using namespace std;

template <typename KeyDataType, typename ValueDataType>
class OrderedMapsElement
{
public:
    int id;
    KeyDataType key;
    ValueDataType value;

    OrderedMapsElement()
    {
        this->id = 0;
    }

    OrderedMapsElement(int id, KeyDataType key, ValueDataType value)
    {
        this->id = id;
        this->key = key;
        this->value = value;
    }
};