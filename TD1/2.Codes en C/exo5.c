#include <stdlib.h>
#include <stdio.h>
//79
int main(int argc, char *argv[])
{
	FILE* file = fopen(argv[1], "r"); 
	
	int i = 0;
	int moy = 0;
	int max = 5;
	int min = -1;
	fscanf (file, "%d", &i);    
	while (!feof (file))
    {  
      //printf ("%d\n", i);
      if(min == -1) min = i;
      if(i > max) max = i;
      if(i < min) min = i;
      moy += i;
      
      fscanf (file, "%d", &i);      
    }
    moy = moy - max - min;
    moy = moy / 48;
    printf("%d\n",moy);
    
	fclose(file);
	
}
