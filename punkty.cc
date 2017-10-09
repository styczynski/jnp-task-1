#include <iostream>

inline void print_usage_message(const std::string& program_name) {
	std::cout << "Usage: " << program_name << " file\n";
}

int main(int argc, char** argv) {

    if(argc != 1) {
		//TODO: Throw error
		print_usage_message(argv[0]);
		return 1;
	}

    std::cout << "Hello World\n";

    return 0;
}
