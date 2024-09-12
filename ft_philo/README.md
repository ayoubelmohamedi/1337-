# I never thought philosophy would be so deadly either 

## Overview
The [dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem) is an example problem often used in concurrent algorithm design to illustrate synchronization issues and techniques for resolving them.

A philosopher can only eat their spaghetti when they have both a left and right fork. Thus two forks will only be available when their two nearest neighbors are thinking, not eating. After an individual philosopher finishes eating, they will put down both forks. 

 
## About pthread library
[pthreads](https://en.wikipedia.org/wiki/Pthreads) defines a set of C programming language types, functions and constants. It is implemented with a pthread.h header and a thread library. see also [UNIX Specification, Version 2 Threads Extensions](https://unix.org/unix/version2/whatsnew/login_threads.html)

There are around 100 threads procedures, all prefixed pthread_ and they can be categorized into five groups:
* Thread management – creating, joining threads etc.
* [Mutexes](https://en.wikipedia.org/wiki/Lock_(computer_science)) : provides mutual exclusion => blocks multiple users from accessing the same shared variable or data ([critical section](https://en.wikipedia.org/wiki/Critical_section))at the same time.
* [Condition variables](https://en.wikipedia.org/wiki/Condition_variable) These allow threads to wait until a particular condition is met, facilitating communication between threads. They are often used in conjunction with mutexes to avoid race conditions.
* Synchronization between threads using [read write locks](https://en.wikipedia.org/wiki/Readers%E2%80%93writer_lock) and [barriers](https://en.wikipedia.org/wiki/Barrier_(computer_science)) (Barries wait for threads to be created first in order for work to start. use it in case you need all threads to start at the same time)
* [Spinlocks](https://en.wikipedia.org/wiki/Spinlock)

## Data types: (for shared ressources)
_**pthread_mutex_t**  one_fork_:  => a mutex provides mutual exclusion

_**pthread_mutex_t**    *forks_: pointer to many mutexes 

>**Note**: multiple mutexes increase the risk of deadlocks.
 	avoid deadlock : lock ordering or [lock hierarchy](https://en.wikipedia.org/wiki/Dining_philosophers_problem#Resource_hierarchy_solution) to minimize deadlock risk)

## Functions:
A **mutex** (short for "mutual exclusion") is a synchronization primitive used to protect shared resources by ensuring that only one thread can access the resource at a time. It effectively prevents concurrent access to shared data, allowing only one thread to modify or read the resource at any given moment, thereby avoiding race conditions.
```
pthread_mutex_init() //intitialize a mutex variable
pthread_mutex_lock() // declared when entering a critical section 
pthread_mutex_unlock()
pthread_mutex_destroy() // free the initialized mutex 
```
better to use the lock and unlock funtions as a macro 
```
define LOCK pthread_mutex_lock
define UNLOCK pthread_mutex_unlock
define DSTR pthread_mutex_destroy
```
## synchronization primitive:


[synchronization primitive](https://en.wikipedia.org/wiki/Synchronization_(computer_science)) prevents state from being modified or accessed by multiple threads of execution at once.
1. **mutexes**:  provides mutual exclusion, allowing only one thread to access a resource at a time.
2. **Semaphores**:  signalling mechanisms. it is variable the can be incremented/decremented (counting semaphores) sitting a limit to how many thread can access the ressource. they can also be toglled true/false (binary semaphores) to signal resource access availability.
3. **Condition variables**:  allow threads to wait until a particular condition is met. Often used in conjunction with mutexes to avoid race conditions.
4. **Barriers**: synchronize a group of threads at a certain point in execution so they can start simultaneously.
5. **Spinlocks**: A type of mutex that keeps checking (or "spinning") until the lock becomes available. (best for short-time wait).
6. **Read/write locks**: These allow multiple threads to read a resource concurrently while providing exclusive access for writing.
7. **Atomic Operations**: low-level operations that ensure certain operations on variables are completed without interruption, thus preventing race conditions.


## Problems :

* **Deadlock** : each process is waiting (everyone is holding one fork, waiting for the other one)
* **Race conditions** : threads sharing data, making changes at the same time (solved by mutual exclusion)
* **Resource Starvation** : thread or process is perpetually denied access, mostly due to Resource Allocation held by other threads, or poor scheduling.

>_example of poor scheduling_ : thread is locking the mutex immediately	after unlocking it, not giving enough time for another thread to access it.
* **Livelock** : A livelock is similar to a deadlock, except that the states of the processes involved in the livelock constantly change with regard to one another, none progressing.

>_real-world example of livelock_ is when two people in a narrow corridor both try to move aside to let the other pass but end up swaying back and forth without making progress.

## Semaphores

[Semaphore](https://en.wikipedia.org/wiki/Semaphore_(programming)) is datatype for control access to a common resource.

trivial semaphore can be incremented or decremented, or toggled) .
> example: Consider a variable A and a boolean variable S. A is only accessed when S is marked true. Thus, S is a semaphore for A.

**counting semaphores**: allow an arbitrary resource count.
**binary semaphores**: restricted to the values 0 and 1 (or locked/unlocked, unavailable/available).

> exampe of binary semaphores, initializing five forks to zero

```
std::binary_semaphore both_forks_available[N]
{
    std::binary_semaphore{0}, std::binary_semaphore{0},
    std::binary_semaphore{0}, std::binary_semaphore{0},
    std::binary_semaphore{0}
};
```



## Dijkstra's solution
This solution negates resource holding, making sure each philosopher holds both forks or wait.

each philo checks his neighbours (left and right), and checks their states which is either eating (holding two forks) , thinking or sleeping].
if both neighbours are not eating, then our current philo can take the left and right fork.
