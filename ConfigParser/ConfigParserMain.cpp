#include <iostream>
#include "configparser.h"
using namespace std;

int main()
{
    ConfigParser *cp = ConfigParser::getConfigParser();
    cout<<"duration:"<<cp->getDuration()<<endl;
    cout<<"timeout:"<<cp->getTimeout()<<endl;
    cout<<"deepth:"<<cp->getDeepth()<<endl;
    cout<<"jobnum:"<<cp->getJobNum()<<endl;
    cout<<"method"<<cp->getMethod()<<endl;
    ModePair *p;
    for( int i = 0 ; i < 20 ; i++)
    {
        p = cp->getMode(i);
        if( p != NULL)
            cout<< i << " match: " << p->getMode() << "type:  " << p->getType()<<endl;
    }
    return 0;
}

