#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <string>

typedef std::tuple<std::string, int> Student;
typedef std::vector<Student> Group;

inline void print_usage_message(const std::string &program_name) {
    std::cout << "Usage: " << program_name << " file\n";
}

inline void print_error_in_cin(unsigned int line_number, const std::string &line) {
    std::cout << "Error in cin, line " << line_number << ": " << line << "\n";
}

bool verify_id(const std::string &id) {
    return !id.empty();//TODO placeholder
}

auto read_student_list() {
    //returns std::vector<std::tuple<std::string, int>>
    // TODO styczyn
}

bool check_basic_group_validity(const std::string &line) {
    return line.substr(0, 5) == "grupa" &&
           line[5] >= '1' &&
           line[5] <= '8' &&
           line[6] == '/' &&
           line.substr(7, 7) == "zadanie" &&
           line[14] >= '1' &&
           line[14] <= '6' &&
           line[15] == '/';
}

Student parse_student(const std::string &id) {
    return {id, 0}; //TODO placeholder
}

std::string student_to_string(const Student& student) {
    std::string init;
    int id_number;
    std::tie(init, id_number) = student;
    return init + std::to_string(id_number);
}

std::vector<Group> read_groups(const std::vector<Student> &students) {
    // TODO joald
    std::string line;
    unsigned int line_number = 1;
    std::vector<Group> result;
    while (std::getline(std::cin, line)) {
        bool group_validity = check_basic_group_validity(line);
        size_t guardian = 15;
        std::vector<Student> group;
        do {
            guardian++;
            auto current_id = line.substr(guardian, 8);
            group_validity &= verify_id(current_id);
            group.push_back(parse_student(current_id));
            guardian += 8;
        } while (line[guardian] == '+');
        if (group_validity) {
            Group final_group;
            for (auto it = group.begin(); it != group.end(); ++it) {
                if (std::find(students.begin(), students.end(), *it) == students.end() ||
                    std::find(it + 1, group.end(), *it) != group.end()) {
                    print_error_in_cin(line_number, student_to_string(*it));
                } else {
                    final_group.push_back(*it);
                }
            }
            result.push_back(final_group);
        } else {
            print_error_in_cin(line_number, line);
        }
        line_number++;
    }
    return result;
}

void print_bad_students(const std::vector<Group> &groups,
                        const std::vector<Student> &students) {
    std::vector<int> deducted_points(students.size());

    // TODO implement the rest

    for (int i = 0; i < deducted_points.size(); ++i) {
        int current_id;
        std::tie(std::ignore, current_id) = students[i];
        std::cout << current_id << ";" << deducted_points[i] << ";\n";
    }
}

int main(int argc, char **argv) {

    if (argc != 1) {
        //TODO: Throw error
        print_usage_message(argv[0]);
        return 1;
    }
    auto students = read_student_list();
    auto groups = read_groups(students);
    print_bad_students(students, groups);

    return 0;
}