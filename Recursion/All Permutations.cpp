#include <iostream>
#include <string>
using namespace std;

void generate(string perm, string s)
{
    if (perm.length() == s.length())
    {
        cout << perm << '\n';
        return;
    }

    for (auto c : s)
    {
        string newString = perm;
        newString.push_back(c);
        generate(newString, s);
    }
}

int main()
{
    string s = "abc";

    string perm = "";
    generate(perm, s);
}
