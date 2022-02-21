# minishell
The aim of this project is to create a simple shell, to learn about processes and file descriptors.

## Table of contents
* [Introduction](#introduction)
* [Prerequisites](#prerequisites)
* [How to launch](#how-to-launch)
* [Arguments](#arguments)
* [Example](#example)
* [Notes](#notes)


## Introduction
Inspired by the "42 Coding School" exercise "minishell" (January 2022).


### Allowed functions
readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history, printf, malloc, free, write, access, open, read, close, fork, wait, waitpid, wait3, wait4, signal,
sigaction, kill, exit, getcwd, chdir, stat, lstat, fstat, unlink, execve, dup, dup2, pipe, opendir, readdir, closedir, strerror, perror, isatty, ttyname, ttyslot, ioctl, getenv, tcsetattr,
tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs

### Description
The aim of the exercise is to write a program which does 

#### General Rules
* Global variables are forbidden.


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




## Notes
The parser is used from a former teamproject and was coded by @jzhou (https://github.com/AmberLawr)
