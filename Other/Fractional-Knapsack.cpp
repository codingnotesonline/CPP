#include <iostream>
#include <queue>
#include <vector>
using namespace std;

class KnapsackObject
{
public:
    string name;
    float weight;
    float profit;
    float profitUponWeightRatio;

    KnapsackObject()
    {
        this->name = "Nothing";
        this->weight = 0;
        this->profit = 0;
        this->profitUponWeightRatio = 0;
    }

    KnapsackObject(string name, float weight, float profit)
    {
        this->name = name;
        this->weight = weight;
        this->profit = profit;
        this->profitUponWeightRatio = this->profit / this->weight;
    }

    void operator=(KnapsackObject obj1)
    {
        this->name = obj1.name;
        this->profit = obj1.profit;
        this->weight = obj1.weight;
        this->profitUponWeightRatio = obj1.profitUponWeightRatio;
    }
};

class KnapsackComparator
{
public:
    bool operator()(KnapsackObject &obj1, KnapsackObject &obj2)
    {
        return (obj1.profitUponWeightRatio < obj2.profitUponWeightRatio);
    }
};

pair<float, vector<string>> fractionalKnapsack(vector<KnapsackObject> container, float bagCapacity)
{

    priority_queue<KnapsackObject, vector<KnapsackObject>, KnapsackComparator> pq;
    float profit = 0;
    vector<string> objNames;

    // building a max heap
    for (int i = 0; i < container.size(); i++)
    {
        pq.push(container[i]);
    }

    KnapsackObject obj;
    while (bagCapacity > 0)
    {
        obj = pq.top();
        pq.pop();

        if (obj.weight <= bagCapacity)
        {
            profit += obj.profit;
            bagCapacity -= obj.weight;
            objNames.push_back(obj.name);
        }
        else
        {
            profit += obj.profit * (bagCapacity / obj.weight);
            bagCapacity = 0;
            objNames.push_back(obj.name);
        }
    }

    return make_pair(profit, objNames);
}

int main()
{
    vector<KnapsackObject> container;
    float bagCapacity;

    // container.push_back(KnapsackObject("Obj1", 2, 10));
    // container.push_back(KnapsackObject("Obj2", 3, 5));
    // container.push_back(KnapsackObject("Obj3", 5, 15));
    // container.push_back(KnapsackObject("Obj4", 7, 7));
    // container.push_back(KnapsackObject("Obj5", 1, 6));
    // container.push_back(KnapsackObject("Obj6", 4, 18));
    // container.push_back(KnapsackObject("Obj7", 1, 3));

    // bagCapacity = 15;

    container.push_back(KnapsackObject("Obj1", 2, 20));
    container.push_back(KnapsackObject("Obj2", 4, 25));
    container.push_back(KnapsackObject("Obj3", 8, 60));

    bagCapacity = 12;

    // using structured bindings concept introduced in c++ 17
    // Note: We even do not need to declare variables
    auto [profit, objNames] = fractionalKnapsack(container, bagCapacity);

    cout << "Profit: " << profit << endl;
    cout << "Objects putted into the bag are: ";
    for (int i = 0; i < objNames.size(); i++)
    {
        cout << objNames[i] << " ";
    }
    cout << endl;

    return 0;
}