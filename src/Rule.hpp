#ifndef RULE_HPP
#define RULE_HPP

#include "Segment.hpp"
#include "Ip.hpp"

#include <string>


class Rule
{
public:
    void from_string(const std::string &line);
    const std::string& to_string() const;

    bool apply(Segment segment) const;

    Action get_action() const;

private:
    bool match_sourceAddress(const IpAddress &address) const;
    bool match_destinationAddress(const IpAddress &address) const;

    bool match_sourcePort(const Port &port) const;
    bool match_destinationPort(const Port &port) const;

    bool match_protocol(const Protocol &protocol) const;

    std::string m_raw;

    Action m_action;
    Protocol m_protocol;

    Target m_sourceTarget;
    Target m_destinationTarget;
};


#endif /* end of include guard: RULE_HPP */
