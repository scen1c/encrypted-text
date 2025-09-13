# Encrypted text

A tiny C++ console utility that demonstrates byte-wise XOR “encryption” of a string with a one-byte key (0–255). Supports interactive encrypt/decrypt, HEX display, and saving/loading from files.

> ⚠️ **Security note:** Single-byte XOR is **not** cryptographically secure. Use this only for learning/demo purposes.

---

## Features
- Menu-driven CLI:
  - **1) Write encrypted text**: read plaintext, XOR with key, show HEX, optionally save to `<name>.txt`.
  - **2) Find decrypted text**: paste HEX or load from file, XOR with key, show plaintext, optionally save.
- Key forced to one byte with `key &= 0xFF`.
- Prints ciphertext in hex (non-printable bytes become visible).
- Accepts HEX with or without spaces/newlines (e.g., `41 42 43` or `414243`).
- Robust input handling:
  - Ignores non-hex characters in HEX mode.
  - Odd trailing nibble is discarded (partial byte is ignored).

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

## Usage

### Main menu
```bash
-------------------------------
Encrypted Text Display Tool
------------------------------
Select an option:
1) Write encrypted text
2) Find decrypted text
0) Exit
Enter your choice (0-2):
```

#### 1) Write encrypted text → show HEX → optional save
```bash
Text: Hello world
Key (0-255): 42
Encrypted (hex): 62 4f 46 46 45 0a 5d 45 58 46 4e

Do you want to save encrypted text to file? (y/n): y
Write the name of this file (without extension): secrets
Encrypted text saved to secrets.txt
```
File format: plaintext HEX bytes separated by spaces, e.g.:
```bash
62 4f 46 46 45 0a 5d 45 58 46 4e
```
#### 2) Find decrypted text (HEX → text)

You can paste HEX or load from a file that contains HEX:
```bash
Decrypt source:
1) Enter encrypted text manually (HEX)
2) Load encrypted text from file (HEX)
Enter your choice (1-2): 1
Paste HEX string (example: 41 42 43 or 414243):
62 4f 46 46 45 0a 5d 45 58 46 4e
Key (0-255): 42
Decrypted text: Hello world

Save decrypted text to file? (y/n): y
Write the name of this file (without extension): plain
Decrypted text saved to plain.txt
```
Loading from file:
```bash
Enter your choice (1-2): 2
Enter file name (with or without .txt): secrets
Key (0-255): 42
Decrypted text: Hello world
```

## File I/O specifics

Save (encrypt/decrypt): appends a new line to <name>.txt.

Load (decrypt): reads entire file and extracts HEX bytes; non-hex chars are ignored.

Extensions: when loading, .txt is added automatically if omitted.

Implementation notes

Core transform: byte ^ key for every byte; same function is used for encrypt and decrypt.

HEX parser: ignores whitespace and non-hex chars; an odd trailing nibble is dropped.

Input buffer: after numeric prompts, the program clears cin newline before getline.

Limitations

Single-byte XOR is trivial to break; do not use for real data.

No authentication or integrity checking.

Binary plaintext printed after decrypt is sent to console as text (non-printables may not render nicely).

Troubleshooting

“could not read file or file is empty” — check filename and that the file contains HEX bytes.

Garbage on decrypt — verify you used the same key and that the HEX was not altered.

Odd HEX length — last half-byte is ignored by design; ensure full bytes are provided.
