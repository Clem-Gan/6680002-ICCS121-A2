all: release/fintrack

# compile 
release/fintrack: src/*.c
	mkdir -p release
	gcc -Wall -Wextra -I./include -g src/*.c -o release/fintrack

clean:
	rm -rf release

.PHONY: all clean