#include <iostream>
using namespace std;

// also work on static data members;

class Vehicle{
protected:
    float speed;
    float engineSize;
    int fuelCapacity;
    bool autoDrive;
    string color;

public:
    Vehicle(){
        this->speed = 0.0;
    }

    void operator+(float data){
        this->speed = data;
    }
};


class Truck: public Vehicle{
public:
    int towingCapacity;

    Truck(){
        this->towingCapacity = 0;
    }

    void operator+(int data){
        this->towingCapacity = data;
    }

    void print(){
        cout<<"towing capacity: "<<this->towingCapacity<<endl;
        cout<<"Speed: "<<this->speed<<endl;
    }
};

class Bus: public Vehicle{
public:
    int numbersofPassengers;
    float length;

    Bus(){
        this->numbersofPassengers = 0;
    }

    Bus operator+(Bus data){
        Bus temp;
        temp.autoDrive = (this->autoDrive || data.autoDrive);
        temp.color = this->color;
        temp.engineSize = min(this->engineSize, data.engineSize);
        temp.fuelCapacity = this->fuelCapacity + data.fuelCapacity;
        temp.length = max(this->length, data.length);
        temp.numbersofPassengers = max(this->numbersofPassengers, data.numbersofPassengers);
        temp.speed = this->speed + data.speed;
        return temp;
    }

    void operator+(int data){

    }

    void operator+(float data){

    }

    void operator=(Bus data){
        this->autoDrive = data.autoDrive;
        this->color = data.color;
        this->engineSize = data.engineSize;
        this->fuelCapacity = data.fuelCapacity;
        this->length = data.length;
        this->numbersofPassengers = data.numbersofPassengers;
        this->speed = data.speed;
    }

    bool operator==(Bus data){

        if(this->autoDrive != data.autoDrive){
            return false;
        }

        if(this->color != data.color){
            return false;
        }

        if(this->engineSize != data.engineSize){
            return false;
        }

        if(this->fuelCapacity != data.fuelCapacity){
            return false;
        }

        if(this->length != data.length){
            return false;
        }

        if(this->numbersofPassengers != data.numbersofPassengers){
            return false;
        }

        if(this->speed != data.speed){
            return false;
        }

        return true;
    }

    void operator++(){
        this->engineSize++;
        this->length++;
        this->numbersofPassengers++;
        this->speed++;
    }

    Bus operator++(int){
        Bus temp = *this;
        this->engineSize++;
        this->length++;
        this->numbersofPassengers++;
        this->speed++;
        return temp;
    }

    void operator--(){
        this->engineSize--;
        this->length--;
        this->numbersofPassengers--;
        this->speed--;
    }

    Bus operator--(int){
        Bus temp = *this;
        this->engineSize--;
        this->length--;
        this->numbersofPassengers--;
        this->speed--;
        return temp;
    }
};

int main(){
    Bus B;
    Vehicle V;

    // operator override will be occured (irrespective of return datatype/parameters datatype)
    Truck T;
    T.print();
    T + 4.5;
    T.print();
    T + 3;
    T.print();
    return 0;
}