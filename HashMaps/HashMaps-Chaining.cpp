#include "./HashMapLinkedList.cpp"
#include "./HashMapElement.cpp"
#include "../Return-Nothing/ReturnNothing.cpp"
#include <iostream>
#include <math.h>
#include <limits.h>
using namespace std;

template <typename KeyDataType, typename ValueDataType>
class HashMapsChaining
{
private:
    SinglyLinkedList<HashMapElement<KeyDataType, ValueDataType> *> **bucket;
    int MaxSize;
    int bucketElements;
    float loadFactor;
    SinglyLinkedList<KeyDataType> *keys;
    ReturnNothing<ValueDataType> defaultReturn;

    long long generateHash(KeyDataType key, int size)
    {
        if constexpr ((is_same_v<KeyDataType, int>) || (is_same_v<KeyDataType, short>) || (is_same_v<KeyDataType, long>) || (is_same_v<KeyDataType, long long>))
        {
            KeyDataType copy = key;
            int iteration = (int(log10(copy)) + 1);
            long long sum = iteration * copy;
            srand(key);
            sum *= ((rand() % 3145739) + 1) + 196613;
            sum %= 130363;
            long long index = sum % size;
            return index;
        }

        else if constexpr ((is_same_v<KeyDataType, float>) || (is_same_v<KeyDataType, double>) || (is_same_v<KeyDataType, long double>))
        {
            KeyDataType copy = key;
            int decimal = int(key);
            long double fraction = copy - decimal;

            srand(decimal);
            long long sum = (rand() * fraction) + 1;
            sum *= decimal;
            srand(sum);
            sum *= ((rand() % 1572869) + 1) + 98317;
            sum %= 786433;
            long long index = sum % size;
            return index;
        }
        else if constexpr ((is_same_v<KeyDataType, char>))
        {
            int ascii = key;
            int iteration = (int(log10(ascii)) + 1);

            srand(ascii);
            long long sum = (rand() * iteration) + 1;
            sum += ascii;
            srand(sum);
            sum *= ((rand() % 6291469) + 1) + 393241;
            sum %= 786433;
            long long index = sum % size;
            return index;
        }
        else if constexpr ((is_same_v<KeyDataType, string>))
        {
            int length = key.length();
            int front = key[0];
            int last = key[length - 1];

            long long sum = length * front * last;
            sum /= length;
            sum += length;
            srand(sum);
            sum *= ((rand() % 108631) + 1) + 12289;
            sum %= 786433;
            long long index = sum % size;
            return index;
        }
        else
        {
            cout << "Please provide primitive datatype's only!!" << endl;
        }
    }

