# qmc
General Quantum Monte Carlo Code

## Compilation
Since the project is very basic, let's go quick and dirty:

```bash
clang++ -Wall -O3 -std=c++11 -Iinclude/ src/* -o qmc.x 
```

Running the executable should just print "QMC begins" and "QMC ends".
