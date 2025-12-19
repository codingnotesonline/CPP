#include <iostream>
#include <cstring>
#include <initializer_list>
using namespace std;

class String
{
private:
    int MaxLength;
    int Length;
    char *storage;
    bool restricted;

    void ReInitializeArray()
    {
        char *oldStr = this->storage;
        this->MaxLength += this->MaxLength;
        this->MaxLength--;
        this->storage = new char[MaxLength];

        for (int i = 0; i < this->Length; i++)
        {
            this->storage[i] = oldStr[i];
        }

        delete oldStr;
    }

    int getLength(char *str)
    {
        char ch = str[0];

        int count = 0;
        int i = 0;
        while (ch != '\0')
        {
            count++;
            i++;
            ch = str[i];
        }

        return count;
    }

public:
    String()
    {
        this->restricted = false;
        this->MaxLength = 100;
        this->MaxLength++;
        this->storage = new char[MaxLength];
        this->Length = 0;
        this->storage[0] = '\0';
    }
    String(int length)
    {
        this->restricted = true;
        this->MaxLength = length;
        this->MaxLength++;
        this->storage = new char[MaxLength];
        this->Length = 0;
        this->storage[0] = '\0';
    }

    String(char *str) {
        this->Length = this->getLength(str);
        this->storage = new char[Length + 1];
        strcpy(this->storage, str);
    }

    String(String &original) {
        this->Length = original.Length;
        this->storage = new char[Length + 1];
        strcpy(this->storage, original.storage);
    }

    ~String()
    {
        this->MaxLength = 0;
        this->Length = 0;
        delete[] this->storage;
    }

    void pushBack(char ch)
    {
        if(this->restricted && (this->Length == this->MaxLength)){
            cout<<"Container Overflow"<<endl;
            return;
        }

        if (!this->restricted && (this->Length == (this->MaxLength - 1)))
        {
            this->ReInitializeArray();
        }

        this->storage[Length] = ch;
        this->Length++;
        this->storage[Length] = '\0';
    }

    char popBack()
    {
        if (this->Length == 0)
        {
            return '\0';
        }

        char ch;
        ch = this->storage[Length - 1];
        this->storage[Length - 1] = '\0';
        this->Length--;

        return ch;
    }

    void pushFront(char ch)
    {
        if(this->restricted && (this->Length == this->MaxLength)){
            cout<<"Container Overflow"<<endl;
            return;
        }

        if (!this->restricted && (this->MaxLength == (this->Length + 1)))
        {
            this->ReInitializeArray();
        }

        for (int i = this->Length - 1; i >= 0; i--)
        {
            this->storage[i + 1] = this->storage[i];
        }

        this->storage[0] = ch;
        this->Length++;
        this->storage[Length] = '\0';
    }

    char popFront()
    {
        if (this->Length == 0)
        {
            return '\0';
        }

        char ch = this->storage[0];

        for (int i = 0; i < this->Length - 1; i++)
        {
            this->storage[i] = this->storage[i + 1];
        }

        this->Length--;
        this->storage[Length - 1] = '\0';

        return ch;
    }

    void pushBackWord(char *str)
    {
        int strlen = this->getLength(str);

        if(this->restricted && (this->MaxLength < (this->Length + strlen))){
            cout<<"Container Overflow"<<endl;
            return;
        }

        if (!this->restricted && (this->MaxLength <= (this->Length + strlen)))
        {
            this->ReInitializeArray();
        }

        int i = this->Length;
        int j = 0;

        int length = this->Length + strlen;

        for (i; i < length; i++)
        {
            this->storage[i] = str[j];
            j++;
            this->Length++;
        }

        this->storage[Length] = '\0';
    }

    void pushBackWord(String container)
    {
        char *str = container.getString();
        int strlen = this->getLength(str);

        if(this->restricted && (this->MaxLength < (this->Length + strlen))){
            cout<<"Container Overflow"<<endl;
            return;
        }

        if (!this->restricted && (this->MaxLength <= (this->Length + strlen)))
        {
            this->ReInitializeArray();
        }

        int i = this->Length;
        int j = 0;

        int length = this->Length + strlen;

        for (i; i < length; i++)
        {
            this->storage[i] = str[j];
            j++;
            this->Length++;
        }

        this->storage[Length] = '\0';
    }

    void pushFrontWord(char *str)
    {
        int strlen = this->getLength(str);

        if(this->restricted && (this->MaxLength < (this->Length + strlen))){
            cout<<"Container Overflow"<<endl;
            return;
        }

        if (!this->restricted && (this->MaxLength <= (this->Length + strlen)))
        {
            this->ReInitializeArray();
        }

        int i = this->Length - 1;
        for (i; i >= 0; i--)
        {
            this->storage[i + strlen] = this->storage[i];
        }

        this->Length += strlen;
        this->storage[Length] = '\0';

        for (int i = 0; i < strlen; i++)
        {
            this->storage[i] = str[i];
        }
    }
    
