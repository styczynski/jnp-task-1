/**
 * punkty.cc
 *
 * Contributors
 *   @styczynski
 *   @Joald
 *   
 * For description of the problem see README file.
**/
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
#include <map>

//
// Types definitions
//
typedef std::pair<std::string, std::string> Student;
typedef std::vector<Student> Group;
typedef bool LineError;
typedef std::string IndexError;
typedef bool InvalidFileException;
typedef std::vector<std::string> Regexes;

namespace {

// Constants
    const unsigned int INDEX_OF_FIRST_INDEX_NUMBER_IN_GROUP = 15;
    const unsigned int NUMBER_OF_FIRST_INPUT_LINE = 1;
    const Regexes STUDENT_ID_REGEXES = {
            "^([a-z]{2})([0-9]{6})$",
            "^([a-z]{2})(m-[0-9]{4})$"
    };

//
// Error printing functions
//

    inline void print_usage_message(const std::string &program_name) {
        std::cout << "Usage: " << program_name << " file\n";
    }

    inline void print_error_with_file(const std::string &filename) {
        std::cerr << "Error: problem with file " << filename << "\n";
    }

    inline void print_error_in_cin(unsigned int line_number, const std::string &line) {
        std::cerr << "Error in cin, line " << line_number << ": " << line << "\n";
    }
	
	inline void print_error_with_id(unsigned int line_number, const std::string &id) {
        std::cerr << "Error in cin, line " << line_number << ": " << id << "\n";
    }
	
    inline void print_error_in_file(const std::string &filename, unsigned int line_number, const std::string &line) {
        std::cerr << "Error in " << filename << ", line " << line_number << ": " << line << "\n";
    }

//
// Core functions of program
//

    /**
     * For a given tree values - value, min, max of type T.
     * Checks if value is in boundaries defined by min and max.
     *
     * @param[in] value : T
     * @param[in] min   : T
     * @param[in] max   : T
     * @returns If min <= value <= max?
    **/
    template<typename T>
    inline constexpr bool is_in_range(const T &value, const T min, const T max) {
        return value == std::clamp(value, min, max);
    }

    /**
     * Checks if given character is digit (ASCII).
     *
     * @returns logic value
    **/
    inline constexpr bool is_digit(const char &c) {
        return is_in_range(c, '0', '9');
    }

    /**
     * Checks if given character is low case latin letter (ASCII).
     *
     * @returns logic value
    **/
    inline constexpr bool is_low_case_letter(const char &c) {
        return is_in_range(c, 'a', 'z');
    }

    // Should consider removing the above two if we are using regex.

    /**
     * Generates Student object from given student id.
     * If id is invalid then empty optional is returned.
     *
     * For matching valid id forms this function utilizes
     * parameter forms that is a Regexes object.
     *
     * Function tries to match each form and if it fits
     * it extracts #1 and #2 groups.
     *
     * First is letter id and the second numerical part of id.
     *
     * If the Regexes are not passed to the function
     * it utilizes by defult STUDENT_ID_REGEXES.
     *
     * @param[in] id    : student id
     * @param[in] forms : regexes
     * @returns generated Student object
     *
    **/
    std::optional<Student> parse_student(const std::string &id, Regexes forms = STUDENT_ID_REGEXES) {
        // Invalid length
        if (id.size() < 8) return {};

        for (const auto &stringForm : forms) {
            std::regex form(stringForm);
            std::smatch formMatches;

            const bool isValidForm = std::regex_search(id, formMatches, form);
            if (isValidForm) {
                return {make_pair(formMatches[1].str(), formMatches[2].str())};
            }
        }

        // Nothing matches
        // So this is invalid student id
        return {};
    }

    /**
     * Throws LineError: false if condition pred is false.
     * @param[in] : const bool&
     */
    void throw_if_false(const bool &pred) {
        if (!pred) {
            throw false;
        }
    }

