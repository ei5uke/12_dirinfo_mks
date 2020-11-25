#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <time.h>
#include <dirent.h>

#define SPACE "---------\n"

int main(int argc, char **argv)
{
    //struct stat sb; //statistcis of a file
    DIR *d;
    struct dirent *entry;
    struct stat sb;
    long size;
    char buffer[100];

    //printf("argv[1]: %s\n", argv[1]); //a.out
    if (argv[1])
    {
        d = opendir(argv[1]);
        if (!d) //open cd
        {
            printf("Open directory from command line argument failed: %d, %s\n", errno, strerror(errno));
            return -1;
        }
    }
    else
    {
        printf("Enter a directory: ");
        fgets(buffer, sizeof(buffer), stdin);
        char *p = strchr(buffer, '\n');
        *p = 0;              //necessary to remove the '\n'
        d = opendir(buffer); //open cd
        if (!d) //open cd
        {
            printf("Open directory from stdin failed: %d, %s\n", errno, strerror(errno));
            return -1;
        }
    }

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
            stat(entry->d_name, &sb);      //get stat of file
            size += sb.st_size;            //add to the total size
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
        if (entry->d_type == 4)            //i noticed that directories have d_type 4
            printf("%s\n", entry->d_name); //print name of directory
        entry = readdir(d);                //move pointer to the next element
    }

    closedir(d);
}