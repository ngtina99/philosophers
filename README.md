#Philosophers

An implementation of the classic Dining Philosophers Problem in C.

##📜 Description

This project simulates the Dining Philosophers Problem using threads and mutexes, focusing on proper synchronization, timing precision, and deadlock prevention.

The goal is to manage philosophers who alternately eat, sleep, and think while sharing limited resources (forks) without starving or causing deadlocks.

##🛠️ Usage

1️⃣ **Clone the repository**

```bash
git clone https://github.com/yourusername/webserv.git philosophers
cd philosophers
```

2️⃣ Build

```bash
make
```

3️⃣ Run

./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

*Example*
```bash
./philo 5 800 200 200
```

##🔎 Argument details

number_of_philosophers: Number of philosophers (max 200)

time_to_die: Time in ms before a philosopher dies without eating (min 60 ms)

time_to_eat: Time in ms it takes to eat (min 60 ms)

time_to_sleep: Time in ms to sleep (min 60 ms)

number_of_times_each_philosopher_must_eat (optional): How many times each philosopher must eat before stopping

##☑️ Example Tests
```bash
./philo 1 800 200 200 → Philosopher will die (cannot eat)
```
```bash
./philo 5 800 200 200 → No philosopher should die
```
```bash
./philo 5 800 200 200 7 → Stops when each has eaten 7 times
```
```bash
./philo 4 310 200 100 → One philosopher should die
```

💼 Connect
If you have any questions or suggestions, feel free to connect: 🔗 LinkedIn: Valentina Nguyen 🙋‍♀️

📜 License
This project is licensed under the MIT License. See LICENSE for details.

🖥️ System Compatibility
This project was developed and tested on Linux (Ubuntu).
