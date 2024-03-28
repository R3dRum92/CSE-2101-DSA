#include <iostream>
#include <string>
using namespace std;

void generate(string perm, string s, int k)
{
    if (perm.length() == k)
    {
        int c = 0;
        for (auto c : s)
            if (c == 'a')
                c++;
        if (c == 4)
            cout << perm << '\n';
        return;
    }

    for (auto c : s)
    {
        string newString = perm;
        newString.push_back(c);
        generate(newString, s, k);
    }
}

int main()
{
    string s = "abc";
    int k = 5;
    string perm = "";
    generate(perm, s, k);
}
