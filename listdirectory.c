#include<stdio.h>
#include<dirent.h>

int main()
{
DIR *dir =opendir(".");
if(dir == NULL){
printf("Could not open current directory.\n");
return 1;
}
//Read and print directory content
struct dirent *entry;
while((entry =readdir(dir))!= NULL){
printf("%s\n",entry->d_name);
}
closedir(dir);
return 0;
}


