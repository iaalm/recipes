/*
ID: simonin1
LANG: C
TASK: milk2
*/

#include <stdio.h>
#include <assert.h>

int main()
{
    int n,time[5000][2],miked = 0,nmiked = 0,i,j,index0,index1,t;
    FILE *fp = fopen("milk2.in","r");
    fscanf(fp,"%d",&n);
    for(i = 0;i < n;i++)
          fscanf(fp,"%d %d",&time[i][0],&time[i][1]);
    fclose(fp);
    
    for(i = 0;i < n;i++)                               //sort in the same time
    {
          index0 = index1 = i;
          for(j = i + 1;j < n;j++)
          {
                if(time[index0][0] > time[j][0])
                              index0 = j;
                if(time[index1][1] > time[j][1])
                              index1 = j;
          }
          if(i != index0)
          {
                   t = time[index0][0];
                   time[index0][0] = time[i][0];
                   time[i][0] = t;
          }
          if(i != index1)
          {
                   t = time[index1][1];
                   time[index1][1] = time[i][1];
                   time[i][1] = t;
          }
    }
    
    //¡Ÿ ± 
    /*fp = fopen("milk2.tmp","w");
	for(i = 0;i < n;i++)
          fprintf(fp,"%d %d\n",time[i][0],time[i][1]);
	fclose(fp);
    */
    index0 = index1 = 0;
	i = time[0][0];            //i = time start mike
    do
    {
           assert(index0 >= index1);
           if(index0 - index1 <= 1 && time[index1][1] < time[index0][0])
           {
                   t = time[index1][1] - i;
                   i = time[index0][0];
                   j = i - time[index1][1];
                   if(t > miked)
                        miked = t;
                   if(j > nmiked)
                        nmiked = j;
           }
           if(time[index0][0] <= time[index1][1] && index0 != n - 1)
                   index0++;
           else
                   index1++;
    }while(index1 != n);

	index1--;
	if(index0 - index1 <= 1)
           {
                   t = time[index1][1] - i;
                   i = time[index0][0];
                   j = i - time[index1][1];
                   if(t > miked)
                        miked = t;
                   if(j > nmiked)
                        nmiked = j;
           }
    if(n == 1)
    miked = time[0][1] - time[0][0];
    
    fp = fopen("milk2.out","w");
	fprintf(fp,"%d %d\n",miked,nmiked);
	fclose(fp);
}
