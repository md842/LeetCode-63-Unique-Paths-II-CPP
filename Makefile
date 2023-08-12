CFLAGS = -std=gnu17 -Wall -O0 -pipe -fno-plt -fPIC
CPPFLAGS = -Wall -O0 -pipe -fno-plt -fPIC

default: unique_paths_cpp

unique_paths: unique_paths.c
	$(CC) $(CFLAGS) unique_paths.c -o unique_paths

unique_paths_cpp: unique_paths.cpp
	g++ $(CPPFLAGS) unique_paths.cpp -o unique_paths

.PHONY: clean
clean:
	rm -f unique_paths
