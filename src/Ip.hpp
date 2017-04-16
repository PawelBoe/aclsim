#ifndef IP_HPP
#define IP_HPP

#include <cstdint>

#include <sstream>

enum class Action
{
    NO_MATCH,
    PERMIT,
    DENY,
};

typedef uint16_t Port;
typedef unsigned char Octet;

enum class Protocol
{
    IP,
    TCP,
    UDP,
    ESP,
    ICMP,
};

struct IpAddress
{
    Octet byte[4];
};

struct Target
{
    IpAddress addressMin;
    IpAddress addressMax;

    Port portMin;
    Port portMax;

    bool portNeq;
};

std::istream& operator>> (std::istream& is, Protocol& protocol);

std::istream& operator>> (std::istream& is, IpAddress& ipAddress);

std::istream& operator>> (std::istream& is, Action& action);

std::istream& operator>> (std::istream& is, Target& target);

void transform_wildcard(IpAddress& address, IpAddress& wildcard);

bool is_ipAddress(const std::string& token);

int parse_port(std::string token);

#endif /* end of include guard: IP_HPP */
