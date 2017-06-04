OBJS := hash_table.o list.o main.o
all: main

%.o: %.c *.h
	$(CC) -c -o $@ $< $(CFLAGS)
main: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)
