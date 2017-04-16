#include "Segment.hpp"

#include <sstream>


void Segment::from_string(const std::string &line)
{
    m_raw = line;

    std::istringstream inbuf(line);

    inbuf >> m_protocol;

    inbuf >> m_sourceAddress;
    inbuf >> m_sourcePort;

    inbuf >> m_destinationAddress;
    inbuf >> m_destinationPort;
}

const std::string& Segment::to_string() const
{
    return m_raw;
}

const Protocol& Segment::protocol() const
{
    return m_protocol;
}

const IpAddress& Segment::sourceAddress() const
{
    return m_sourceAddress;
}

const Port& Segment::sourcePort() const
{
    return m_sourcePort;
}

const IpAddress& Segment::destinationAddress() const
{
    return m_destinationAddress;
}

const Port& Segment::destinationPort() const
{
    return m_destinationPort;
}

