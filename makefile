
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
	
test-punkty: ./punkty
	$(info Testing punkty...)
	@bash ./tests/utest.sh --tneed-err "./punkty ./tests/students.id" ./tests
	@touch ./punkty

.PHONY: all clean test
