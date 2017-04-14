#ifndef RULE_HPP
#define RULE_HPP

#include "Segment.hpp"

#include <string>


enum class Action
{
    NO_MATCH,
    PERMIT,
    DENY,
};

class Rule
{
public:
    void from_string(const std::string &line);

    bool apply(Segment segment) const;

    Action get_action() const;

    const std::string& data() const;

private:
    std::string m_data;

/*     int m_number; */
/*     Action m_action; // DENY, PERMIT */
/*     int m_protocol; // IP, TCP, UDP, ICMP .. */

/*     int m_srcAdrStart; */
/*     int m_srcAdrEnd; */

/*     int m_dstAdrStart; */
/*     int m_dstAdrEnd; */

/*     int m_srcPrtStart; */
/*     int m_srcPrtEnd; */
/*     bool m_srcPrtNeq; */

/*     int m_dstPrtStart; */
/*     int m_dstPrtEnd; */
/*     bool m_dstPrtNeq; */
};


#endif /* end of include guard: RULE_HPP */
