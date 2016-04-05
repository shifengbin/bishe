#ifndef MODEPAIR_H
#define MODEPAIR_H
#ifndef NULL
#define NULL (void*)0
#endif
class ModePair
{
public:
    ModePair(char *mode, int type);
    ~ModePair();
    char *getMode();
    int getType();
private:
    char *mode;
    int type;
};

#endif // MODEPAIR_H
