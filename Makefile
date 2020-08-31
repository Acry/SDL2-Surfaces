CFLAGS   = -Wall -Wextra -mtune=native -no-pie `sdl2-config --cflags`
LDFLAGS  = `sdl2-config --libs` -lm

.SUFFIXES:
.SUFFIXES: .c .o

srcdir	 = src/
TARGETS	 = 0 1 2 3 4 5 6 7 8 9 10 11

.PHONY: all
all: $(TARGETS)

# init & create
0: $(srcdir)0.c
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS)

# fill
1: $(srcdir)1.c
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS)

# set icon
2: $(srcdir)2.c
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS)

# refresh fill
3: $(srcdir)helper.c $(srcdir)3.c
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS)

# blit surface
4: $(srcdir)helper.c $(srcdir)4.c
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS)

# custom pointer
5: $(srcdir)helper.c $(srcdir)5.c
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS)

# fixed gradient
6: $(srcdir)helper.c $(srcdir)6.c
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS)

# refresh gradient
7: $(srcdir)helper.c $(srcdir)7.c
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS)

# animated gradient
8: $(srcdir)helper.c $(srcdir)8.c
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS) -lrt

# candy bar
9: $(srcdir)9.c
	@cc $(CFLAGS) -o $@ $^ $(LDFLAGS)

# manually flip surface
10: $(srcdir)10.c
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS)

# copper bars
11: $(srcdir)11.c
	@cc $(CFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	@rm $(TARGETS) 2>/dev/null || true

