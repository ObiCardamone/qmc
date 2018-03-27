# qmc
General Quantum Monte Carlo Code

## Environment
We utilise the `boost` mathematical library, so you'll have to set the path
to the include and library directories. On my machine, for instance,

```bash
export BOOST_INC=/usr/include/boost
export BOOST_LIB=/usr/lib/x86_64-linux-gnu
```

## Compilation
Since the project is very basic, let's go quick and dirty:

```bash
clang++ -Wall -O3 -std=c++11 -Iinclude/ -I$BOOST_INC src/* -L$BOOST_LIB -o qmc.x 
```

Running the executable should just print "QMC begins" and "QMC ends".
