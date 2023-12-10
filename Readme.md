# Test package for coin hsl ma27 solver.

I have seen various implementations of interfaces to the hsl ma27 solver. They have all been reasonably cumbersome to get to work.

In order to use this package you will have to build the ma27 solver with its own build. Here we simply include it via `pkg-config`. In principle this works fine whenever `pkg-config` works. I.e. you're on your own if you're on Windows. 

Once you have installed the ma27 on your system, pass the prefix to your local install to `cmake`

```bash
cmake -B build -DLOCAL_INSTALL_PREFIX:STRING=/your/install/prefix
```

and hopefully everything will work out of the box.