# Minishell

## Introduction

Minishell is a custom implementation of a Unix shell, developed as part of the 42 Network curriculum. This project aims to provide a deeper understanding of system calls, process management, and basic shell functionality by recreating a simple yet functional shell.

## About Minishell

Minishell mimics the behavior of traditional Unix shells, providing essential features such as command execution, environment variable handling, and support for various shell-specific functionalities. The goal was to implement a shell that behaves similarly to bash, with certain constraints and requirements specific to the project.

## Key Features

- **Prompt Display**: A prompt is displayed when waiting for a new command.
- **Command History**: Keeps a history of commands entered during the session.
- **Executable Search and Launch**: Finds and executes the correct program based on the `PATH` environment variable or a provided relative/absolute path.
- **Limited Global Variables**: Uses no more than one global variable.
- **Quote Handling**:
  - Single quotes (`'`) prevent the interpretation of meta-characters.
  - Double quotes (`"`) prevent the interpretation of meta-characters except for the dollar sign (`$`).
- **Redirections**:
  - `<` for input redirection.
  - `>` for output redirection.
  - `<<` for heredoc with a specified delimiter.
  - `>>` for output redirection in append mode.
- **Pipes**: Implements piping (`|`) to connect the output of one command to the input of another.
- **Environment Variables**: Expands environment variables prefixed with `$`.
- **Special Variables**: Expands `$?` to the exit status of the most recent foreground pipeline.
- **Signal Handling**:
  - `ctrl-C` displays a new prompt.
  - `ctrl-D` exits the shell.
  - `ctrl-\` does nothing in interactive mode.
- **Built-in Commands**:
  - `echo` with `-n` option.
  - `cd` with relative or absolute path.
  - `pwd` without options.
  - `export` without options.
  - `unset` without options.
  - `env` without options or arguments.
  - `exit` without options.

## Bonus Features

- **Logical Operators**: Implements `&&` and `||` with parenthesis for priority.
- **Wildcards**: Supports wildcard `*` for the current working directory.

## Installation and Usage

To compile and run Minishell, follow these steps:

1. **Clone the Repository**:
    ```sh
    git clone git@github.com:iobba/minishell.git
    cd minishell
    ```

2. **Compile the Program**:
    ```sh
    make
    ```

3. **Run Minishell**:
    ```sh
    ./minishell
    ```

## Makefile

The Makefile includes the following targets:

- `all`: Compiles the program.
- `clean`: Removes object files.
- `fclean`: Removes object files and the executable.
- `re`: Recompiles the program.
