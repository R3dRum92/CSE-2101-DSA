#include <iostream>
#include <string>
#include <stack>
using namespace std;

int precedence(char x)
{
    if (x == '+' || x == '-')
        return 1;
    else if (x == '*' || x == '/')
        return 2;
    else if (x == '^')
        return 3;
    else
        return -1;
}

int main()
{
    string infix;
    cin >> infix;

    stack<char> out;
    stack<char> op;
    for (int i = 0; i < infix.length(); ++i)
    {
        if (infix[i] >= 'a' && infix[i] <= 'z')
            out.push(infix[i]);
        else if (infix[i] == '(')
            op.push(infix[i]);
        else if (infix[i] == ')')
        {
            while (op.top() != '(')
            {
                out.push(op.top());
                op.pop();
            }
            op.pop();
        }
        else
        {
            while (op.size() != 0 && precedence(infix[i]) <= precedence(op.top()) && op.top() != '(')
            {
                out.push(op.top());
                op.pop();
            }
            op.push(infix[i]);
        }
    }

    while (op.size() != 0)
    {
        out.push(op.top());
        op.pop();
    }

    string postfix = "";
    while (out.size() != 0)
    {
        postfix += out.top();
        out.pop();
    }

    for (auto it = postfix.rbegin(); it != postfix.rend(); ++it)
        cout << *it;
    cout << '\n';
    return 0;
}