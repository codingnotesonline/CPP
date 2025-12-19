#include "../HashMaps/HashMaps-Chaining.cpp"
#include "AVLTree-Maps.cpp"
#include "OrderedMapsElement.cpp"
// #include "../Return-Nothing/ReturnNothing.cpp"
// do not include this agian as it is already included in the upper included files
#include <iostream>
using namespace std;

template <typename KeyDataType, typename ValueDataType>
class OrderedMaps{
private:
    // We started assigning id's from 1
    int uniqueId;
    HashMapsChaining<KeyDataType, int> keyIds;
    AVLTree<OrderedMapsElement<KeyDataType, ValueDataType>> container;
    ReturnNothing<ValueDataType> defaultValue;

public:
    OrderedMaps(){
        this->uniqueId = 1;
    }

    void insert(KeyDataType key, ValueDataType value){
        OrderedMapsElement<KeyDataType, ValueDataType> element;
        this->keyIds[key] = this->uniqueId;
        element.id = this->uniqueId++;
        element.key = key;
        element.value = value;

        this->container.InsertData(element);
    }

    void erase(KeyDataType key){
        OrderedMapsElement<KeyDataType, ValueDataType> element;
        element.id = this->keyIds[key];
        element.key = key;

        this->container.DeleteData(element);
        this->keyIds.erase(key);
    }

    ValueDataType at(KeyDataType key){
        OrderedMapsElement<KeyDataType, ValueDataType> element;
        element.id = this->keyIds[key];
        element.key = key;

        return this->container.SearchData(element).value;
    }

    // this can be implemented after writing iterators
    // void print(){

    // }

    void clear(){
        this->keyIds.clear();
        this->container.clear();
    }

};

int main(){
    OrderedMaps<string, int> classData;
    classData.insert("Oggy", 8);
    cout<<"inserted 1"<<endl;
    classData.insert("Jack", 10);
    cout<<"inserted 2"<<endl;
    classData.insert("Bob", 12);
    cout<<"inserted 3"<<endl;
    classData.insert("Olly", 8);
    cout<<"inserted 4"<<endl;

    cout<<classData.at("Bob")<<endl;
    cout<<classData.at("Olly")<<endl;   
    // cout<<classData.at("Nobita")<<endl; 

    classData.erase("Bob");

    cout<<classData.at("Oggy")<<endl;   
    cout<<classData.at("Jack")<<endl;   

    classData.insert("Doraemon", 18);
    classData.insert("Degisugi", 16);
    classData.insert("Nobita", 14);

    return 0;
}