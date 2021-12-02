#Task Scheduler
This is a C based project to represent how tasks are scheduled in UNIX-like operating systems.


##Project Description:
In this project, the user can choose from some scheduling algorithms. These algorithms are:
	
* First Come First Served (FCFS)
* Shortest Job First (SJF)
* Priority Scheduling
* Round-robin
* Priority with round-robin


## How To Run The Code:
The user is supposed to rune the make file followed by the name of the scheduling algorithm they want. For example:
`make fcfs` to run the first come first served scheduler. Then you run the executable for example `./fcfs <path of the input file>`. Available options are:
> * make fcfs
> * make sjf
> * make rr
> * make priority
> * make pr-rr

## Code Organization:
The code depends on a circular linked list.
	 Each node contains a task that consists of:
> 1. A task name `char* name`
2. A task PID `int pid`
3. A priority number `int priority`
4. A cpu burst time `int burst`

## How the code works:
###  1.FCFS:

As the name suggests, it runs all the tasks based on thier order in the queue. It doesn't put into consideration the priority or the burst time. So I just run the task within each node of the linked list.


###  2.SJF:
It runs the tasks based on their cpu burst time. I copied the nodes to an array of nodes. Then I, sorted the nodes within the array using quicksort.


###  3.Priority:
It runs the tasks based on their priority. I used the same algorithm as in SJF, yet I just changed the `cmp` function to sort based on `priority` not `burst` time.

###  4.Round-Robin:
This algorithm mainly sets a pre-defined time slice. The scheduler gives each task this time slice then preempts it. If the burst time of the task is already less than the slice, it runs the task for the burst time. Otherwise, it runs it runs it for this time slice then subtracts it from the task's burst time.

###  5.Priority With Round-Robin:
This algorithm runs the tasks based on their priority, and for those taske with same priority, it uses round-robin to run them.

## Trade-offs:
Well, I used the same circular linked list for all the algorithms. This may not be the most effecient way, because some algorithms like SJF, FCFS and priority just need a normal linked list. Yet, I decided to save some memory instead of having another linked list file.

## Future Improvements:
I plan to add the completely fair scheduler(CFS) implemented in the linux kernel. Other improvements may include adding other algorithms implemented in major operating systems.
