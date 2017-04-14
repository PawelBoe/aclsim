#ifndef RULEPARSER_HPP
#define RULEPARSER_HPP

#include "Rule.hpp"

#include <string>
#include <vector>


class RuleParser
{
public:
    void from_file(const std::string &aclFile);

    const std::vector<Rule>& get_rules() const;

private:
    std::vector<Rule> m_rules;
};


#endif /* end of include guard: RULEPARSER_HPP */
