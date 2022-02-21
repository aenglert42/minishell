# minishell
The aim of this project is to create a simple shell, to learn about processes, file descriptors and pipes.

## Table of contents
* [Introduction](#introduction)
* [Prerequisites](#prerequisites)
* [How to launch](#how-to-launch)
* [Example](#example)
* [Notes](#notes)


## Introduction
Inspired by the "42 Coding School" exercise "minishell" (January 2022).


### Allowed functions
readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history, printf, malloc, free, write, access, open, read, close, fork, wait, waitpid, wait3, wait4, signal,
sigaction, kill, exit, getcwd, chdir, stat, lstat, fstat, unlink, execve, dup, dup2, pipe, opendir, readdir, closedir, strerror, perror, isatty, ttyname, ttyslot, ioctl, getenv, tcsetattr,
tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs

### Description
The aim of the exercise is to write a shell. Bash can be taken as a reference.
About the shell:

* It should not interpret unclosed quotes or unspecified special characters like '\\' or ';'.
* It should not use more than one global variable.
* It should show a prompt when waiting for a new command.
* It should have a working History.
* Search and launch the right executable (with relative, absolute or without path).
* Environment variables should expand to their values.
* "$?" should expand to the exit status of the most recently executed foreground pipeline.
* Singlequoates inhibit all interpretation of a sequence of characters.
* Doublequotes inhibit all interpretation of a sequence of characters except for environment variables.
* ```ctrl+c```, ```ctrl+d``` and ```ctrl+\``` should work like in bash.
* '|' pipes the output of a command to the input of the next command.
* '>' should redirect output.
* '<' should redirect input.
* ">>" should redirect output with append mode.
* It should have a basic "heredoc". It doesn’t need to update history or handle expansion.

The following builtins have to be implemented:
* __echo__ with option -n
* __cd__
* __pwd__ with no options
* __export__ with no options
* __unset__ with no options
* __env__ with no options or arguments
* __exit__ with no options


## Prerequisites
Tested on Ubuntu 20.04.3 LTS
* gcc
* readline (```$ sudo apt-get install lib32readline8 lib32readline-dev```)


## How to launch
Compile the program via the Makefile by using ```$ make``` in the root directory of the repository.

Run it like this:

```
$ ./minishell
```


## Example
_Screenshot_

![grafik](https://user-images.githubusercontent.com/80413516/155032152-f8cb99cd-2bd4-4f81-b52b-8c1698226d9e.png)

## Notes
The parser is used from a former teamproject and was coded by @jzhou (https://github.com/AmberLawr).

Please note that the external "readline" function can produce some memory leaks. For this exercise I did not care about them.
