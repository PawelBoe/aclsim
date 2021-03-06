#include "RuleParser.hpp"

#include <fstream>
#include <stdexcept>


void RuleParser::from_file(const std::string &aclFile)
{
    std::ifstream aclStream;
    aclStream.open(aclFile);

    if (!aclStream.is_open())
        throw std::runtime_error("Could not open [aclFile]: " + aclFile);

    Rule rule;
    std::string line;

    while (std::getline(aclStream, line))
    {
        if (line.find("remark") != std::string::npos)
        {
            continue; // skip comments
        }
        try
        {
            rule.from_string(line);
            m_rules.push_back(rule);
        }
        catch (std::runtime_error &e)
        {
            throw std::runtime_error("Rule [" + line + "] " + e.what());
        }
    }

    aclStream.close();
}

const std::vector<Rule>& RuleParser::get_rules() const
{
    return m_rules;
}