    void pushFrontWord(String container)
    {
        char *str = container.getString();
        int strlen = this->getLength(str);

        if(this->restricted && (this->MaxLength < (this->Length + strlen))){
            cout<<"Container Overflow"<<endl;
            return;
        }

        if (!restricted && (this->MaxLength <= (this->Length + strlen)))
        {
            this->ReInitializeArray();
        }

        int i = this->Length - 1;
        for (i; i >= 0; i--)
        {
            this->storage[i + strlen] = this->storage[i];
        }

        this->Length += strlen;
        this->storage[Length] = '\0';

        for (int i = 0; i < strlen; i++)
        {
            this->storage[i] = str[i];
        }
    }

    bool compare(char *str)
    {
        int i;
        for (i = 0; i < this->Length; i++)
        {
            if ((str[i] != '\0' && this->storage[i] != '\0') && this->storage[i] != str[i])
            {
                return false;
            }
        }

        if (this->storage[i] != '\0' || str[i] != '\0')
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    void insert(char ch, int index)
    {
        if (index > (this->Length + 1) || index <= 0)
        {
            return;
        }

        if (index == 1)
        {
            this->pushFront(ch);
            return;
        }

        if (index == (this->Length + 1))
        {
            this->pushBack(ch);
            return;
        }

        for (int i = this->Length - 1; i >= (index - 1); i--)
        {
            this->storage[i + 1] = this->storage[i];
        }

        this->storage[index - 1] = ch;
        this->Length++;
        this->storage[Length] = '\0';
    }

    char erase(int index)
    {
        if (index > this->Length || index <= 0)
        {
            return '\0';
        }

        if (index == 1)
        {
            return this->popFront();
        }

        if (index == this->Length)
        {
            return this->popBack();
        }

        char ch = this->storage[index - 1];

        for (int i = index - 1; i < this->Length; i++)
        {
            this->storage[i] = this->storage[i + 1];
        }

        this->Length--;
        this->storage[Length] = '\0';

        return ch;
    }

    int remove(char ch)
    {
        char temp;

        temp = this->storage[0];

        int i = 0;
        while (temp != '\0')
        {
            if (temp == ch)
            {
                this->erase(i + 1);
                return 0;
            }
            i++;
            temp = this->storage[i];
        }

        return -1;
    }

    bool empty()
    {
        if (this->Length == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    char at(int index)
    {
        if (index < this->Length)
        {
            return this->storage[index - 1];
        }
        else
        {
            return '\0';
        }
    }

    char *getString()
    {
        char *temp = new char[Length];

        char ch = this->storage[0];

        int i = 0;
        while (ch != '\0')
        {
            temp[i] = ch;
            i++;
            ch = this->storage[i];
        }

        temp[i] = '\0';

        return temp;
    }

    void insertString(char *str)
    {
        int strlen = this->getLength(str);

        if(this->restricted && (this->MaxLength < strlen)){
            cout<<"Container Overflow"<<endl;
            return;
        }

        if (!restricted && (this->MaxLength <= strlen))
        {
            this->ReInitializeArray();
        }

        char ch = str[0];

        int i = 0;
        while (ch != '\0')
        {
            this->storage[i] = ch;
            i++;
            ch = str[i];
        }

        this->Length = strlen;
        this->storage[i] = '\0';
    }

    void clear()
    {
        if (this->Length == 0)
        {
            return;
        }

        this->Length = 0;
        this->storage[0] = '\0';
    }

    int length()
    {
        return this->Length;
    }

    int maxLength(){
        return this->MaxLength;
    }

    char *begin()
    {
        return &this->storage[0];
    }

    char *end()
    {
        return &this->storage[Length - 1];
    }

    char front()
    {
        return this->storage[0];
    }

    char back()
    {
        return this->storage[Length - 1];
    }

    String operator+(String str)
    {
        this->pushBackWord(str.storage);
        return *this;
    }

    String operator+(char *str)
    {
        this->pushBackWord(str);
        return *this;
    }

    bool operator==(String str)
    {
        return this->compare(str.storage);
    }

    bool operator==(char *str)
    {
        return this->compare(str);
    }

    bool operator!=(String str)
    {
        return ((this->compare(str.storage)) ? false : true);
    }

    bool operator!=(char *str)
    {
        return ((this->compare(str)) ? false : true);
    }

    void operator=(char *str)
    {
        this->insertString(str);
    }

    void operator=(String str)
    {
        this->insertString(str.storage);
    }

    char &operator[](int index){
        return this->storage[index];
    }
};

ostream &operator<<(ostream &COUT, String str)
{
    COUT << str.getString() << endl;
    return COUT;
}

istream &operator>>(istream &CIN, String &str)
{
    int maxLength = str.maxLength();
    char *temp = new char[maxLength];
    cin.getline(temp, maxLength);
    str.insertString(temp);
    delete[] temp;

    return CIN;
}

// int main()
// {
//     String s;

//     cout<<"Enter the String: "<<endl;
//     cin >> s;

//     cout<<s.getString()<<endl;
//     char ch[] = "qwertyy";
//     cout<<"Comapring String: "<<s.compare(ch)<<endl;
//     s.insert('d', 4);
//     cout<<s.getString()<<endl;
//     cout<<"returned value: "<<s.erase(4)<<endl;
//     cout<<s.getString()<<endl;

//     return 0;
// }