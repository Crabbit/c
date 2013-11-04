#include <stdio.h>

int main()
{
  char* file1 = "test1.txt";
  char* file2 = "test2.txt";
 FILE* fin1 = fopen(file1, "r");
 FILE* fin2 = fopen(file2, "r");

 while (!feof(fin1) && !feof(fin2)) {
  if (fgetc(fin1) != fgetc(fin2))
   break;
 }
 if (feof(fin1) && feof(fin2)) 
  printf("Compare OK!\n");
 else
  printf("Not Equal\n");

 fclose(fin1);
 fclose(fin2);
}
