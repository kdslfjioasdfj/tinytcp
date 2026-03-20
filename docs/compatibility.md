# Notes for compatibility

## System API Usage

On _POSIX_ systems, **TinyTCP** uses _Berkeley Sockets_ internally.
On _Windows_, **TinyTCP** uses _Winsock2_ internally.
Ensure that one of these are available.

## Shared/Dynamic Library vs Static Library Usage

If you are building a _shared/dynamic_ library (using `premake5 <system> --shared`), `TINYTCP_CONFIG_SHARED` must be defined. Otherwise, there may be _linker errors_.
