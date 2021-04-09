# COMPSCI 230 Computer Systems Principles
# Pipes Lab

The goal of this lab is to become familiar with the basics of the `pipe()`
function. As you know, processes are created with the `fork()` system call. This
allows the creation of concurrently executing processes. There are several
limitations (rightly so) in the process model such as process communication. In
this lab, you will learn how to use pipe to support inter-process communication.

To start working on this lab you must be logged in to the Edlab and in your
`cs230` directory. From this directory run the command:

```
$ git clone https://github.com/umass-cs-230/230-lab-bank-simulator
```

Take a moment to read through the manual for `pipe(2)`. This manual page
describes the pipe function which creates a new "pipe", a unidirectional data
channel that can be used for interprocess communication.

Compile the C file in the folder you just downloaded by running the Makefile:

```
$ make
```

You will notice that it does not compile because of missing symbols. Figure out
which header files you need to include in order to get this program to compile.
You should start with the man page for `pipe(2)`. After you are able to get this
program to compile, run the program to observe the results:

```
$ ./pipes
```

In the associated Gradescope assignment, describe to the best of your
understanding, what this code is doing.

Lastly, make a change to your program such that Cookie Monster says "Thank you!"
to Cookie Maker at the end. The output of the modified program should look like
the following:

```
Cookie Monster writing: I want cookies! (16 bytes)
Cookie Maker read: I want cookies! (16 bytes)
Cookie Maker writing: You got cookies! (17 bytes)
Cookie Monster read: You got cookies! (17 bytes)
Cookie Monster writing: Thank you! (11 bytes)
Cookie Maker read: Thank you! (11 bytes)
The parent cleaned up the cookie mess!
```

Paste your code in the associated Gradescope assignment.

