# Minishell Project Roadmap

**Created for:** kaisen1337
**Date:** 2025-03-26

## Introduction
This roadmap provides a structured approach to building a Minishell project, breaking down the process into logical stages with detailed learning objectives and implementation steps.

---

## Stage 1: Foundation & Basic Shell Structure (Weeks 1-2)

### Learning Objectives:
1. **Unix Process Model**
   - Understand how processes work in Unix systems
   - Learn about process creation, termination, and hierarchies
   - Study `fork()`, `wait()`, `waitpid()`, and `exit()`

2. **File Descriptors & I/O**
   - Learn about stdin (0), stdout (1), and stderr (2)
   - Understand file descriptor tables and inheritance
   - Study `open()`, `close()`, `read()`, and `write()`

3. **Command Execution**
   - Learn about the `exec` family of functions
   - Understand environment variables and how they're passed
   - Study `execve()` and path resolution

4. **Signal Handling**
   - Understand Unix signals (SIGINT, SIGQUIT, etc.)
   - Learn how to set up signal handlers
   - Study `signal()` and `sigaction()`

### Implementation Steps:
1. **Set up project structure**
   - Create directory structure and Makefile
   - Set up version control (git)

2. **Create basic REPL (Read-Evaluate-Print Loop)**
   - Implement prompt display
   - Use readline() to get user input
   - Set up basic command history

3. **Implement basic command execution**
   - Parse simple commands (no arguments yet)
   - Fork and execute external commands
   - Handle basic error reporting

4. **Implement basic signal handling**
   - Handle Ctrl+C (SIGINT) and Ctrl+\ (SIGQUIT)
   - Make sure signals work properly for child processes

