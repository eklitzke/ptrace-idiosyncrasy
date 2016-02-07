This repository demonstrates an interesting idiosyncrasy of the `ptrace(2)`
system call on Linux.

With the `kill(2)` system call if you send a valid signal number there are two
errors you can get. You will get `EPERM` if you don't have sufficient privileges
to send a signal to the target process. You will get `ESRCH` if the target
process doesn't exist.

The same is similar with `ptrace(2)` when using the `PTRACE_ATTACH` request. If
you don't have sufficient permissions to `PTRACE_ATTACH` to the specified pid
then you will get `EPERM`, and if the specified pid doesn't exist you will get
`ESRCH`, just as in `kill(2)`.

However, there is one interesting difference between thesse two system calls,
relating to their behavior if the target process is in the "exited" state.

If you run `make` in tihs project directory you will get three executables.

To see the idiosyncracy, in one shell run `./create_zombie` and it will print a
process id for the zombie process. This zombie process is in the exited state:

```
$ ./create_zombie
20755
```

You can use the supplied `./kill` command to send the target `SIGSTOP`. You can
also use the shell builtin `kill` or `/usr/bin/kill`, I just supplied my own
implementation to make it very clear what the actual return code of the
`kill(2)` system call is:

```
$ ./kill 20755
kill successful
```

You can use the supplied `./ptrace_attach` command to ptrace attach.
Alternatively, you can use the `strace(1)` command, e.g. `strace -p 20755`.
Here's what it looks like if you use my version:

```
$ ./ptrace_attach 20755
PTRACE_ATTACH: Operation not permitted
```

As you can see, the seemingly similar `kill(2)` and `ptrace(2)` system calls do
not behave the same for processes in the exited state.

I have more details about this issue
[on my blog](https://eklitzke.org/a-ptrace-idiosyncrasy).
