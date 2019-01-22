#include "Ip.hpp"

#include <sstream>
#include <fstream>
#include <unordered_map>
#include <stdexcept>
#include <algorithm>


std::istream& operator>> (std::istream& is, Protocol& protocol)
{
    std::string tmp;
    is >> tmp;
    std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);

    if (tmp == "ip")
        protocol = Protocol::IP;
    else if (tmp == "tcp")
        protocol = Protocol::TCP;
    else if (tmp == "udp")
        protocol = Protocol::UDP;
    else if (tmp == "esp")
        protocol = Protocol::ESP;
    else if (tmp == "icmp")
        protocol = Protocol::ICMP;
    else
        throw std::runtime_error("Unknown protocol: " + tmp);

    return is;
}

std::istream& operator>> (std::istream& is, IpAddress& ipAddress)
{
    char dot;
    int a, b, c, d;

    is >> a;
    is >> dot;
    is >> b;
    is >> dot;
    is >> c;
    is >> dot;
    is >> d;

    if (a > 255 || a < 0)
    {
        throw std::runtime_error("Bad octet number: " + std::to_string(a));
    }
    if (b > 255 || b < 0)
    {
        throw std::runtime_error("Bad octet number: " + std::to_string(b));
    }
    if (c > 255 || c < 0)
    {
        throw std::runtime_error("Bad octet number: " + std::to_string(c));
    }
    if (d > 255 || d < 0)
    {
        throw std::runtime_error("Bad octet number: " + std::to_string(d));
    }

    ipAddress.byte[0] = a;
    ipAddress.byte[1] = b;
    ipAddress.byte[2] = c;
    ipAddress.byte[3] = d;

    return is;
}

std::istream& operator>> (std::istream& is, Action& action)
{
    std::string tmp;
    is >> tmp;
    std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);

    if (tmp == "permit")
        action = Action::PERMIT;
    else if (tmp == "deny")
        action = Action::DENY;
    else
        throw std::runtime_error("Unknown action: " + tmp);

    return is;
}
std::istream& operator>> (std::istream& ss, Target& target)
{
    std::string tmp;
    ss >> tmp;

    if (tmp == "any")
    {
        target.addressMin.byte[0] = 0;
        target.addressMin.byte[1] = 0;
        target.addressMin.byte[2] = 0;
        target.addressMin.byte[3] = 0;

        target.addressMax.byte[0] = 255;
        target.addressMax.byte[1] = 255;
        target.addressMax.byte[2] = 255;
        target.addressMax.byte[3] = 255;
    }
    else if (tmp == "host")
    {
        ss >> target.addressMin;
        target.addressMax = target.addressMin;
    }
    else if (is_ipAddress(tmp))
    {
        std::istringstream ipStream(tmp);
        ipStream >> target.addressMin;
        ss >> target.addressMax;
        transform_wildcard(target.addressMin, target.addressMax);
    }

    auto len = ss.tellg();
    ss >> tmp;

    if (tmp == "eq")
    {
        ss >> tmp;
        target.portMin = parse_port(tmp);
        target.portMax = target.portMin;
        target.portNeq = false;
    }
    else if (tmp == "neq")
    {
        ss >> tmp;
        target.portMin = parse_port(tmp);
        target.portMax = target.portMin;
        target.portNeq = true;
    }
    else if (tmp == "lt")
    {
        ss >> tmp;
        target.portMax = parse_port(tmp);
        target.portMin = 0;
        target.portMax --;
        target.portNeq = false;
    }
    else if (tmp == "gt")
    {
        ss >> tmp;
        target.portMin = parse_port(tmp);
        target.portMax = 65535;
        target.portMin ++;
        target.portNeq = false;
    }
    else if (tmp == "range")
    {
        ss >> tmp;
        target.portMin = parse_port(tmp);
        ss >> tmp;
        target.portMax = parse_port(tmp);
        target.portNeq = false;
    }
    else
    {
        ss.seekg(len);
    }

    return ss;
}

void transform_wildcard(IpAddress& address, IpAddress& wildcard)
{
    for (int i = 0; i < 4; i++)
    {
        address.byte[i] = address.byte[i] & ~ wildcard.byte[i];
    }

    for (int i = 0; i < 4; i++)
    {
        wildcard.byte[i] = address.byte[i] | wildcard.byte[i];
    }
}

bool is_ipAddress(const std::string& token)
{
    std::string tmp (token);
    std::replace( tmp.begin(), tmp.end(), '.', ' ');

    std::istringstream inbuf(tmp);

    int a, b, c, d;

    inbuf >> a >> b >> c >> d;

    if (a > 255 || a < 0)
        return false;
    if (b > 255 || b < 0)
        return false;
    if (c > 255 || c < 0)
        return false;
    if (d > 255 || d < 0)
        return false;

    if (inbuf.fail())
        return false;

    return true;
}

int parse_port(std::string token)
{
    std::transform(token.begin(), token.end(), token.begin(), ::tolower);
    PortParser p("ports.cfg");

    int result;

    try
    {
        result = p.PORTS.at(token);
    }
    catch (std::out_of_range &e)
    {
        std::istringstream ss(token);
        ss >> result;

        if (ss.fail())
            throw std::runtime_error("Unknown port: " + token);
    }

    return result;
}

PortParser::PortParser(std::string port_file)
{
    std::ifstream port_stream(port_file);

    std::string line;

    while (std::getline(port_stream, line))
    {
        try
        {
            std::string delimiter = "=";
            std::string name;
            int number;

            name = line.substr(0, line.find(delimiter));
            number = std::stoi(line.substr(line.find(delimiter)+1, line.length()));

            PORTS[name] = number;
        }
        catch (std::exception &e)
        {
            throw std::runtime_error("Processing " + port_file + " [" + line + "] " + e.what());
        }
    }
    port_stream.close();
}
