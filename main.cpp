#include "bst.h"
using namespace std;

int main(){
    bst<int> t;

    int val = 10;
    t.insert(val);

    val = 15;
    t.insert(val);

    val = 25;
    t.insert(val);

    val = 26;
    t.insert(val);

    val = 20;
    t.insert(val);

    val = 17;
    t.insert(val);

    val = 30;
    t.insert(val);

    cout << t.root->val << endl;

    return 0;
}