    bool checkLoadFactor()
    {
        if (((float(this->bucketElements) / float(this->MaxSize)) < this->loadFactor))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void ClearBucket(SinglyLinkedList<HashMapElement<KeyDataType, ValueDataType> *> **bucket, int size){
        for (int i = 0; i < size; i++)
        {
            if (bucket[i] != NULL)
            {
                Singly<HashMapElement<KeyDataType, ValueDataType> *> *head = bucket[i]->returnHead();
                while (head != NULL)
                {
                    delete head->value;
                    head = head->next;
                }
                delete bucket[i];
            }
        }
    }

    void ReinitializeBucket(){
        this->MaxSize += this->MaxSize;
        this->bucket = new SinglyLinkedList<HashMapElement<KeyDataType, ValueDataType> *> *[MaxSize];
        this->bucketElements = 0;
    }

    void RegenerateHash(){
        SinglyLinkedList<HashMapElement<KeyDataType, ValueDataType> *> **oldBucket = this->bucket;
        int oldSize = this->MaxSize;

        this->ReinitializeBucket();

        KeyDataType key;
        ValueDataType value;
        Singly<HashMapElement<KeyDataType, ValueDataType> *> *innerHead;
        Singly<KeyDataType> *head = this->keys->returnHead();

        long long hash;
        while(head != NULL){
            key = head->value;
            hash = this->generateHash(key, oldSize);
            innerHead = oldBucket[hash]->returnHead();

            while(innerHead != NULL){
                if(innerHead->value->Key == key){
                    value = innerHead->value->Value;
                }
                innerHead = innerHead->next;
            }
            this->insert(key, value);
            head = head->next;
        }

        this->ClearBucket(oldBucket, oldSize);
        delete[] oldBucket; 
    }

public:
    HashMapsChaining()
    {
        if (!((is_same_v<KeyDataType, int>) || (is_same_v<KeyDataType, short>) || (is_same_v<KeyDataType, long>) || (is_same_v<KeyDataType, long long>) || (is_same_v<KeyDataType, float>) || (is_same_v<KeyDataType, double>) || (is_same_v<KeyDataType, long double>) || (is_same_v<KeyDataType, char>) || (is_same_v<KeyDataType, string>)))
        {
            cout << "Please provide primitive datatype's only as Key!!" << endl;
            exit(1);
        }

        this->MaxSize = 1000;
        this->bucketElements = 0;
        this->loadFactor = 0.50;
        this->bucket = new SinglyLinkedList<HashMapElement<KeyDataType, ValueDataType> *> *[MaxSize];
        this->keys = new SinglyLinkedList<KeyDataType>();
        for (int i = 0; i < this->MaxSize; i++)
        {
            this->bucket[i] = NULL;
        }
    }

    ~HashMapsChaining()
    {
        this->MaxSize = 0;
        this->bucketElements = 0;
        this->loadFactor = 0.0;
        this->clear();
        delete this->keys;
        delete[] this->bucket;
    }

    ValueDataType at(KeyDataType key)
    {
        long long hash = this->generateHash(key, this->MaxSize);

        if (this->bucket[hash] == NULL)
        {
            return this->defaultReturn.DefaultValue();
        }

        Singly<HashMapElement<KeyDataType, ValueDataType> *> *head = this->bucket[hash]->returnHead();
        while (head != NULL)
        {
            if (head->value->Key == key)
            {
                return &head->value->Value;
            }
            head = head->next;
        }

        return this->defaultReturn.DefaultValue();
    }

    void insert(KeyDataType key, ValueDataType value)
    {
        long long hash = this->generateHash(key, this->MaxSize);

        HashMapElement<KeyDataType, ValueDataType> *element = new HashMapElement<KeyDataType, ValueDataType>(key, value);

        if (this->bucket[hash] == NULL)
        {
            this->bucket[hash] = new SinglyLinkedList<HashMapElement<KeyDataType, ValueDataType> *>();
        }

        Singly<HashMapElement<KeyDataType, ValueDataType> *> *head = this->bucket[hash]->returnHead();

        bool found = 0;
        while (head != NULL)
        {
            if (head->value->Key == key)
            {
                found = 1;
                head->value->Value = value;
                break;
            }
            head = head->next;
        }

        if (!found)
        {
            this->bucket[hash]->pushBack(element);
            this->keys->pushBack(key);
            this->bucketElements++;
        }
    }

    void erase(KeyDataType key)
    {
        long long hash = this->generateHash(key, this->MaxSize);

        if (this->bucket[hash] == NULL)
        {
            return;
        }

        Singly<HashMapElement<KeyDataType, ValueDataType> *> *head = this->bucket[hash]->returnHead();
        int index = 1;
        while (head != NULL)
        {
            if (head->value->Key == key)
            {
                break;
            }
            index++;
            head = head->next;
        }

        if (head == NULL)
        {
            return;
        }

        this->bucket[hash]->erase(index);
        this->keys->remove(key);
        this->bucketElements--;
    }

    void clear(){
        this->ClearBucket(this->bucket, this->MaxSize);
        // this->keys->clear();
        this->bucketElements = 0;
    }

    int size()
    {
        cout << "Checking Load Factor: " << this->checkLoadFactor() << endl;
        return this->bucketElements;
    }

    // void operator=(HashMapsChaining<KeyDataType, ValueDataType> &element){
        
    // }

    ValueDataType &operator[](KeyDataType key){
        long long hash = this->generateHash(key, this->MaxSize);

        if (this->bucket[hash] == NULL)
        {
            this->bucket[hash] = new SinglyLinkedList<HashMapElement<KeyDataType, ValueDataType> *>();
            HashMapElement<KeyDataType, ValueDataType> *element = new HashMapElement<KeyDataType, ValueDataType>(key, this->defaultReturn.DefaultValue());
            this->bucket[hash]->pushBack(element);
            this->keys->pushBack(key);
        }

        Singly<HashMapElement<KeyDataType, ValueDataType> *> *head = this->bucket[hash]->returnHead();
        while (head->next != NULL)
        {
            if (head->value->Key == key)
            {
                break;
            }
            
            head = head->next;
        }

        if(head->next == NULL){
            if (head->value->Key != key)
            {
                HashMapElement<KeyDataType, ValueDataType> *elem = new HashMapElement<KeyDataType, ValueDataType>(key, this->defaultReturn.DefaultValue());
                head->next = new Singly<HashMapElement<KeyDataType, ValueDataType> *>(elem);
                this->keys->pushBack(key);
                head = head->next;
            }
        }

        return head->value->Value;
    }


};

// int main()
// {
//     // HashMapsChaining<string, string> __1;

//     // __1.insert("Oggy and the Cockroaches", "Phd Artificial Intelligence");
//     // __1.insert("Jack", "Phd Biotechnology");
//     // __1.insert("Nobita", "Phd Robotics Engineering");
//     // __1.insert("Oly", "MS Fashion Designing");

//     // cout << (*__1.at("Oggy and the Cockroaches")) << endl;
//     // cout << (*__1.at("Nobita")) << endl;
//     // cout << (*__1.at("Oly")) << endl;
//     // cout << __1.size() << endl;

//     // __1.erase("Oly");

//     // // cout<<(*__1.at("Olly"))<<endl;
//     // cout << (*__1.at("Jack")) << endl;

//     // cout << __1.size() << endl;

//     HashMapsChaining<int, string> __1;
//     __1.insert(1, "Oggy");
//     __1.insert(2, "Jack");
//     __1.insert(3, "Nobita");
//     __1.insert(4, "Olly");
//     __1.insert(5, "Bob");
//     __1.insert(4, "Doraemon");

//     HashMapsChaining<int, string> __2;
//     __2.insert(1, "Big G");
//     __2.insert(2, "Sneech");
//     __2.insert(3, "Suzuka");
//     __2.insert(4, "Marky");
//     __2.insert(5, "Jeoy");
//     __2.insert(3, "Dee Dee");

//     // cout<<(*list.at(1))<<endl;
//     // cout<<(*list.at(2))<<endl;
//     // cout<<(*list.at(3))<<endl;
//     // cout<<(*list.at(4))<<endl;
//     // cout<<list.size()<<endl;

//     // list.erase(1);
//     // list.erase(3);

//     // // cout<<(*list.at(1))<<endl;
//     // cout<<(*list.at(2))<<endl;
//     // // cout<<(*list.at(3))<<endl;
//     // cout<<(*list.at(4))<<endl;
//     // cout<<list.size()<<endl;

//     // cout<<list.size()<<endl;

//     HashMapsChaining<double, string> megaList;

//     megaList.insert(15.24569, "Oggy");
//     megaList.insert(30.18637, "Bob");
//     megaList.insert(45.10667, "Nobita");
//     megaList.insert(60.39037, "Doraemon");

//     cout<<(*megaList.at(15.24569))<<endl;

//     megaList.erase(30.18637);


//     return 0;
// }