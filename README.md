# Encrypted text

A tiny C++ console utility that demonstrates byte-wise XOR “encryption” of a string with a one-byte key (0–255) and prints the ciphertext in hexadecimal.

> ⚠️ **Security note:** Single-byte XOR is **not** cryptographically secure. Use this only for learning/demo purposes.

---

## Features
- Reads plaintext from stdin (including spaces).
- Reads a key `0–255` and forces it to one byte with `key &= 0xFF`.
- Encrypts each byte: `enc[с] = text[с] ^ key`.
- Prints ciphertext in hex (so non-printable bytes are visible).
- Decrypts back with the same key.

## Requirements
- C++11+ compiler (g++/clang++ on Linux/macOS, MSVC or MinGW on Windows).
- Terminal/console.

## Build

### Linux / macOS (g++/clang++)
```bash
g++ -std=c++11 -O2 -Wall -Wextra -o encrypted_text encrypted_text.cpp
./encrypted_text
```
### Windows (MSVC — “x64 Native Tools Command Prompt”)
```bash
cl /EHsc /O2 encrypted_text.cpp /Fe:encrypted_text.exe
encrypted_text.exe
```

### Windows (MinGW)
```bash
g++ -std=c++11 -O2 -Wall -Wextra -o encrypted_text.exe encrypted_text.cpp
encrypted_text.exe
```

## Usage

Interactive:
```bash
Text: Hello world
Key (0-255): 42
Encrypted (hex): 62 4f 46 46 45 0a 5d 45 58 46 4e 
Decrypted: Hello world
```
