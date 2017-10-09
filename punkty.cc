#include <iostream>
#include <vector>

inline void print_usage_message(const std::string& program_name) {
	std::cout << "Usage: " << program_name << " file\n";
}

auto read_student_list() {
    //returns std::vector<std::tuple<std::string, int>>
    // TODO styczyn
}

auto read_groups(const std::vector<std::tuple<std::string, int>>& students) {
    // TODO joald
}

void print_bad_students(void, void) {

}

int main(int argc, char** argv) {

    if(argc != 1) {
		//TODO: Throw error
		print_usage_message(argv[0]);
		return 1;
	}
	auto students = read_student_list();
	auto groups = read_groups(students);
    print_bad_students(students, groups);

    std::cout << "Hello World\n";

    return 0;
}
