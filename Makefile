TARGETS = kill create_zombie ptrace_attach

all: $(TARGETS)

%.o: %.c
	$(CC) $< -c

create_zombie: create_zombie.o
	$(CC) $< -o $@

kill: kill.o parse_pid.o
	$(CC) $^ -o $@

ptrace_attach: ptrace_attach.o parse_pid.o
	$(CC) $^ -o $@

clean:
	rm -f $(TARGETS) *.o

.PHONY: all clean
