#include <stdio.h>
int main()
{
   FILE *fp;
   fp=fopen("EOG_S1.txt","r")
   fscanf("%d %d %d %d %d", &eog, &gaze, &sacc, &stim, &time)
   printf(eog)
   fclose(fp);

}
