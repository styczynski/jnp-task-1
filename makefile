
all: ./punkty
	$(info Compilation done.)
	@touch ./punkty

./punkty: ./punkty.cc
	$(info Compile punkty.cc ...)
	@g++ -Wall -Wextra -O2 -std=c++17 punkty.cc -o punkty
	
clean:
	@rm -r -f -d ./punkty
	
rebuild: clean all

test: test-punkty
	$(info Testing done..)
	
test-punkty: ./punkty
	$(info Testing punkty...)
	@bash  ./tests/utest.sh --tgout "\$$input_file_folder/moj_sort.out" --tierr --tpipe-out "./tests/sortuj_out \$$input \$$output" "echo \$$input_file_folder/idFile" "./tests/*/lineFile"
	@touch ./punkty

.PHONY: all clean test
