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

typedef std::pair<std::string, std::string> Student;
typedef std::vector<Student> Group;
typedef bool LineError;
typedef bool InvalidFileException;

const int INDEX_OF_FIRST_INDEX_NUMBER_IN_GROUP = 15;
const int NUMBER_OF_FIRST_INPUT_LINE = 1;


static const std::regex student_id_form_normal("^([a-z]{2})([0-9]{6})$");
static const std::regex student_id_form_dashed("^([a-z]{2})m-([0-9]{4})$");


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


std::optional<Student> parse_student(const std::string& id) {
    // Invalid length
    if(id.size() < 8) return {};

    std::smatch normalFormMatches;
    std::smatch dashedFormMatches;

    const bool isNormalForm = std::regex_search(id, normalFormMatches, student_id_form_normal);
    const bool isDashedForm = std::regex_search(id, dashedFormMatches, student_id_form_dashed);

    if(isNormalForm) {
      std::cout << "MATCHED NORMAL FORM = "<<normalFormMatches[1].str()<<" | "<<normalFormMatches[2].str()<<" from "<<id<<"\n";
      return { make_pair(dashedFormMatches[1].str(), normalFormMatches[2].str()) };
    } else if(isDashedForm) {
      std::cout << "MATCHED DASHED FORM = "<<dashedFormMatches[1].str()<<" | "<<dashedFormMatches[2].str()<<" from "<<id<<"\n";
      return { make_pair(dashedFormMatches[1].str(), dashedFormMatches[2].str()) };
    } else {
      return {};
    }
}

bool verify_id(const std::string &id) {
    return parse_student(id).has_value();
}

/**
 * Throws LineError: false if condition pred is false.
 * @param[in] : const bool& 
 */
void throw_if_false(const bool& pred) {
	if (!pred) {
		throw false;
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
std::vector<Student> read_student_list(const std::string& filename, 
	std::function<void(std::string, int, std::string)> loading_error_handler) {
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
                if(loaded_ids.find(input_line) == loaded_ids.end()) {
                    student_list.push_back(student_value);
                    loaded_ids.insert(input_line);
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

/**
 * For a given line, checks if everything except 
 * student ids is correct.
 * 
 * @param[in] line : const std::string &
 * @returns if line is valid
 */
void check_basic_group_validity(const std::string &line) {
    throw_if_false(
      //
			// TODO Hej :) Wez uzyj is_in_range skoro powstalo XD
      // ok?
      //
      line.substr(0, 5) == "grupa" &&
			line[5] >= '1' &&
			line[5] <= '8' &&
			line[6] == '/' &&
			line.substr(7, 7) == "zadanie" &&
			line[14] >= '1' &&
			line[14] <= '6' &&
			line[15] == '/');
}

/**
 * Merges a std::pair of two objects of the same type,
 * on the condition that the objects have a valid binary operator+
 * @param[in] : const std::pair<T, T>&
 * @returns pair.first + pair.second
 */
template <typename T>
auto merge_pair(const std::pair<T, T>& pair) -> decltype(pair.first + pair.second) {
    T first;
    T second;
    std::tie(first, second) = std::move_if_noexcept(pair);
    return second + second;
}

/**
 * Reads student ids from std::string line and inserts correct ones
 * into the group while checking line correctness.
 * @param[in] : const Group&, const std::string&
 */
void fill_group(Group& group, const std::string& line) {
	size_t guardian = INDEX_OF_FIRST_INDEX_NUMBER_IN_GROUP;
	do {
		guardian++;
		auto current_id = line.substr(guardian, 8);
		throw_if_false(verify_id(current_id));
		group.push_back(parse_student(current_id).value());
		guardian += 8;
	} while (line[guardian] == '+');
	throw_if_false(line[guardian] == '\0');
}
/**
 * Reads groups of students from stdin using std::cin.
 * Verifies their validity, prints errors and saves all valid groups
 * in a std::vector.
 * 
 * @param[in] std::vector of known students
 * @returns correct groups of students
 */
std::vector<Group> read_groups(const std::vector<Student> &students_vector) {
    // TODO joald
    std::set<Student, std::function<bool(const Student&, const Student&)>> 
    students (students_vector.begin(), students_vector.end(), 
    [](const Student& left_student, const Student& right_student) {
		return left_student.first.size() == right_student.first.size() ? 
		left_student.second.size() > right_student.second.size() : 
		left_student.first.size() > right_student.first.size();});
    std::string line;
    unsigned int line_number = NUMBER_OF_FIRST_INPUT_LINE;
    std::vector<Group> result;
    while (std::getline(std::cin, line)) {
        try {
			check_basic_group_validity(line);
			Group group;
			fill_group(group, line);
			Group final_group;
			for (auto it = group.begin(); it != group.end(); ++it) {
				if (students.find(*it) == students.end() || 
					std::find(it + 1, group.end(), *it) != group.end()) {
					print_error_in_cin(line_number, merge_pair(*it));
				} else {
					final_group.push_back(*it);
				}
			}
			result.push_back(final_group);
		} catch (LineError e) {
			print_error_in_cin(line_number, line);
		}
		line_number++;
    }
    return result;
}

/**
 * Calculates how many points each student should be deducted and 
 * prints the result to stdout using std::cout.
 * @param[in] : const std::vector<Student> &, const std::vector<Group> &
 */
void print_bad_students(const std::vector<Student> &students,
                        const std::vector<Group> &groups) {
    std::vector<int> deducted_points(students.size());

    // TODO implement the rest

    for (int i = 0; i < (signed)deducted_points.size(); ++i) {
        std::string current_id;
        std::tie(std::ignore, current_id) = students[i];
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
