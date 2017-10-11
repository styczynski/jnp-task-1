#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <string>
#include <optional>
#include <set>

typedef std::tuple<std::string, int> Student;
typedef std::vector<Student> Group;

inline void print_usage_message(const std::string &program_name) {
    std::cout << "Usage: " << program_name << " file\n";
}

inline void print_error_in_cin(unsigned int line_number, const std::string &line) {
    std::cout << "Error in cin, line " << line_number << ": " << line << "\n";
}

inline void print_error_in_file(const std::string &filename, unsigned int line_number, const std::string &line) {
    std::cout << "Error in " << filename << ", line " << line_number << ": " << line << "\n";
}

inline static bool is_digit(const char& c) {
    return (c>='0') && (c<='9');
}

inline static bool is_low_case_letter(const char& c) {
    return (c>='a') && (c<='z');
}

// TODO Handle overflow anyway there below
// (I know, yes I know we ARE overkilling now...)
std::optional<int> parse_non_negative_integer(const std::string& input, const int starting_index=0) {
    const int len = input.size();
    int result = 0;
    for(int i=starting_index; i<len; ++i) {
        if(!is_digit(input[i])) {
            // Error: non digit character in input string!
            return std::optional<int>();
        } else {
            result = result * 10 + (input[i]-'0');
        }
    }
    return std::optional<int>(result);
}
  
std::optional<int> get_student_id(const std::string& id) {
    // Invalid length
    if(id.size() < 8) return std::optional<int>();
    
    // Two first are letters (lowercase, english alphabet)
    if(!is_low_case_letter(id[0]) ||
       !is_low_case_letter(id[1])) {
        return std::optional<int>();
    }
    
    // We test third character
    if(is_digit(id[2])) {
        // If we have digit we try to match FULL ID form
        // xx000000
        
        // Everything left should be a valid number
        return parse_non_negative_integer(id, 3);
    } else {
        // If not we try to match DASHED ID form
        // xxm-0000
        
        if(id[2] != 'm') return std::optional<int>();
        if(id[3] != '-') return std::optional<int>();
        
        // Everything left should be a valid number
        return parse_non_negative_integer(id, 4);
    }
  
}

bool verify_id(const std::string &id) {
    return get_student_id(id).has_value();
}

std::optional<Student> parse_student(const std::string &id) {
    const auto student_id = get_student_id(id);
    if(student_id.has_value()) {
      return std::optional<Student>(make_tuple(id, student_id.value()));
    } else {
      return std::optional<Student>();
    }
}

/**
 * Reads given file line by line.
 * Then tries to parse the line using parse_student(string)
 * and finally saves the student data into the collection.
 *
 * @param[in] filename : const char*
 * @returns collection containing all valid student entries from file
 *  
**/
std::vector<Student> read_student_list(const char* filename) {
    std::vector<Student> student_list;
    std::ifstream input_stream(filename);
    
    std::set<std::string> loaded_ids;
    
    if(input_stream.is_open()) {
        std::string input_line;
        unsigned int line_number = 1;
        while(std::getline(input_stream, input_line)) {
            const std::optional<Student> student = parse_student(input_line);
            if(student.has_value()) {
                const Student student_value = student.value();
                if(loaded_ids.find(std::get<0>(student_value)) == loaded_ids.end()) {
                    student_list.push_back(student_value);
                    loaded_ids.insert(std::get<0>(student_value));
                } else {
                    // Repeating ID
                    print_error_in_file(std::string(filename), line_number, input_line);
                }
            } else {
                // Invalid ID
                print_error_in_file(std::string(filename), line_number, input_line);
            }
            ++line_number;
        }
          
        input_stream.close();
    } else {
        // TODO File couldn't be loaded -> throw error
        std::cout<<"Could not read file!\n";
    }
    return student_list;
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
            group.push_back(parse_student(current_id).value());
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

void print_bad_students(const std::vector<Student> &students,
                        const std::vector<Group> &groups) {
    std::vector<int> deducted_points(students.size());

    // TODO implement the rest

    for (int i = 0; i < (signed)deducted_points.size(); ++i) {
        int current_id;
        std::tie(std::ignore, current_id) = students[i];
        std::cout << current_id << ";" << deducted_points[i] << ";\n";
    }
}

int main(int argc, char **argv) {

    if (argc != 2) {
        //TODO: Throw error
        print_usage_message(argv[0]);
        return 1;
    }
    
    auto students = read_student_list(argv[1]);
    auto groups = read_groups(students);
    print_bad_students(students, groups);
    
    return 0;
}
