# TinyTCP

## What is **TinyTCP**?

**TinyTCP** is a minimal, cross-platform, blocking TCP library for C.  
It works on **Linux, macOS, BSD, and Windows** and provides a thin abstraction over OS sockets, so you can write TCP clients and servers without worrying about platform differences.

## Features

- Cross-platform (POSIX & Windows)
- Minimal, blocking TCP API

## License

**TinyTCP** is licensed under the **MIT License**. See the [LICENSE](LICENSE) file for details.

## Contributions

I don’t take contributions for now — this library is meant to stay minimal and simple.

## Getting Started

### 1. Build the library

#### POSIX (Linux, macOS, BSD)

```bash
git clone https://github.com/kdslfjioasdfj/tinytcp
cd tinytcp
premake5 ninja
ninja
```

#### Windows (CMD.EXE)

```bat
git clone https://github.com/kdslfjioasdfj/tinytcp
cd /d tinytcp
premake5 ninja
ninja
```

### 2. Read the documentation

- [Disclaimers](docs/disclaimers.md)
- [Common API](docs/common.md)
- [Server API](docs/server.md)
- [Client API](docs/client.md)

> **NOTE:** It is highly suggested that you read the documentation.
