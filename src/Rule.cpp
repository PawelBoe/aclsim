#include "Rule.hpp"

#include <sstream>


void Rule::from_string(const std::string &line)
{
    m_raw = line;

    std::istringstream inbuf(line);

    // RULE => ACTION PROTOCOL TARGET TARGET FLAGS
    // TARGET => IP (PORT)
    // ACTION => permit | deny
    // PROTOCOL => ip | tcp | udp | esp | icmp
    // IP => any | host NUM.NUM.NUM.NUM | NUM.NUM.NUM.NUM NUM.NUM.NUM.NUM | NETWORK_GROUP
    // PORT => eq NUM | gt NUM | lt NUM | range NUM NUM | SERVICE_GROUP

    m_sourceTarget.portMin = 0;
    m_sourceTarget.portMax = 65535;
    m_destinationTarget.portMin = 0;
    m_destinationTarget.portMax = 65535;

    inbuf >> m_action;
    inbuf >> m_protocol;

    inbuf >> m_sourceTarget;
    inbuf >> m_destinationTarget;
}

const std::string& Rule::to_string() const
{
    return m_raw;
}
#include <iostream>
bool Rule::apply(Segment segment) const
{
    return
        match_protocol(segment.protocol()) &&
        match_sourceAddress(segment.sourceAddress()) &&
        match_destinationAddress(segment.destinationAddress()) &&
        match_sourcePort(segment.sourcePort()) &&
        match_destinationPort(segment.destinationPort());
}

Action Rule::get_action() const
{
    return m_action;
}

bool Rule::match_sourceAddress(const IpAddress &address) const
{
    for (int i = 0; i < 4; i++)
    {
        if (!(address.byte[i] >= m_sourceTarget.addressMin.byte[i]) ||
            !(address.byte[i] <= m_sourceTarget.addressMax.byte[i]))
        {
            return false;
        }
    }

    return true;
}

bool Rule::match_destinationAddress(const IpAddress &address) const
{
    for (int i = 0; i < 4; i++)
    {
        if (!(address.byte[i] >= m_destinationTarget.addressMin.byte[i]) ||
            !(address.byte[i] <= m_destinationTarget.addressMax.byte[i]))
        {
            return false;
        }
    }

    return true;
}


bool Rule::match_sourcePort(const Port &port) const
{
    if (!m_sourceTarget.portNeq)
        return (m_sourceTarget.portMin <= port) && (m_sourceTarget.portMax >= port);
    else
        return !(m_sourceTarget.portMin <= port) || !(m_sourceTarget.portMax >= port);
}

bool Rule::match_destinationPort(const Port &port) const
{
    if (!m_destinationTarget.portNeq)
        return (m_destinationTarget.portMin <= port) && (m_destinationTarget.portMax >= port);
    else
        return !(m_destinationTarget.portMin <= port) || !(m_destinationTarget.portMax >= port);
}

bool Rule::match_protocol(const Protocol &protocol) const
{
    if (m_protocol == Protocol::IP)
        return true;

    return m_protocol == protocol;
}
