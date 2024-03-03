// Add two Numbers using Linked List

#include "../Linked List/LinkedList.cpp"
#include <iostream>
#include <limits.h>

using namespace std;

int getCarry(int number)
{
    if ((number / 10) >= 1)
    {
        return number / 10;
    }
    return 0;
}

void addNumbers(Singly<int> *head, Singly<int> *l1, Singly<int> *l2, int carry = 0)
{
    if (l1 == NULL && l2 == NULL)
    {
        if (carry == 0)
        {
            return;
        }
        else
        {
            head->next = new Singly<int>(carry);
            return;
        }
    }

    int sum;
    if (l1 == NULL)
    {
        sum = l2->value + carry;
        carry = getCarry(sum);
        if (carry == 0)
        {
            head->next = new Singly<int>(sum);
            addNumbers(head->next, l1, l2->next, carry);
        }
        else
        {
            head->next = new Singly<int>(sum % 10);
            addNumbers(head->next, l1, l2->next, carry);
        }
    }
    else if (l2 == NULL)
    {
        sum = l1->value + carry;
        carry = getCarry(sum);
        if (carry == 0)
        {
            head->next = new Singly<int>(sum);
            addNumbers(head->next, l1->next, l2, carry);
        }
        else
        {
            head->next = new Singly<int>(sum % 10);
            addNumbers(head->next, l1->next, l2, carry);
        }
    }
    else
    {
        sum = l1->value + l2->value + carry;
        carry = getCarry(sum);
        if (carry == 0)
        {
            head->next = new Singly<int>(sum);
            addNumbers(head->next, l1->next, l2->next, carry);
        }
        else
        {
            head->next = new Singly<int>(sum % 10);
            addNumbers(head->next, l1->next, l2->next, carry);
        }
    }
}

void addNumbersLoop(Singly<int> *head, Singly<int> *l1, Singly<int> *l2)
{
    int sum;
    int carry = 0;
    while (l1 != NULL || l2 != NULL)
    {
        if (l1 == NULL)
        {
            sum = l2->value + carry;
            carry = getCarry(sum);
            if (carry == 0)
            {
                head->next = new Singly<int>(sum);
            }
            else
            {
                head->next = new Singly<int>(sum % 10);
            }

            head = head->next;
            l2 = l2->next;
        }
        else if (l2 == NULL)
        {
            sum = l1->value + carry;
            carry = getCarry(sum);
            if (carry == 0)
            {
                head->next = new Singly<int>(sum);
            }
            else
            {
                head->next = new Singly<int>(sum % 10);
            }

            head = head->next;
            l1 = l1->next;
        }
        else
        {
            sum = l1->value + l2->value + carry;
            carry = getCarry(sum);
            if (carry == 0)
            {
                head->next = new Singly<int>(sum);
            }
            else
            {
                head->next = new Singly<int>(sum % 10);
            }

            head = head->next;
            l1 = l1->next;
            l2 = l2->next;
        }
    }

    if (carry != 0)
    {
        head->next = new Singly<int>(carry);
    }
}

void printLL(Singly<int> *node)
{
    if (node == NULL)
    {
        return;
    }

    cout << node->value << " ";
    printLL(node->next);
}

void addTwoNumbers(Singly<int> *l1, Singly<int> *l2)
{
    Singly<int> *head = new Singly<int>(-1);

    addNumbersLoop(head, l1, l2);

    cout << endl;
    printLL(head->next);
    cout << endl;
}

// ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {

// }

int reverse(int number)
{
    long long reversed = 0;

    while (number != 0)
    {

        reversed = (reversed * 10) + (number % 10);

        if (reversed < INT32_MIN || reversed > INT32_MAX)
        {
            return 0;
        }

        number /= 10;
    }

    return reversed;
}

bool isPalindrome(int x)
{
    if (x < 0)
    {
        return false;
    }

    int temp = x;
    long long reversed = 0;

    while (temp != 0)
    {
        reversed = (reversed * 10) + (temp % 10);

        temp /= 10;
    }

    if (x == reversed)
    {
        return true;
    }
    else
    {
        return false;
    }
}

#include <unordered_map>

void prepareRomanTable(unordered_map<int, char> &romanTable)
{
    romanTable[1] = 'I';
    romanTable[5] = 'V';
    romanTable[10] = 'X';
    romanTable[50] = 'L';
    romanTable[100] = 'C';
    romanTable[500] = 'D';
    romanTable[1000] = 'M';
}

