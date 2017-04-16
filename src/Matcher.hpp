#ifndef MATCHER_HPP
#define MATCHER_HPP

#include <vector>

#include "ArgumentParser.hpp"
#include "Rule.hpp"
#include "Segment.hpp"


struct Match
{
    Action action;
    Rule rule;
    Segment segment;
};

class Matcher
{
public:
    void match(Rule aclRules, Segment segment);

    void print_matches(Segment, Option option) const;

private:
    void print_match(Match match) const;

    std::vector<Match> get_first_match(Segment segment) const;
    std::vector<Match> get_all_matches(Segment segment) const;
    std::vector<Match> get_no_matches(Segment segment) const;

    std::vector<Match> m_matches;
};


#endif /* end of include guard: MATCHER_HPP */
