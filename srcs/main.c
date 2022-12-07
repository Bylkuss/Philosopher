/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loadjou <loadjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 13:15:20 by loadjou           #+#    #+#             */
/*   Updated: 2022/12/07 17:55:54 by loadjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h> 
// #include <stdlib.h> 
// #include <sys/types.h> 
// #include <unistd.h> 
// #include <sys/wait.h> 
// #include <signal.h>

/*
how to create threads in c

1. Create a thread variable

Create a variable of type pthread_t that will be used to store the thread identifier returned by the pthread_create() function.

2. Create the thread

Call the pthread_create() function with the thread variable as one of its arguments. This function takes four arguments: a pointer to a thread variable, attributes, start routine, and arguments for the start routine.

3. Execute the thread

Once the thread is created, it will immediately begin execution, starting at the start routine specified in the pthread_create() call.

4. Join the thread

When the main thread has finished executing, it can wait for the newly created thread to finish by calling the pthread_join() function with the thread variable as its argument.
This will cause the main thread to pause until the new thread has finished executing.
*/

// int main() 
// { 
//     int pid = fork();
//     // pid = fork();
//     // pid = fork();
//     // pid = fork();
//     // pid = fork();
//     // pid = fork();
  
//     if (pid == 0) { 
//         printf("pid = %i\n", pid);
//         printf("Child process created\n"); 
//         sleep(30); 
//     } 
//     else { 
//         printf("Parent process created\n"); 
//         // usleep(10); 
//         kill(pid, SIGKILL); 
//         printf("Child process killed\n"); 
//     } 
  
//     return 0; 
// }



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void* routine()
{
    static int i = 1;
    printf("Message from thread nb %d\n", i);
    i++;
    return 0;
}


int main()
{
    pthread_t t, t1, t2;
    int th;
    // int i = 1;
    /*
    while(i < 5)
    {
        pthread_create(&t, NULL, routine(i), NULL);
        pthread_join(t, NULL);
        i++;
    }
    */
    th = pthread_create(&t, NULL, &routine, NULL);
    if(th)
        printf("Unable to create thread");
    
    pthread_create(&t1, NULL, &routine, NULL);
    pthread_create(&t2, NULL, &routine, NULL);
    
    pthread_join(t, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
        
    return 0;
}
