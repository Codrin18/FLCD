#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pif.h"

//Add identifier in PIF
void addIdentifier(char *key,int p){
    int ok = 0 ;
    
    if (pifLength == 0)
    {
        strncpy(PIF[pifLength].key,key,sizeof(key));
        PIF[pifLength++].value = p;
        //++pifLength;
    }
    else
    {
        for (int i = 0; i < pifLength; ++i)
        {
            if (strcmp(PIF[i].key,key) == 0)
            {
                ok = 1;
                break;
            }
        }

        if (ok == 0)
        {
            strncpy(PIF[pifLength].key,key,sizeof(key));
            PIF[pifLength++].value = p;
            
        }
    }
}

void addElementPIF(char *key){


    if (pifLength == 0)
    {
        strncpy(PIF[pifLength].key,key,sizeof(key));
        PIF[pifLength++].value = -1;
        //++pifLength;
    }
    else
    {
        int ok = 0;

        for (int i = 0; i < pifLength; ++i)
        {
            if (strcmp(PIF[i].key,key) == 0)
            {
                ok = 1;
                break;
            }
        }

        if (ok == 0)
        {
            strncpy(PIF[pifLength].key,key,sizeof(key));
            PIF[pifLength++].value = -1;
            //++pifLength;
        }
    }
    
}

void pif_dumb(FILE *of){

    for(int i = 0; i < pifLength; ++i){
        fprintf(of,PIF[i].key,PIF[i].value);
        fprintf(of,"\n");
    }
}
