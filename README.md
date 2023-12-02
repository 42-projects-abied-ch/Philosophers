# Philosophers

42 uni project

## Tasks

Solve the dining philosopher's problem using mulitthreading

## Explanation of the problem

The philosophers need to eat in order to survive. They are eating spaghetti, so they need 2 forks(???) to avoid making a mess. However, each philosopher only brings one fork to the table,
meaning they have to borrow the second one from the other philosopher.
The task here is to make sure they keep eating.

### Mutual Exclusion

Only one philosopher can hold a fork at a time. This ensures that no two philosophers can simultaneously access the same fork.

### Hold and Wait

A philosopher can only eat if they can acquire both the forks on their left and right. If a philosopher cannot acquire both forks, they must release the fork they are holding and try again later.

### No Preemption

Once a philosopher has picked up a fork, they cannot be forced to release it until they have finished eating.

### Circular Wait

To avoid deadlock, the philosophers must pick up forks in a way that prevents circular waiting. For example, if all philosophers pick up the fork to their left before attempting to pick up the one on their right, a circular dependency is avoided.

### grade

100/100
