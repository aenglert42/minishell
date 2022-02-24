# minishell
The aim of this project is to create a simple shell, to learn about processes, file descriptors and pipes. Inspired by the "42 Coding School" exercise "minishell" (January 2022).

## Table of contents
* [Introduction](#introduction)
  * [Allowed functions](#allowed-functions)
  * [Description](#description)
* [Approach](#approach)
* [Prerequisites](#prerequisites)
* [How to launch](#how-to-launch)
* [Example](#example)
* [Resources](#resources)
* [Notes](#notes)

## Introduction
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

## Approach
My approach was to first get an understanding of how the original bash works so that I can reimplement it. For this the [Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html) was the most important resource when I had to look up things, I didn't know how they were supposed to work.Only reading the table of contend already gives an idea of the sequence in which things happen and gives a nice overview of its single elements.

The [Definitions](https://www.gnu.org/software/bash/manual/bash.html#Definitions) were super useful. Here you learn what __metacharacters__, __words__, __operators__ and __tokens__ are.

Some of the most important chapters of the manual for this exercise are: [Quoting](https://www.gnu.org/software/bash/manual/bash.html#Quoting), [Pipes](https://www.gnu.org/software/bash/manual/bash.html#Pipelines), [Redirections](https://www.gnu.org/software/bash/manual/bash.html#Redirections), [Executing Commands](https://www.gnu.org/software/bash/manual/bash.html#Executing-Commands) and [Builtins](https://www.gnu.org/software/bash/manual/bash.html#Shell-Builtin-Commands).

In a nutshell when my minishell (which will not be as complex as bash) reads and executes input from the command line it has to do something like this:

* Split the input up into __tokens__ (__words__ and __operators__), via the __metacharacters__, considering the quoting rules.
* Perform expansions.
* Parse the expanded __tokens__ into __commands__.
* Set up redirections, if necessary.
* Execute the command(s).

From my understanding a shell consists of three main parts: the __lexer__, the __parser__ and the __executor__.


#### Lexer
The __lexer__ (also called __lexical analyzer__ or __tokenizer__) splits the input into __tokens__, using the __metacharacters__.

#### Parser
The __parser__ processes the tokens and builds a command table for each command. This happens following the shell's grammar. The grammar is written in a format called __Backus-Naur Form__ and looks like [this](https://cmdse.github.io/pages/appendix/bash-grammar.html).

This is pretty confusing. I thought about the following "building blocks" to parse the command table:

__simple command__: executable [argument]*

A simple command is an executable followed by 0 or more arguments.

__input redirection__: < filename

A input redirection is a input operator followed by a filename.

__output redirection__: > filename

A output redirection is a output operator followed by a filename.

__append redirection__: >> filename

A append redirection is a append operator followed by a filename.

__heredoc__: << delimiter

A heredoc is a heredoc operator followed by a delimiter.

__stdin redirection__: [input redirection] / [heredoc]

A stdin redirection is a input redirection or a heredoc.

__stdout redirection__: [output redirection] / [append redirection]

A stdout redirection is a output redirection or a append redirection.

__command__: [simple command] [stdin redirection]* [stdout redirection]*

A command can contain a simple command, 0 or more stdout redirections, 0 or more stdin redirections.

__pipeline__: [command] [ | [command] ]*

A pipeline consisting of a command and 0 or more pipe operators followed by another command.

The order of the "building blocks" themselves does not matter. However the order within them does.

#####Command table

ls

cat Makefile

echo Hello world! > outfile1

< infile  > outfile2 wc -w

| # | executable | list of arguments | list of stdin redirections | list of stdin redirections |
| :---- | :---- | :---- | :---- | :---- |
|1|ls|-|-|-|
|2|cat|Makefile|-|-|
|3|echo|Hello, world!|-|outfile1|
|4|wc|-w|infile|outfile2|

#### Executor
The __executor__ executes the command table. 

## Prerequisites
Tested on Ubuntu 20.04.3 LTS
* gcc (```sudo apt-get install gcc```)
* make (```sudo apt-get install make```)
* readline (```$ sudo apt-get install lib32readline8 lib32readline-dev```)

## How to launch
Compile the program via the Makefile by using ```$ make``` in the root directory of the repository.

Run it like this:

```
$ ./minishell
```

## Example
![minishell](https://user-images.githubusercontent.com/80413516/155508179-96505e8a-92f6-46e7-8c57-3d346b9782eb.gif)

## Resources
[Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html)

## Notes
The parser is used from a former teamproject and was coded by [jzhou](https://github.com/AmberLawr).

Please note that the external "readline" function can produce some memory leaks. For this exercise I did not care about them.
