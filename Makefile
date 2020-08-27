
Toolchain=g++
Compile_Flag=-c
Execute_Flag=-o
all: hello
hello: main.o Storage.o FAT.o
	$(Toolchain) main.o Storage.o FAT.o $(Execute_Flag) hello
main.o: main.cpp
	$(Toolchain) $(Compile_Flag) main.cpp -g
Storage.o: Storage.cpp
	$(Toolchain) $(Compile_Flag) Storage.cpp -g
FAT.o: FAT.cpp
	$(Toolchain) $(Compile_Flag) FAT.cpp -g
clean:
	rm -rf *o hello