#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <string>
#include <optional>
#include <set>
#include <regex>
#include <exception>
#include <functional>

typedef std::tuple<std::string, std::string> Student;
typedef std::vector<Student> Group;

class InvalidFileException : public std::exception {
public:
   const char * what () const throw () {
      return "File is unreachable or not exists. Could not open it.";
   }
};

static const std::regex student_id_form_normal("^([a-z]{2}([0-9]{6}))$");
static const std::regex student_id_form_dashed("^([a-z]{2}m-([0-9]{4}))$");


inline void print_usage_message(const std::string &program_name) {
    std::cout << "Usage: " << program_name << " file\n";
}

inline void print_error_with_file(const std::string &filename) {
  std::cout << "Error: problem with file " << filename << "\n";
}

inline void print_error_in_cin(unsigned int line_number, const std::string &line) {
    std::cout << "Error in cin, line " << line_number << ": " << line << "\n";
}

inline void print_error_in_file(const std::string &filename, unsigned int line_number, const std::string &line) {
    std::cout << "Error in " << filename << ", line " << line_number << ": " << line << "\n";
}

template<typename T>
inline static constexpr bool is_in_range(const T& value, const T min, const T max) {
  return value == std::clamp(value, min, max);
}

inline static constexpr bool is_digit(const char& c) {
    return is_in_range(c, '0', '9');
}

inline static constexpr bool is_low_case_letter(const char& c) {
    return is_in_range(c, 'a', 'z');
}


std::optional<std::string> get_student_id(const std::string& id) {
    // Invalid length
    if(id.size() < 8) return {};

    std::smatch normalFormMatches;
    std::smatch dashedFormMatches;

    const bool isNormalForm = std::regex_search(id, normalFormMatches, student_id_form_normal);
    const bool isDashedForm = std::regex_search(id, dashedFormMatches, student_id_form_dashed);

    if(isNormalForm) {
      //std::cout << "MATCHED NORMAL FORM = "<<normalFormMatches[2].str()<<" from "<<id<<"\n";
      return {normalFormMatches[2].str()};
    } else if(isDashedForm) {
      //std::cout << "MATCHED DASHED FORM = "<<dashedFormMatches[2].str()<<" from "<<id<<"\n";
      return {dashedFormMatches[2].str()};
    } else {
      return {};
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
std::vector<Student> read_student_list(const char* filename, std::function<void(std::string, int, std::string)> loading_error_handler) {
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
                    loading_error_handler(std::string(filename), line_number, input_line);
                }
            } else {
                // Invalid ID
                loading_error_handler(std::string(filename), line_number, input_line);
            }
            ++line_number;
        }

        input_stream.close();
    } else {
        throw InvalidFileException();
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

//TODO Fix that
std::string student_to_string(const Student& student) {
    std::string init;
    std::string id_number;
    //std::tie(init, id_number) = student;
    //return init + std::to_string(id_number);
    return "";
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
        //std::tie(std::ignore, current_id) = students[i];
        std::cout << current_id << ";" << deducted_points[i] << ";\n";
    }
}

int main(int argc, char **argv) {

    if (argc != 2) {
        print_usage_message(argv[0]);
        return 1;
    }

    try {
      auto students = read_student_list(argv[1], print_error_in_file);
      auto groups = read_groups(students);
      print_bad_students(students, groups);
    } catch(const InvalidFileException& e) {
      print_error_with_file(argv[1]);
    }

    return 0;
}
