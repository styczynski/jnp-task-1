
all: ./punkty
	$(info Compilation done.)
	@touch ./punkty

./punkty: ./punkty.cc
	$(info Compile punkty.cc ...)
	@g++ -Wall -Wextra -O2 -std=c++17 punkty.cc -o punkty
	
clean:
	@rm -r -f -d ./punkty
	
rebuild: clean all

test: all test-punkty
	$(info Testing done..)
	
test-punkty: ./punkty ./_test_1.file
	$(info Testing punkty...)
	$(info $(shell ./punkty _test_1.file))
	@touch ./punkty

.PHONY: all clean test
