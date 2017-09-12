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

int stdout = 1;

int
main (void)
{
    // Print out my name
    printf(stdout, "Lili Peng\n");
    
    // Create a file
    fd = open("tom.txt", O_CREATE|O_RDWR));
    if (fd >= 0)
    {
        printf(stdout, "creat tom.txt file succeed; ok\n");
    }
    else
    {
        printf(stdout, "error: created tom.txt file failed\n");
        exit();
    }
    
    char message[8] = {'1', ' ', '2', ' ', '3', ' ', '4', '\0'};
    int size = sizeof(message);
    
    if (write(fd, &message, size) != size)
    {
        printf(stdout, "error: write to tom.txt file failed\n");
        exit();
    }
    printf(stdout, "write ok\n");
    close(fd);
    
}
