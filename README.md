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
mkdir -p build
cmake -B build
cmake --build build
```

#### Windows (CMD.EXE)

```bat
git clone https://github.com/kdslfjioasdfj/tinytcp
cd /d tinytcp
mkdir build 2>nul
cmake -B build
cmake --build build
```

### 2. Read the documentation

#### POSIX

```bash
cd docs
cat *.md
```

#### Windows

```bat
cd docs
type *.md
```

> **NOTE:** It is highly suggested that you read the documentation.
