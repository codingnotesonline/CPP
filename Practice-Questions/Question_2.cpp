#include <iostream>
#include <stack>
using namespace std;

void getPath(stack<char> &container, string &answer)
{
    char ch;

    while (!container.empty())
    {
        ch = container.top();
        container.pop();

        if (answer.empty() && ch != '/')
        {
            answer.push_back('/');
        }

        else if (ch == '/' && container.empty())
        {
            break;
        }

        else if (ch == '/' && container.top() == '/')
        {
            container.pop();
        }

        else if (ch == '/' && answer.back() == '/')
        {
            continue;
        }

        else if (ch == '.' && container.top() != '.')
        {
            continue;
        }

        else if (ch == '.' && container.top() == '.')
        {
            container.pop();
            int temp = answer.length();

            for (int j = temp; j > 1; j--)
            {
                answer.pop_back();
                if (answer.back() == '/')
                {
                    break;
                }
            }
            continue;
        }
        else{
        answer.push_back(ch);
        }
    }
}

string simplifyPath(string path)
{
    stack<char> container;
    string answer;
    int length = path.length();

    char ch;
    int i;
    for (i = 0; i < length; ++i)
    {
        ch = path.back();
        path.pop_back();
        container.push(ch);
    }

    getPath(container, answer);

    if (answer.length() > 1 && answer.back() == '/')
    {
        answer.pop_back();
    }

    return answer;
}

int main()
{
    cout << simplifyPath("/home/") << endl;
    cout << simplifyPath("/../") << endl;
    cout << simplifyPath("/home//foo/") << endl;
    cout << simplifyPath("/a/./b/../../c/") << endl;
    cout << simplifyPath("/a/../../b/../c//.//") << endl;
    cout << simplifyPath("./../wsd/./fghd/../c///") << endl;

    return 0;
}