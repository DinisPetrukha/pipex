# Pipex Project

## Overview

This project is the 7th project at School 42, aiming to recreate the command shell pipe mechanism. The shell command to replicate is:

 ```bash
 < infile cmd1 | cmd2 > outfile
 ```

To use the program, follow the format:

```bash
./pipex <infile> <cmd1> <cmd2> <outfile>
```

Example:

```bash
./pipex infile cat "grep -l" outfile
```

The program takes an input file (infile) that serves as the STDIN for the program. It then executes the specified commands using the fork(), pipe(), and execve() functions. The result (STDOUT) is redirected to the output file (outfile). File names are not fixed.. If outfile does not exist, the program creates it.

## Bonus Feature: here_doc & multiple cmd arguments

As a bonus feature, the program implements the "here_doc" mechanism, which uses the user's terminal (STDIN) instead of a separate file. The mechanism continues until it encounters a user-chosen delimiter. To activate this feature, use the string "here_doc" as the argv[1]. The number of commands that can be executed is unlimited.

Usage:

```bash
./pipex here_doc <limiter> <cmd1> <cmd2> [...] <outfile>
```

Example:

```bash
./pipex here_doc EOF cat "grep t" "wc -l" outfile
```

### Installation

Clone the repository:

```bash
git clone git@gitlab.com:dinis-petrukha/pipex.git pipex
cd pipex
```

Execute the Makefile:
```bash
make
```

Feel free to explore and contribute to the project!
