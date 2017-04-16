#ifndef SEGMENT_HPP
#define SEGMENT_HPP

#include <string>

#include "Ip.hpp"


class Segment
{
public:
    void from_string(const std::string &line);
    const std::string& to_string() const;

    const Protocol& protocol() const;

    const IpAddress& sourceAddress() const;
    const Port& sourcePort() const;

    const IpAddress& destinationAddress() const;
    const Port& destinationPort() const;

private:
    std::string m_raw;

    Protocol m_protocol;

    IpAddress m_sourceAddress;
    Port m_sourcePort;

    IpAddress m_destinationAddress;
    Port m_destinationPort;
};

#endif /* end of include guard: SEGMENT_HPP */
