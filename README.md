
# Philosophers Simulation 🍝🤔💤

![xuhgni9ifz9d1uo1red2](https://github.com/DjoykeAbyah/PHILOSOPHERS/assets/115019123/66e81f37-258e-465f-a772-d13b0e8d5462)

In this assignment, philosophers gather around a round table with a central bowl of spaghetti. Here are the key points to succeed in this simulation:

- Philosophers alternate between eating, thinking, and sleeping.
- While eating, they cannot think or sleep; while thinking, they cannot eat or sleep; and during sleep, no eating or thinking occurs.
- Forks on the table are as numerous as philosophers, and each philosopher holds both right and left forks while eating.
- Once a philosopher finishes eating, they return the forks to the table and start sleeping. Upon waking up, they resume thinking until the simulation stops when a philosopher dies of starvation.
- Every philosopher must eat and should never starve.
- Philosophers do not communicate with each other.
- Philosophers are unaware of another philosopher's imminent death.

## Global Rules

- Program arguments: `number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]`.
- Each philosopher is numbered from 1 to `number_of_philosophers`.
- Philosopher 1 sits next to philosopher `number_of_philosophers`, and any other philosopher N sits between philosopher N - 1 and philosopher N + 1.

### About Program Logs:
- State changes for philosophers are formatted with timestamps.
- A displayed state message must not be mixed up with another message.
- Messages announcing a philosopher's death should be displayed within 10 ms after the actual death.
- Ofcourse data races in the program are avoided.

### Specific Rules:
- Each philosopher is a thread.
- One fork between each pair of philosophers.
- Mutexes are used to protect the state of forks to prevent duplication.

```
