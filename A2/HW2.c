//
//  HW2.c
//  
//
//  Created by Lili Peng on 9/11/17.
//
//

#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int stdout = 1;

void
filetest(void)
{
    int fd;

    // Print out my name
    printf(stdout, "Lili Peng\n");
    
    // Create a file
    fd = open("tom.txt", O_CREATE|O_RDWR);
    if (fd >= 0)
    {
        printf(stdout, "creat tom.txt file succeed; ok\n");
    }
    else
    {
        printf(stdout, "error: created tom.txt file failed\n");
        exit();
    }
    
    char message[9] = {'1', ' ', '2', ' ', '3', ' ', '4', '\n', '\0'};
    int size = sizeof(message);
    
    if (write(fd, &message, size) != size)
    {
        printf(stdout, "error: write to tom.txt file failed\n");
        exit();
    }
    printf(stdout, "write ok\n");
    close(fd);
    
}

int
main(int argc, char *argv[])
{
    filetest();
    exit();
}
