#include <iostream>

inline void print_usage_message() {
	std::cout << "Usage: PROGRAM file\n";
}

int main(int argc, char** argv) {

    if(argc != 1) {
      //TODO: Throw error
			print_usage_message();
			return 1;
		}

    std::cout << "Hello World\n";

    return 0;
}
