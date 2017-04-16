#include "Matcher.hpp"

#include <iostream>


void Matcher::match(Rule rule, Segment segment)
{
    Match match;

    match.action = Action::NO_MATCH;
    match.rule = rule;
    match.segment = segment;

    if (rule.apply(segment))
        match.action = rule.get_action();

    m_matches.push_back(match);
}

void Matcher::print_matches(Segment segment, Option option) const
{
    if (option == Option::SHOW_MATCH)
    {
        auto matches = get_first_match(segment);

        if (matches.empty())
            return;

        print_match(matches[0]);
    }
    else if (option == Option::ALL_MATCH)
    {
        auto matches = get_all_matches(segment);

        for (auto &m : matches) {
            print_match(m);
        }
    }
    else if (option == Option::NO_MATCH)
    {
        auto noMatches = get_no_matches(segment);

        for (auto &m : noMatches) {
            print_match(m);
        }
    }
    else if (option == Option::VERBOSE)
    {
        auto matches = get_all_matches(segment);

        for (auto &m : matches) {
            print_match(m);
        }

        auto noMatches = get_no_matches(segment);

        for (auto &m : noMatches) {
            print_match(m);
        }
    }
    else if (option == Option::FILTER)
    {
        auto matches = get_first_match(segment);

        if (matches.empty())
            return;

        if (matches[0].action == Action::PERMIT)
            std::cout << matches[0].segment.to_string() << std::endl;
    }
    else
    {
        throw std::runtime_error("Bad option");
    }
}

void Matcher::print_match(Match match) const
{
    switch (match.action) {
        case Action::NO_MATCH:
            std::cout
                << "NO MATCH "
                << "[" << match.rule.to_string() << "]"
                << " => "
                << "[" << match.segment.to_string() << "]"
                << std::endl;
            break;
        default:
            std::cout
                << "MATCH "
                << "[" << match.rule.to_string() << "]"
                << " => "
                << "[" << match.segment.to_string() << "]"
                << std::endl;
            break;
    }
}

std::vector<Match> Matcher::get_first_match(Segment segment) const
{
    std::vector<Match> matches;

    for (auto &m : m_matches) {
        if (m.action != Action::NO_MATCH) {
            matches.push_back(m);
            return matches;
        }
    }

    return matches;
}

std::vector<Match> Matcher::get_all_matches(Segment segment) const
{
    std::vector<Match> matches;

    for (auto &m : m_matches) {
        if (m.action != Action::NO_MATCH) {
            matches.push_back(m);
        }
    }

    return matches;
}

std::vector<Match> Matcher::get_no_matches(Segment segment) const
{
    std::vector<Match> matches;

    for (auto &m : m_matches) {
        if (m.action == Action::NO_MATCH) {
            matches.push_back(m);
        }
    }

    return matches;
}
