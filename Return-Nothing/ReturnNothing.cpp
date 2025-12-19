// #include "../Ordered-Maps/OrderedMapsElement.cpp"
#include <iostream>
using namespace std;

template <typename DataType>
class ReturnNothing
{
private:
    DataType value;

public:
    ReturnNothing()
    {
        if constexpr ((is_same_v<DataType, int>) || (is_same_v<DataType, short>) || (is_same_v<DataType, long>) || (is_same_v<DataType, long long>) || (is_same_v<DataType, short int>) || (is_same_v<DataType, long int>) || (is_same_v<DataType, long long int>)){
            this->value = 0;
        }
        else if constexpr ((is_same_v<DataType, unsigned int>) || (is_same_v<DataType, unsigned short>) || (is_same_v<DataType, unsigned long>) || (is_same_v<DataType, unsigned long long>) || (is_same_v<DataType, unsigned short int>) || (is_same_v<DataType, unsigned long int>) || (is_same_v<DataType, unsigned long long int>)){
            this->value = 0;
        }
        else if constexpr ((is_same_v<DataType, float>) || (is_same_v<DataType, double>) || (is_same_v<DataType, long double>)){
            this->value = 0.0;
        }
        else if constexpr ((is_same_v<DataType, char>)){
            this->value = '\0';
        }
        else if constexpr ((is_same_v<DataType, bool>)){
            this->value = false;
        }
        else if constexpr ((is_same_v<DataType, string>)){
            this->value = "";
        }
        else if constexpr ((is_same_v<DataType, char *>)){
            this->value = new char[1];
            this->value[0] = '\0';
        }
        else if constexpr ((sizeof(DataType)) == 8){
            this->value = NULL;
        }
    }

    ReturnNothing(DataType value){
        this->value = value;
    }

    DataType DefaultValue(){
        if constexpr ((is_same_v<DataType, char *>)){
            DataType temp = new char[1];
            strcpy(temp, this->value);
            return temp;    
        }

        return this->value;
    }

    void SetValue(DataType value){
        if constexpr ((is_same_v<DataType, char *>)){
            DataType temp = new char[1];
            strcpy(temp, value);
            this->value = temp;
            return;
        }

        this->value = value;
    }
};

// int main()
// {
//     return 0;
// }