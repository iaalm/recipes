/*
ID: simonin1
LANG: C
TASK: namenum
*/

#include<stdio.h>
#include<string.h>
#include<assert.h>

int fit(char* name,char* dict)
{
    if(strlen(name) != strlen(dict))
            return 0;
    
    static const char list[8][3] = {{'A','B','C'},
                                    {'D','E','F'},
                                    {'G','H','I'},
                                    {'J','K','L'},
                                    {'M','N','O'},
                                    {'P','R','S'},
                                    {'T','U','V'},
                                    {'W','X','Y'}};
    int i,j;
    for(i = 0;i < strlen(name);i++)
    {
            assert(name[i] > '1');
            for(j = 0;j < 3;j++)
            {
                  if(list[name[i] - '2'][j] == dict[i])
                          break;
            }
            if(j == 3)
                    return 0;
    }
    return 1;
}

int main()
{
    char name[15],dict[15],n = 0;
    
    FILE* fp = fopen("namenum.in","r"),*o = fopen("namenum.out","w");
    fscanf(fp,"%s",name);
    fclose(fp);
    
    fp = fopen("dict.txt","r");
    do
    {
         fscanf(fp,"%s",dict);
         if(fit(name,dict))
         {
             n = 1;
             fprintf(o,"%s\n",dict);
         }
    }while(!feof(fp));
    fclose(fp);
    if(n == 0)
            fprintf(o,"NONE\n");
    fclose(o);
    return 0;
}
