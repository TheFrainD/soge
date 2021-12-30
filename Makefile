.PHONY: all clean

all:
	cd sandbox && make

run: all
	cd bin && ./game

clean:
	cd engine && make clean
	cd sandbox && make clean
	$(RM) -rf bin