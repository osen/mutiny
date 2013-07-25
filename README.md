Mutiny 3D - Open-source Unity re-implementation
![](http://devio.us/~kpedersen/mutiny/lib/tpl/prsnl10/user/logo.png)

To build the software on Linux, follow these steps:

```
$ cd mutiny
$ make -f Makefile.linux
$ bin/collision
```

To build the software using the Emscripten cross compiler, use:

```
$ cd mutiny
$ make -f Makefile.emscripten
$ firefox index.html
```

Mutiny is licensed under the GPLv3
