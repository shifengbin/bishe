#include "modepair.h"
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
ModePair::ModePair(char *mode, int type)
{
    if (mode == NULL)   return;

    int len = strlen(mode);
    this->mode = new char[len+1];
    sprintf(this->mode,"%s",mode);
    this->type = type;

}
int ModePair::getType()
{
    return this->type;
}

char * ModePair::getMode()
{
    return this->mode;
}

ModePair::~ModePair()
{
    if ( this->mode != NULL)
    {
        free(this->mode);
    }
}
