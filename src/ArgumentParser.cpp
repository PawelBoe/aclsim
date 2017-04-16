#include "ArgumentParser.hpp"

#include <iostream>
#include <stdexcept>


ArgumentParser::ArgumentParser(int argc, char **argv)
{
    m_programName = argv[0];

    if (argc == 2)
    {
        if (is_option(argv[1]))
            m_option = parse_option(argv[1]);
        else
            m_option = parse_option("-s");

        m_aclFile = argv[1];
    }
    else if (argc == 3)
    {
        m_option = parse_option(argv[1]);
        m_aclFile = argv[2];
    }
    else
    {
        print_help();
        throw std::invalid_argument("Wrong unmber of arguments");
    }
}

void ArgumentParser::print_help() const
{
    std::cout
            << std::endl
            << "Simulate CISCO ACL functionality by applying rules to a test vector file." << std::endl
            << "Vectors are read from standard input and can therefore be piped into the" << std::endl
            << "program: " << std::endl
            << std::endl
            << m_programName << " [option] [aclFile] < [vectorFile]" << std::endl
            << std::endl
            << "Possible options are:" << std::endl
            << "-h \t\tshow help" << std::endl
            << "-s (standard)\tshow first match ONLY" << std::endl
            << "-a \t\tshow all matches, not only the first ones" << std::endl
            << "-n \t\tshow not matching rules and corresponding vectors ONLY" << std::endl
            << "-v \t\tshow verbose output (like using both -a and -n)" << std::endl
            << "-f \t\tfilter and print permitted vectors to stdout" << std::endl
            << std::endl;
}

bool ArgumentParser::is_option(const std::string &option) const
{
    return option[0] == '-';
}

Option ArgumentParser::parse_option(const std::string &option) const
{
    if (option.length() != 2 || option[0] != '-')
    {
        print_help();
        throw std::invalid_argument("Wrong option: " + option);
    }

    Option result;

    switch (option[1]) {
        case 'h':
            result = Option::HELP;
            break;
        case 's':
            result = Option::SHOW_MATCH;
            break;
        case 'a':
            result = Option::ALL_MATCH;
            break;
        case 'n':
            result = Option::NO_MATCH;
            break;
        case 'v':
            result = Option::VERBOSE;
            break;
        case 'f':
            result = Option::FILTER;
            break;
        default:
            print_help();
            throw std::invalid_argument("Wrong option: " + option);
            break;
    }

    return result;
}

const std::string& ArgumentParser::get_aclFile() const
{
    return m_aclFile;
}

const Option ArgumentParser::get_option() const
{
    return m_option;
}
