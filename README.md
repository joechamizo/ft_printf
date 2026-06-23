# ft_printf

## 👤 Project Overview and AI Collaboration

To keep the project understandable, maintainable, and aligned with the 42 evaluation process, the development was structured around efficient handling of variable arguments, a unified state control mechanism, and an optimized data flushing stream.

- **Unified state architecture:** Designed and implemented a control mechanism based on a single structure (`t_printf`) to encapsulate the buffer and flag states, removing the need for global variables.
- **Output optimization:** Implemented a buffering mechanism to mitigate the performance cost of system calls, accumulating characters in RAM before performing write operations.
- **Advanced modularity:** Structured the execution flow into atomic, dedicated modules to strictly comply with the 42 Norm restriction of a maximum of 5 functions per file.

---

## 📝 Description

The **ft_printf** project consists of recreating the famous `printf` function from the standard C library (`libc`). The primary objective is to learn how to handle variadic functions and to delve deep into the efficient management of data streams through the use of an output buffer.

This implementation faithfully mimics the original behavior of `printf`, returning the total number of printed characters and handling various types of formatting conversions and flags under the strict constraints of the 42 Norm.

---

## 📂 Project Structure

To comply with the restriction of a maximum of 5 functions per file, the source code is meticulously organized as follows:

- **🚀 ft_printf.c:** Main entry point, buffer lifecycle management, and main format parsing loop.
- **🔍 ft_parser.c:** Syntactic analysis and flag capture (`-`, `0`, `.`, `#`, ` `, `+`), field width computation, and precision handling.
- **🛤️ ft_dispatch.c:** Conversion dispatcher responsible for routing execution control to the correct module based on the specifier.
- **🔢 ft_print_nums.c:** Processing and printing logic for integers (`%d`, `%i`, `%u`) with rigorous sign management.
- **⬢ ft_print_hex.c:** Conversion logic for hexadecimal formats (`%x`, `%X`) and memory addresses/pointers (`%p`).
- **🛠️ ft_utils.c:** Core base utilities, numerical length calculation, and arithmetic base management.

---

## 📐 Technical Decisions: Algorithm and Data Structure

The project is designed under a modular paradigm where the control structure directs data through memory buffers before interacting with the operating system kernel.

### 💾 Unified Data Structure: `t_printf`

A unified data structure was designed to act as the "global state" of the function. It contains the character buffer, the current index, the total printed byte counter, and all boolean and numerical flag variables.

- **Justification:** It allows total and secure access to information via a single pointer passed by reference. This completely eliminates the use of forbidden global variables and facilitates clean modular communication across the different files of the project.

### ⚡ Output Algorithm: Active Buffer Management

Instead of printing every single character individually using repeated primitive system calls, the system utilizes a static 4096-byte buffer in memory.

- **Justification:** System calls (`write`) are computationally expensive operations due to the context switch overhead between user space and kernel space. Minimizing these calls drastically optimizes the overall performance of the function by accumulating data in RAM and flushing the block only when the buffer is full or when the function terminates.

### 🎯 Formatting Algorithm: Hierarchical Pre-computation

To correctly resolve the complex combination of bonus flags, a predictive three-step algorithm is used:

1. **Capture:** The parser extracts numerical values for field width and precision, and toggles active flags.
2. **Computation:** The total size of the final text "bounding box" is mathematically determined (calculating padding spaces, precision zeros, prefixes like `0x`, or `+`/`-` signs alongside the raw numerical value).
3. **Flushing:** The formatted components are pushed to the buffer in a strict, sequential hierarchical order, ensuring the output matches the standard `libc` behavior.

---

## 🧠 Defense Guide and Edge Cases

To pass the most rigorous automated test suites in the 42 community, the codebase implements robust native solutions for critical scenarios:

- **Null Pointer Management (`%s` and `%p` with NULL):** If a `NULL` pointer is passed to a string specifier, it safely prints `(null)` (or system-specific variations). For `%p` pointers, it manages the correct output layout as `(nil)` or `0x0`.
- **Integer Overflows:** Handling boundary values such as `LONG_MIN` or `INT_MIN` is performed by casting up to higher-capacity data types (`long long` or `unsigned long long`) during intermediate arithmetic transformations to avoid undefined behavior.
- **Conflicting Flags and Precedence:** The codebase implements an implicit precedence logic hierarchy. For example, the `-` flag (left alignment) completely overrides the `0` flag (zero padding), and the `+` flag (always show sign) takes priority over the ` ` (blank space) flag.

---

## 🛠️ Usage and Compilation

### Requirements
- `cc`, `clang`, or `gcc`
- `make` automation utility
- Unix-based environment (Linux, macOS)

### Library Compilation

To generate the static library file (`libftprintf.a`), execute the base command in the project root:
```bash
make
```
The Makefile includes the mandatory rules required by the subject: `all`, `clean`, `fclean`, and `re`.

### Linking and Integration

To use `ft_printf` inside your own C source code, include its header file and link the compiled static `.a` archive during your final binary compilation:

```c
#include "ft_printf.h"

int main(void)
{
    ft_printf("Hello %s, the number is %+10.5d\n", "World", 42);
    return (0);
}
```

```bash
gcc main.c libftprintf.a -o my_program
./my_program
```

---

## 📚 Resources and References

### References
- Linux Programmer's Manual: `printf(3)` reference page.
- ISO/IEC 9899 Standard: Official documentation on variadic types and associated macros (`va_list`, `va_start`, `va_arg`, `va_end`).
- System call optimization guidelines for POSIX-compliant systems.

### AI Usage Statement
Generative artificial intelligence assistance was strictly used as an architectural optimization and support tool during the project workflow for:
- **Architectural Design:** Conceptualizing the unified `t_printf` control structure for safe cross-file modularity.
- **Memory Optimization:** Refactoring the internal output buffer flushing logic to guarantee the absolute minimum amount of `write()` execution paths.
- **Documentation:** Structural formatting and visual layout generations of this README.md file schema.

All generated suggestions were manually reviewed, adapted, tested, and validated with:
- `norminette` checks;
- Automated test suites (ensuring total absence of memory leaks).

---

## ⚖️ Academic Disclaimer

This repository has been created for purely academic purposes as part of my personal learning journey through the **42 network** curriculum.

* **Use at your own risk:** I do not take any responsibility for how the code in this repository is used, nor for any consequences arising from its duplication, modification, or reuse in your own project submissions.
* **42 Plagiarism Policy:** 42 students are heavily reminded that plagiarism or direct code copying without fully understanding its inner workings violates the school rules and can be severely penalized by both automated testing systems (*Moulinette*) and human peer-evaluators.
* **Purpose:** This codebase is shared with the sole purpose of serving as an engineering reference, technical guide, or inspiration for building advanced custom Makefiles and automated interactive test suites.
