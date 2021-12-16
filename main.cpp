#include <iostream>

using namespace std;

#include "Human.h"
#include "Cyborg.h"

int main()
{
    man::Human human;
    cout << "S human: " + to_string(sizeof(human)) << endl;
    man::Cyborg cyborg;
    cout << "S cyborg: " + to_string(sizeof(cyborg)) << endl;
    cyborg.skeleton.bones[boneHead].serialize();
    return 0;
}