### Resources:
- [The Linux Programming Interface](https://man7.org/tlpi/)
- Man pages for: fork, wait, exec, signal
- [GNU Readline Documentation](https://tiswww.case.edu/php/chet/readline/rltop.html)

---

## Stage 2: Command Parsing & Builtins (Weeks 3-4)

### Learning Objectives:
1. **Lexical Analysis & Parsing**
   - Learn about tokenization and parsing techniques
   - Understand command arguments and quoting rules
   - Study finite state machines for parsing

2. **Environment Variables**
   - Understand how environment variables work
   - Learn how to modify, add, and remove variables
   - Study `getenv()`, environment array structure

3. **Shell Built-in Commands**
   - Understand the difference between builtins and external commands
   - Learn implementation details of common builtins
   - Study how to maintain shell state across command executions

### Implementation Steps:
1. **Enhance command parsing**
   - Split command line into command and arguments
   - Handle whitespace properly
   - Implement basic quote handling (single and double quotes)

2. **Implement environment variable functionality**
   - Store and manage environment variables
   - Support variable expansion ($VAR syntax)

3. **Implement basic built-in commands**
   - `echo`: with option -n
   - `cd`: with relative/absolute paths and `~`
   - `pwd`: print working directory
   - `env`: display environment variables
   - `export`: set environment variables
   - `unset`: remove environment variables
   - `exit`: exit the shell with status code

### Resources:
- POSIX Shell Command Language specification
- Bash reference manual for builtin behavior
- Examples of simple parsers in C

---

## Stage 3: Redirections & Pipes (Weeks 5-6)

### Learning Objectives:
1. **File Redirection**
   - Understand input/output redirection mechanisms
   - Learn about file descriptor duplication
   - Study `dup()`, `dup2()` functions

2. **Pipes**
   - Understand how pipes work for inter-process communication
   - Learn about pipe creation and management
   - Study `pipe()` function and pipe descriptors

3. **Advanced Process Management**
   - Learn about process groups and sessions
   - Understand job control concepts
   - Study `setpgid()`, `tcsetpgrp()`

### Implementation Steps:
1. **Implement input/output redirections**
   - `<` input redirection
   - `>` output redirection
   - `>>` append output redirection

2. **Implement pipe handling**
   - Create proper parent-child process structure
   - Set up pipes between processes
   - Handle multiple pipes in a command chain

3. **Enhance parser to recognize redirection and pipe operators**
   - Update tokenizer to recognize `<`, `>`, `>>`, and `|`
   - Build a command structure to represent redirections and pipes

### Resources:
- Examples of simple shell implementations
- Man pages for dup2, pipe
- Advanced Unix Programming guides

---

## Stage 4: Advanced Features & Polishing (Weeks 7-8)

### Learning Objectives:
1. **Error Handling & Edge Cases**
   - Learn proper error reporting techniques
   - Understand how to handle edge cases in shell syntax
   - Study error codes and their meaning

2. **Signal Handling in Complex Scenarios**
   - Understand signal propagation in process groups
   - Learn about signal blocking and masking
   - Study advanced signal handling techniques

3. **Memory Management**
   - Understand proper memory allocation/deallocation
   - Learn techniques to prevent memory leaks
   - Study tools for memory debugging

### Implementation Steps:
1. **Implement advanced features**
   - Handle environment variable expansion in quotes
   - Implement exit status variable `$?`
   - Add support for single quotes (no interpretation) and double quotes (with variable expansion)

2. **Implement comprehensive error handling**
   - Set proper exit codes for command failures
   - Handle syntax errors gracefully
   - Improve error messages

3. **Polish and optimize**
   - Check for and fix memory leaks
   - Ensure clean termination in all scenarios
   - Test edge cases and unusual inputs

4. **Add bonus features (optional)**
   - Command history navigation
   - Wildcard expansion
   - Logical operators (`&&`, `||`)
   - Subshells with parentheses

### Resources:
- Valgrind for memory leak detection
- POSIX standard for shell behavior in corner cases
- Shell testing frameworks

---

## Testing & Debugging Tips

1. **Testing Strategy**
   - Test each feature in isolation
   - Create test scripts for automated testing
   - Compare output with bash for validation

2. **Debugging Tools**
   - GDB for runtime debugging
   - Valgrind for memory issues
   - Custom debug prints with detailed information

3. **Common Issues & Solutions**
   - Zombie processes: ensure proper wait calls
   - Signal handling: check signal mask and handlers
   - Memory leaks: track allocations and free properly
   - Parsing errors: use state machines for robust parsing

---

## Additional Resources

1. **Books**
   - "Advanced Programming in the UNIX Environment" by W. Richard Stevens
   - "The Linux Programming Interface" by Michael Kerrisk

2. **Online Documentation**
   - [Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html)
   - [POSIX Shell Command Language](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/contents.html)

3. **Tools**
   - [Readline Documentation](https://tiswww.case.edu/php/chet/readline/rltop.html)
   - [Valgrind User Manual](https://valgrind.org/docs/manual/manual.html)
   - [GDB Documentation](https://sourceware.org/gdb/current/onlinedocs/gdb/)

---

## Project Milestones Checklist

### Basic Shell
- [ ] Display prompt and read commands
- [ ] Execute simple commands
- [ ] Handle command-line arguments

### Parsing
- [ ] Split input into tokens
- [ ] Handle quotes
- [ ] Parse environment variables

### Builtins
- [ ] Implement echo
- [ ] Implement cd
- [ ] Implement pwd
- [ ] Implement export
- [ ] Implement unset
- [ ] Implement env
- [ ] Implement exit

### Redirections & Pipes
- [ ] Implement input redirection (<)
- [ ] Implement output redirection (>)
- [ ] Implement append redirection (>>)
- [ ] Implement pipes (|)

### Signal Handling
- [ ] Handle Ctrl+C (SIGINT)
- [ ] Handle Ctrl+\ (SIGQUIT)
- [ ] Handle Ctrl+D (EOF)

### Error Handling
- [ ] Proper error messages
- [ ] Appropriate exit codes
- [ ] Handle edge cases

### Memory Management
- [ ] No memory leaks
- [ ] Proper resource cleanup
- [ ] Robust error recovery

Good luck with your Minishell project!