    /**
     * Reads given file line by line.
     * Then tries to parse the line using parse_student(string)
     * and finally saves the student data into the collection.
     *
     * The function utilizes loading_error_handler as error handler.
     * The handler is called for each invalid line.
     * It receives the following parameters:
     *   * filename      : string
     *   * line number   : int
     *   * line contents : string
     *
     * @param[in] filename              : const char*
     * @param[in] loading_error_handler : (string, int, string)->void
     * @returns collection containing all valid student entries from file
     *
    **/
    std::vector<Student> read_student_list(const std::string &filename,
                                           const std::function<void(std::string, int,
                                                                    std::string)> &loading_error_handler) {
        std::vector<Student> student_list;
        std::ifstream input_stream(filename);

        std::set<std::string> loaded_ids;

        if (input_stream.is_open()) {
            std::string input_line;
            unsigned int line_number = 1;
            while (std::getline(input_stream, input_line)) {
                const std::optional<Student> student = parse_student(input_line);
                if (student.has_value()) {
                    const Student &student_value = student.value();
                    if (loaded_ids.find(input_line) == loaded_ids.end()) {
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
                line.substr(0, 5) == "grupa" &&
                is_in_range(line[5], '1', '8') &&
                line[6] == '/' &&
                line.substr(7, 7) == "zadanie" &&
                is_in_range(line[14], '1', '6') &&
                line[15] == '/');
    }

    /**
     * Merges a std::pair of two objects of the same type,
     * on the condition that the objects have a valid binary operator+
     * @param[in] : const std::pair<T, T>&
     * @returns pair.first + pair.second
     */
    template<typename T1, typename T2>
    auto merge_pair(const std::pair<T1, T2> &pair) -> decltype(pair.first + pair.second) {
        T1 first;
        T2 second;
        std::tie(first, second) = std::move_if_noexcept(pair);
        return first + second;
    }

    /**
     * Reads student ids from std::string line and inserts correct ones
     * into the group while checking line correctness.
     * @param[in] : const Group&, const std::string&
     */
    void fill_group(Group &group, const std::string &line, int line_number) {
        size_t guardian = INDEX_OF_FIRST_INDEX_NUMBER_IN_GROUP;
        std::vector<std::string> bad_ids;
        do {
            guardian++;
            auto current_id = line.substr(guardian, 8);
            auto newStudent = parse_student(current_id);
            if (!newStudent.has_value()){
				bad_ids.push_back(current_id);
			} else {
				group.push_back(newStudent.value());
			}
            guardian += 8;
        } while (line[guardian] == '+');
        throw_if_false(line[guardian] == '\0');
        throw_if_false(group.size() == 2 || group.size() == 3);
        for (auto& i : bad_ids) {
			print_error_with_id(line_number, i);
		}
    }

    /**
     * Given a Student, the function returns their id.
     *
     * @param[in]
     */
    inline std::string get_student_id(const Student &student) {
        return student.second;
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
        std::set<Student, std::function<bool(const Student &, const Student &)>>
                students(students_vector.begin(), students_vector.end(),
                         [](const Student &left_student, const Student &right_student) {
                             return left_student.first.size() == right_student.first.size() ?
                                    left_student.second.size() > right_student.second.size() :
                                    left_student.first.size() > right_student.first.size();
                         });
        std::string line;
        auto line_number = NUMBER_OF_FIRST_INPUT_LINE;
        std::vector<Group> result;
        while (std::getline(std::cin, line)) {
            try {
                check_basic_group_validity(line);
                Group group;
                fill_group(group, line, line_number);
                Group final_group;
                for (auto it = group.begin(); it != group.end(); ++it) {
                    
                    if (students.find(*it) == students.end() ||
                        std::find(it + 1, group.end(), *it) != group.end() ||
                        std::find(students_vector.begin(), students_vector.end(), *it) == students_vector.end()) {
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
        std::map<const Student *, unsigned long> deducted_points;
        auto search = [&](const Student &student) {
            Group cooperators;
            for (const auto &i : groups) {
                if (std::find(i.begin(), i.end(), student) != i.end()) {
                    for (const auto &j : i) {
                        if (j != student) {
                            cooperators.push_back(j);
                        }
                    }
                }
            }
            auto points = cooperators.size() -
                          std::distance(cooperators.begin(), std::unique(cooperators.begin(), cooperators.end()));
            if (points > 0) {
                deducted_points.insert({&student, points});
            }
        };
        std::for_each(students.begin(), students.end(), search);

        for (auto &i : deducted_points) {
            std::cout << get_student_id(*(i.first)) << ";" << i.second << ";\n";
        }
    }

} // namespace

//
// Application entry point
//

int main(int argc, char **argv) {

    // Invalid number of command line parameters
    if (argc != 2) {
        print_usage_message(argv[0]);
        return 1;
    }

    try {
        auto students = read_student_list(argv[1], print_error_in_file);
        auto groups = read_groups(students);
        print_bad_students(students, groups);
    } catch (const InvalidFileException &e) {
        print_error_with_file(argv[1]);
    }

    return 0;
}
