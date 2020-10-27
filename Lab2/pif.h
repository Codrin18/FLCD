#define MAXSIZE 100 // maximum size for pif 

typedef struct{
    char key[50];
    int value;
}_pif;

int pifLength = 0;

_pif PIF[MAXSIZE];

void addIdentifier(char *key, int p);
void addElementPIF(char *key);
void addConstantPIF(char *key);
void pif_dumb(FILE *of);




