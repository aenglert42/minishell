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
* "<<" should redirect input like a basic "heredoc". It doesn’t need to update history or handle expansion.

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

The [Definitions](https://www.gnu.org/software/bash/manual/bash.html#Definitions) were super useful. Here you learn what _metacharacters_, _words_, _operators_ and _tokens_ are.

Some of the most important chapters of the manual for this exercise are: [Quoting](https://www.gnu.org/software/bash/manual/bash.html#Quoting), [Pipes](https://www.gnu.org/software/bash/manual/bash.html#Pipelines), [Redirections](https://www.gnu.org/software/bash/manual/bash.html#Redirections), [Executing Commands](https://www.gnu.org/software/bash/manual/bash.html#Executing-Commands) and [Builtins](https://www.gnu.org/software/bash/manual/bash.html#Shell-Builtin-Commands).

In a nutshell when my minishell (which will not be as complex as bash) reads and executes input from the command line it has to do something like this:

* Split the input up into _tokens_ (_words_ and _operators_), via the _metacharacters_, considering the quoting rules.
* Perform expansions.
* Parse the expanded _tokens_ into _commands_.
* Set up redirections, if necessary.
* Execute the command(s).

From what I learned so far, I decided to devided the shell into three main parts: the [_lexer_](#lexer), the [_parser_](#parser) and the [_executor_](#executor).


### Lexer
The lexer (also called _lexical analyzer_ or _tokenizer_) splits the input into a list of _tokens_, using the _metacharacters_ and performs expansions and quoteremoval. 

For example the commandline:

```<<END <$HOMEinfile grep -v 42 | >> outfile1 wc -l > outfile2 | ls | >outfile3 | echo "don't | split"```

will give us the following token list:

```<<``` ```END``` ```<``` ```/home/infile``` ```grep``` ```-v``` ```42``` ```|``` ```>>``` ```outfile1``` ```wc``` ```-l``` ```>``` ```outfile2``` ```|``` ```ls```
 ```|``` ```>``` ```outfile3``` ```|``` ```echo``` ```don't | split```

 Note how all the unquoted whitespaces disappeared.

### Parser
The parser processes the tokens and creates a command table (a data structure that stores the commands that will be executed). This happens following the shell's grammar. The grammar is written in a format called _Backus-Naur Form_ and looks like [this](https://cmdse.github.io/pages/appendix/bash-grammar.html).

This is pretty confusing. For a better understanding, I tried to write down my own "grammar receips". I used my own words (so it might not be coherent with the original terms):

__[simple command]__ = [executable [argument]*]

> A simple command is an executable followed by 0 or more arguments.

__[input redirection]__ = [<filename]

> A input redirection is a input operator followed by a filename.

__[output redirection]__ = [>filename]

> A output redirection is a output operator followed by a filename.

__[append redirection]__ = [>>filename]

> A append redirection is a append operator followed by a filename.

__[heredoc]__ = [<<delimiter]

> A heredoc is a heredoc operator followed by a delimiter.

__[redirection]__ = [[input redirection] / [output redirection] / [append redirection] / [heredoc]]

> A redirection is an input redirection or an outout redirection or an append redirection or a heredoc.

__[command]__ = [[simple command] [redirection]*]

> A command can contain a simple command and 0 or more redirections. The order of the elements does not matter.

__[pipeline]__ = [[command]] [[| [command]]*]

> A pipeline consisting of a command and 0 or more pipe operators followed by another command.

So the minishell input will have the following format:

```
[executable [argument]*] [< filename]* [<< delimiter]* [> filename]* [>> filename]* [| [[executable [argument]*] [< filename]* [<< delimiter]* [> filename]* [>> filename]*]*
```

### Command table
Knowing the grammar, creating the command table from the tokens is easy. Let's try it with our example token list:

```<<``` ```END``` ```<``` ```/home/infile``` ```grep``` ```-v``` ```42``` ```|``` ```>>``` ```outfile1``` ```wc``` ```-l``` ```>``` ```outfile2``` ```|``` ```ls```
 ```|``` ```>``` ```outfile3``` ```|``` ```echo``` ```don't | split```

First we search for the pipe operators, as they separate the commands.

```<<``` ```END``` ```<``` ```/home/infile``` ```grep``` ```-v``` ```42``` ~~```|```~~ ```>>``` ```outfile1``` ```wc``` ```-l``` ```>``` ```outfile2``` ~~```|```~~ ```ls``` ~~```|```~~ ```>``` ```outfile3``` ~~```|```~~ ```echo``` ```don't | split```

This will give us the commands:

Command1: ```<<``` ```END``` ```<``` ```/home/infile``` ```grep``` ```-v``` ```42```

Command2: ```outfile1``` ```wc``` ```-l``` ```>``` ```outfile2```

Command3: ```ls```

Command4: ```>``` ```outfile3```

Command5: ```echo``` ```don't | split```

Within each command we then search for the redirection operators, because we know that the token following a redirection operator is the associated filename/delimiter.

Command1: ~~```<<```~~ ~~```END```~~ ~~```<```~~ ~~```/home/infile```~~ ```grep``` ```-v``` ```42```

Command2: ~~```>>```~~ ~~```outfile1```~~ ```wc``` ```-l``` ~~```>```~~ ~~```outfile2```~~

Command3: ```ls```

Command4: ~~```>```~~ ~~```outfile3```~~

Command5: ```echo``` ```don't | split```

So what's left is the executable and the arguments. As the arguments follow the executable we now know that the first token that is left is the executable and the rest are the arguments.

Command1: ```grep``` ```-v``` ```42```

Command2: ```wc``` ```-l```

Command3: ```ls```

Command4: -

Command5: ```echo``` ```don't | split```

| # | executable | list of arguments | list of stdin redirections | list of stdout redirections |
| :---- | :---- | :---- | :---- | :---- |
|Command1|```grep```|```-v``` ```42```|```<<END``` ```</home/infile```|-|
|Command2|```wc```|```-l```|-|```>>outfile1``` ```>outfile2```|
|Command3|```ls```|-|-|-|
|Command4|-|-|-|```>outfile3```|
|Command5|```echo```|```don't \| split```|-|-|

### Executor
The executor takes the command table generated by the parser and creates a new process for each command that is not a builtin. If necessary it will create pipes to forward the output of one process to the input of the next one and redirect the standard in- and output.

Creating the processes is necessary, because to execute the non-builtin executables, we will use the _execve_ function, that basically overrides all following code by the code of the executable. This means after the first successful _execve_ call the entire program would end. Calling it in a child process will only end that, while the parent process goes on.

[How to fork a process](https://www.youtube.com/watch?v=cex9XrZCU14&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY&index=1)

[How to setup pipes](https://www.youtube.com/watch?v=6xbLgZpOBi8&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY&index=23)

[How to use the exec family functions](https://www.youtube.com/watch?v=uh2FqejQRk8&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY&index=11)

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

[Code Vault Playlist - Unix Processes in C](https://www.youtube.com/watch?v=cex9XrZCU14&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY)

## Notes
The parser is used from a former teamproject and was coded by [jzhou](https://github.com/AmberLawr).

Please note that the external "readline" function can produce some memory leaks. For this exercise I did not care about them.
