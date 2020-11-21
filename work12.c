#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <dirent.h>

#define SPACE "---------\n"

int main()
{
    //struct stat sb; //statistcis of a file
    DIR *d;
    struct dirent *entry;
    struct stat sb;
    long size;

    d = opendir("."); //open cd
    entry = readdir(d);

    printf(SPACE);
    printf("Statistics for directory: .\n");
    printf(SPACE);

    printf("All regular files:\n");
    while (entry)
    {
        if (entry->d_type == 8) //i noticed that regular files all have d_type 8
        {
            printf("%s\n", entry->d_name); //print name of file
            stat(entry->d_name, &sb); //get stat of file
            size += sb.st_size; //add to the total size
        }
        entry = readdir(d); //move pointer to the next element
    }

    printf(SPACE);
    printf("Total Directory Size: %ld\n", size);
    printf(SPACE);
    printf("All Directories:\n");

    rewinddir(d);
    entry = readdir(d);
    while (entry)
    {
        if (entry->d_type == 4) //i noticed that directories have d_type 4
            printf("%s\n", entry->d_name); //print name of directory
        entry = readdir(d); //move pointer to the next element
    }

    closedir(d);
}