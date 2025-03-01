#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <vector>
using namespace std;

int main()
{
    vector <string>::const_iterator iter1;

    vector <string> scores1;
    scores1.push_back("1000");
    scores1.push_back("1007");
    scores1.push_back("1001");

    for (iter1 = scores1.begin(); iter1 < scores1.end(); ++iter1)
        cout << *iter1 << endl;

    int yourScore1;
    cin >> yourScore1;
    iter1 = find(scores1.begin(), scores1.end(), &yourScore1);
    if (iter1 != scores1.end())
        cout << "succses\n";
    else
        cout << "fail\n";

    srand(static_cast<unsigned int>(time(0)));
    random_shuffle(scores1.begin(), scores1.end());
    for (iter1 = scores1.begin(); iter1 < scores1.end(); ++iter1)
        cout << *iter1 << endl;

    sort(scores1.begin(), scores1.end());
    for (iter1 = scores1.begin(); iter1 < scores1.end(); ++iter1)
        cout << *iter1 << endl;
    return 0;
}