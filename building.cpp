#include "applib/skiplist.h" 
#include "applib/random.h"

#include <iostream>
#include <sstream>


int main()
{
    stringstream outSS;
    SkipList skp;
    skp.add(3);
    outSS << skp;
    cout << outSS.str() << endl;
    //assert(outSS.str() == "[level: 1] 3-->nullptr\n");
}

