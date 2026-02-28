# Disclaimers:

## Thread-safety
**TinyTCP** does not perform internal synchronization.
`tinytcp_common_setup` (which can be found in `"common.h"`; see `common.md:Functions:tinytcp_common_setup`) and `tinytcp_common_cleanup` (which can be found in `"common.h"`; see `common.md:Functions:tinytcp_common_cleanup`) must not be called concurrently.
All other **TinyTCP** functionality is reentrant. Concurrent access to the same socket from multiple threads must be externally synchronized by the user.

## Blocking behavior
**TinyTCP** is a **BLOCKING** TCP library.