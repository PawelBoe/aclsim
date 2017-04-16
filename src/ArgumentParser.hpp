#ifndef ARGUMENTPARSER_HPP
#define ARGUMENTPARSER_HPP

#include <string>


enum class Option
{
    HELP,
    SHOW_MATCH,
    ALL_MATCH,
    NO_MATCH,
    VERBOSE,
    FILTER,
};

class ArgumentParser
{
public:
    explicit ArgumentParser(int argc, char **argv);

    void print_help() const;

    const std::string& get_aclFile() const;
    const Option get_option() const;

private:
    bool is_option(const std::string &option) const;
    Option parse_option(const std::string &option) const;

    std::string m_programName;
    std::string m_aclFile;
    Option m_option;
};


#endif /* end of include guard: ARGUMENTPARSER_HPP */