#include <string.h>

int exceptionalCases(string str)
{
    if(str == "CM"){
        return 900;
    }
    else if(str == "CD"){
        return 400;
    }
    else if(str == "XC"){
        return 90;
    }
    else if(str == "XL"){
        return 40;
    }
    else if(str == "IX"){
        return 9;
    }
    else if(str == "IV"){
        return 4;
    }
    else{
        return 0;
    }
}

// continue from here
int romanToInt(string s) {
    int length = s.length();

    int answer = 0;
    int exceptionalCase = 0;
    string temp;

    for(int i=0;i<length;i++){
        cout<<s[i]<<endl;
        if((i+1) < length){
            cout<<"inside checking condition"<<endl;
            temp = (s.at(i) + s.at(i+1));
            exceptionalCase = exceptionalCases(temp);
        }
        cout<<"temp: "<<temp<<endl;
        cout<<"exceptional case: "<<exceptionalCase<<endl;

        if(exceptionalCase != 0){
            answer += exceptionalCase;
            i += 2;
            exceptionalCase = 0;
            continue;
        }

        if(s[i] == 'M'){
            answer += 1000;
        }
        else if(s[i] == 'D'){
            answer += 500;
        }
        else if(s[i] == 'C'){
            answer += 100;
        }
        else if(s[i] == 'L'){
            answer += 50;
        }
        else if(s[i] == 'X'){
            answer += 10;
        }
        else if(s[i] == 'V'){
            answer += 5;
        }
        else{
            answer += 1;
        }
    }
}

string intToRoman(int num)
{
    string answer;

    while (num != 0)
    {
        if (num >= 1000)
        {
            answer.push_back('M');
            num -= 1000;
        }
        else if (num < 1000 && num >= 900)
        {
            answer.push_back('C');
            answer.push_back('M');
            num -= 900;
        }
        else if (num < 900 && num >= 500)
        {
            answer.push_back('D');
            num -= 500;
        }
        else if (num < 500 && num >= 400)
        {
            answer.push_back('C');
            answer.push_back('D');
            num -= 400;
        }
        else if (num < 400 && num >= 100)
        {
            answer.push_back('C');
            num -= 100;
        }
        else if (num < 100 && num >= 90)
        {
            answer.push_back('X');
            answer.push_back('C');
            num -= 90;
        }
        else if (num < 90 && num >= 50)
        {
            answer.push_back('L');
            num -= 50;
        }
        else if (num < 50 && num >= 40)
        {
            answer.push_back('X');
            answer.push_back('L');
            num -= 40;
        }
        else if (num < 40 && num >= 10)
        {
            answer.push_back('X');
            num -= 10;
        }
        else if (num == 9)
        {
            answer.push_back('I');
            answer.push_back('X');
            num -= 9;
        }
        else if (num < 9 && num >= 5)
        {
            answer.push_back('V');
            num -= 5;
        }
        else if (num == 4)
        {
            answer.push_back('I');
            answer.push_back('V');
            num -= 4;
        }
        else
        {
            answer.push_back('I');
            num -= 1;
        }
    }

    return answer;
}

int main()
{
    // Singly<int> *temp;
    // Singly<int> *l1 = new Singly<int>(9);
    // temp = l1;
    // temp->next = new Singly<int>(9);
    // temp = temp->next;
    // temp->next = new Singly<int>(9);
    // temp = temp->next;
    // temp->next = new Singly<int>(9);
    // temp = temp->next;
    // temp->next = new Singly<int>(9);
    // temp = temp->next;
    // temp->next = new Singly<int>(9);
    // temp = temp->next;
    // temp->next = new Singly<int>(9);

    // Singly<int> *l2 = new Singly<int>(9);
    // temp = l2;
    // temp->next = new Singly<int>(9);
    // temp = temp->next;
    // temp->next = new Singly<int>(9);
    // temp = temp->next;
    // temp->next = new Singly<int>(9);

    // addTwoNumbers(l1, l2);

    // cout << "returned value: " << reverse(-112608788) << endl;

    // cout << "Is Palindrome: " << isPalindrome(11) << endl;

    // cout<<"Roman of Int Number: "<<intToRoman(1994)<<endl;

    cout<<"Int of Roman Number: "<<romanToInt("III")<<endl;

    return 0;
}