
all: ./punkty
	$(info Compilation done.)

./punkty: ./punkty.cc
	$(info Compile punkty.cc ...)
	g++ -Wall -Wextra -O2 -std=c++17 punkty.cc -o punkty
	
clean:
	@rm -r -f -d ./punkty
	
rebuild: clean all
	
.PHONY: all clean
