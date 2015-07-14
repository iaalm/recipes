/*
ID: simonin1
LANG: C
TASK: transform
*/
#include <stdio.h>
#include <assert.h>

int rotation(char matrix[2][10][10],int n);
int nchange(char matrix[2][10][10],int n); 

int main()
{
    int n,i,j,result;
    char matrix[2][10][10],t;
    FILE *fp = fopen("transform.in","r");
    fscanf(fp,"%d",&n);
    for(i = 0;i < n;i++)
    {
          fgetc(fp);
          for(j = 0;j < n;j++)
                matrix[0][i][j] = fgetc(fp);
    }
    for(i = 0;i < n;i++)
    {
          fgetc(fp);
          for(j = 0;j < n;j++)
                matrix[1][i][j] = fgetc(fp);
    }
    fclose(fp);
                     
                                            for(i = 0;i < n;i++)
                                            {
                                                  for(j = 0;j < n;j++)
                                                        printf("%c",matrix[0][i][j]);
                                                  printf("\n");
                                            }
                                                  printf("\n");
                                            for(i = 0;i < n;i++)
                                            {
                                                  for(j = 0;j < n;j++)
                                                        printf("%c",matrix[1][i][j]);
                                                  printf("\n");
                                            }
    result = rotation(matrix,n);
    if(result == 7)
              result = nchange(matrix,n);
    if(result == 7)
    {
              for(i = 0;i < n;i++)
                     for(j = 0;j <= ((n - 1)/ 2);j++)
                     {
                            t = matrix[1][i][j];
                            matrix[1][i][j] = matrix[1][i][n - j -1];
                            matrix[1][i][n - j -1] = t;
                     }
                     
                                                                 
                                            for(i = 0;i < n;i++)
                                            {
                                                  for(j = 0;j < n;j++)
                                                        printf("%c",matrix[0][i][j]);
                                                  printf("\n");
                                            }
                                                  printf("\n");
                                            for(i = 0;i < n;i++)
                                            {
                                                  for(j = 0;j < n;j++)
                                                        printf("%c",matrix[1][i][j]);
                                                  printf("\n");
                                            }
              if(nchange(matrix,n) == 6)
                                   result = 4;
              else
                  if(rotation(matrix,n) != 7)
                                        result = 5;
    }
    
    fp = fopen("transform.out","w");
    fprintf(fp,"%d\n",result);
    fclose(fp);
    
    return 0;
}
int nchange(char matrix[2][10][10],int n)
{
    int result = 6,i,j;
    for(i = 0;i < n;i++)
          for(j = 0;j < n;j++)
                if(matrix[0][i][j] != matrix[1][i][j])
                                   result = 7;
    return result;
} 

int rotation(char matrix[2][10][10],int n)
{
    n--;
    int result = 1,i,j;
    for(i = 0;i <= n;i++)
          for(j = 0;j <= n;j++)
                if(matrix[0][i][j] != matrix[1][j][n - i])
                                   result = 7;
          if(result == 7)
          {
                    result = 2;
                    for(i = 0;i <= n;i++)
                          for(j = 0;j <= n;j++)
                                if(matrix[0][i][j] != matrix[1][n - i][n - j])
                                   result = 7;
          }
          if(result == 7)
          {
                    result = 3;
                    for(i = 0;i <= n;i++)
                          for(j = 0;j <= n;j++)
                                if(matrix[0][i][j] != matrix[1][n - j][i])
                                   result = 7;
          }
          return result;
}
