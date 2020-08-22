CFLAGS   = -Wall -Wextra -mtune=native -no-pie `sdl2-config --cflags`
LDFLAGS  = `sdl2-config --libs` -lm

.SUFFIXES:
.SUFFIXES: .c .o

srcdir	 =src/
TARGETS	 = 1 2 2a 3 4 5 5a 5b 6 7 7a 8

.PHONY: all
all: $(TARGETS)

1: $(srcdir)1.c
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS)

2: $(srcdir)2.c
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS)

2a: $(srcdir)2a.c
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS)

3: $(srcdir)3.c
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS)

4: $(srcdir)4.c
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS)

5: $(srcdir)5.c
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS)

5a: $(srcdir)5a.c
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS)

5b: $(srcdir)5b.c
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS)

6: $(srcdir)6.c
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS)

7: $(srcdir)helper.c $(srcdir)7.c
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS)

7a: $(srcdir)helper.c $(srcdir)7a.c
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS)

8: $(srcdir)helper.c $(srcdir)8.c
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS) -lrt

.PHONY: clean
clean:
	@rm $(TARGETS) 2>/dev/null || true

