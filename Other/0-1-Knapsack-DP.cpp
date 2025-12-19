#include <iostream>
#include <queue>
#include <vector>
using namespace std;

class _0_1_KnapsackObject
{
public:
    string name;
    float weight;
    float profit;

    _0_1_KnapsackObject()
    {
        this->name = "Nothing";
        this->weight = 0;
        this->profit = 0;
    }

    _0_1_KnapsackObject(string name, float weight, float profit)
    {
        this->name = name;
        this->weight = weight;
        this->profit = profit;
    }

    void operator=(_0_1_KnapsackObject obj1)
    {
        this->name = obj1.name;
        this->profit = obj1.profit;
        this->weight = obj1.weight;
    }
};

int count = 0;

pair<float, vector<string>> _0_1_Knapsack(vector<_0_1_KnapsackObject> container, int bagCapacity, float profit, vector<string> objNames, vector<vector<pair<float, vector<string>>>> &record)
{
    count++;
    if (container.size() == 0 || bagCapacity == 0)
    {
        return make_pair(profit, objNames);
    }

    if (record[container.size() - 1][bagCapacity].first != -1)
    {
        return record[container.size() - 1][bagCapacity];
    }

    _0_1_KnapsackObject obj;
    obj = container[container.size() - 1];
    container.pop_back();

    if (obj.weight > bagCapacity)
    {
        return _0_1_Knapsack(container, bagCapacity, profit, objNames, record);
    }

    pair<float, vector<string>> included = _0_1_Knapsack(container, bagCapacity - obj.weight, profit + obj.profit, objNames, record);

    pair<float, vector<string>> notIncluded = _0_1_Knapsack(container, bagCapacity, profit, objNames, record);

    if (included.first >= notIncluded.first)
    {
        included.second.push_back(obj.name);
        return record[container.size()][bagCapacity] = included;
    }
    else
    {
        return record[container.size()][bagCapacity] = notIncluded;
    }
}

int main()
{
    vector<_0_1_KnapsackObject> container;
    // bagCapacity is of int datatype here, because here we d will not see any fraction
    int bagCapacity;

    container.push_back(_0_1_KnapsackObject("Obj1", 2, 10));
    container.push_back(_0_1_KnapsackObject("Obj2", 3, 5));
    container.push_back(_0_1_KnapsackObject("Obj3", 5, 15));
    container.push_back(_0_1_KnapsackObject("Obj4", 7, 7));
    container.push_back(_0_1_KnapsackObject("Obj5", 1, 6));
    container.push_back(_0_1_KnapsackObject("Obj6", 4, 18));
    container.push_back(_0_1_KnapsackObject("Obj7", 1, 3));

    bagCapacity = 15;

    // container.push_back(_0_1_KnapsackObject("Obj1", 2, 20));
    // container.push_back(_0_1_KnapsackObject("Obj2", 4, 25));
    // container.push_back(_0_1_KnapsackObject("Obj3", 8, 60));

    // bagCapacity = 12;

    vector<vector<pair<float, vector<string>>>> record(container.size(), vector<pair<float, vector<string>>>(bagCapacity + 1));
    
    for (int i = 0; i < container.size(); i++)
    {
        for (int j = 0; j <= bagCapacity; j++)
        {
            record[i][j].first = -1;
        }
    }
    cout<<"After this segmentation fault!"<<endl;

    // using structured bindings concept introduced in c++ 17
    // Note: We even do not need to declare variables

    float profit = 0;
    vector<string> objNames;
    auto [returnedProfit, returnedObjNames] = _0_1_Knapsack(container, bagCapacity, profit, objNames, record);

    cout << "Profit: " << returnedProfit << endl;
    cout << "Objects putted into the bag are: ";
    for (int i = 0; i < returnedObjNames.size(); i++)
    {
        cout << returnedObjNames[i] << " ";
    }
    cout << endl;

    cout<<"Count: "<<count<<endl;

    return 0;
}