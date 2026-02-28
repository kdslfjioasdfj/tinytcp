# Disclaimers:

## Thread-safety
**TinyTCP** is NOT thread-safe NOR reentrant.
If you desire to use **TinyTCP** in a multi-threaded environment, you would need to maintain a mutex for all **TinyTCP** functionality and only use **TinyTCP** functionality when said mutex has been obtained.