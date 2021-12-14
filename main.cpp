#include <iostream>

using namespace std;

#include "Human.h"
#include "Cyborg.h"

int main()
{
    Human human;
    cout << "S human: " + to_string(sizeof(human)) << endl;
    Cyborg cyborg;
    cout << "S cyborg: " + to_string(sizeof(cyborg)) << endl;
    return 0;
}
