//
//  forkExecTest.c
//
//
//  Created by Lili Peng on 10/24/17.
//
//

#include "param.h"
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"
#include "syscall.h"
#include "traps.h"
#include "memlayout.h"

int stdout = 1;

int
main (int argc, char *argv[])
{
    if (argc != 2)
    {
        printf(stdout, "error: incorrect number of arguments. example execution command is \"forkExecTest 1000\" \n");
    }
    else
    {
        // if the argument is a postive integer
        if (atoi(argv[1]))
        {
            int n = atoi(argv[1]);
            
            int fds[2], pid;
            
            if(pipe(fds) != 0)
            {
                printf(stdout, "error: pipe() failed\n");
                exit();
            }
            pid = fork();
            
            if(pid == 0)
            {
                close(fds[0]);
                
                int i;
                for (i = 1; i <= n; i++)
                {
                    printf(stdout, "lowPriority: %d\n", i);
                    sleep(20);
                }
                exit();
            }
            else if (pid > 0)
            {
                close(fds[1]);
                
                int j;
                for (j = 1; j <= n; j++)
                {
                    printf(stdout, "highPriority: %d\n", j);
                    sleep(20);
                }
                close(fds[0]);
                wait();
            }
            else
            {
                printf(stdout, "error: fork() failed\n");
                exit();
            }
            
        }
        else
        {
            printf(stdout, "error: input should be a positive integer\n");
            exit();
        }
    }
    exit();
}

