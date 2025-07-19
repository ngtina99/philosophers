# Philosophers

An implementation of the classic Dining Philosophers Problem in C.

<img src="philosophers.png" width="400">

## 📝 Description

This project simulates the Dining Philosophers Problem using threads and mutexes, focusing on proper synchronization, timing precision, and deadlock prevention. The goal is to manage philosophers who alternately eat, sleep, and think while sharing limited resources (forks) without starving or causing deadlocks.

## 🛠️ Usage

1️⃣ **Clone the repository**

```bash
git clone https://github.com/ngtina99/philosophers.git philosophers
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

## 🔎 Argument details

1️. number_of_philosophers: Number of philosophers (max 200)

2️. time_to_die: Time in ms before a philosopher dies without eating (min 60 ms)

3️. time_to_eat: Time in ms it takes to eat (min 60 ms)

4️. time_to_sleep: Time in ms to sleep (min 60 ms)

5️. number_of_times_each_philosopher_must_eat (optional): How many times each philosopher must eat before stopping

## ☑️ Tests
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
```bash
./philo 4 410 200 200 → No philosopher should die
```
```bash
./philo 2 <various> → Death delayed >10ms is unacceptable
```
Stress tests with varied values to ensure proper fork handling, death detection, and timing accuracy

## ✅ Code Safety & Concurrency Assurance

- No global variables (all shared data passed via structures)
- All dynamic memory properly freed (no leaks)
- All shared resources (forks, printing, state updates) protected by mutexes
- No data races thanks to correct mutex use
- Compiled with -Wall -Wextra -Werror

## 💡 Debugging & Validation Tools

To verify there are no data races or thread issues, run:
```bash
valgrind --tool=helgrind ./philo [arguments]   # checks for data races between threads
valgrind --tool=drd ./philo [arguments]       # checks for data races and thread errors
```

## 💼 Connect
If you have any questions or suggestions, feel free to connect:
🔗 [LinkedIn: Valentina Nguyen](https://www.linkedin.com/in/valentina-nguyen-t/) 🙋‍♀️

## 📜 License
This project is licensed under the MIT License. See LICENSE for details.

## 🖥️ System Compatibility
This project was developed and tested on Linux (Ubuntu).
