#include "Ip.hpp"

#include <sstream>
#include <unordered_map>
#include <stdexcept>


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

    std::unordered_map<std::string, int> PORTS;

    PORTS["echo"] = 7;
    PORTS["discard"] = 9;
    PORTS["daytime"] = 13;
    PORTS["chargen"] = 19;
    PORTS["ftp-data"] = 20;
    PORTS["sip"] = 5060;
    PORTS["nfs"] = 2049;
    PORTS["ftp"] = 21;
    PORTS["ssh"] = 22;
    PORTS["telnet"] = 23;
    PORTS["smtp"] = 25;
    PORTS["time"] = 37;
    PORTS["nameserver"] = 42;
    PORTS["whois"] = 43;
    PORTS["tacacs"] = 49;
    PORTS["domain"] = 53;
    PORTS["tacacs_ds"] = 65;
    PORTS["bootps"] = 67;
    PORTS["bootpc"] = 68;
    PORTS["tftp"] = 69;
    PORTS["gopher"] = 70;
    PORTS["finger"] = 79;
    PORTS["www"] = 80;
    PORTS["kerberos_sec"] = 88;
    PORTS["hostname"] = 101;
    PORTS["pop2"] = 109;
    PORTS["pop3"] = 110;
    PORTS["sunrpc"] = 111;
    PORTS["ident"] = 113;
    PORTS["nntp"] = 119;
    PORTS["ntp"] = 123;
    PORTS["netbios_ns"] = 137;
    PORTS["netbios_dgm"] = 138;
    PORTS["netbios_ss"] = 139;
    PORTS["imap"] = 143;
    PORTS["snmp"] = 161;
    PORTS["snmptrap"] = 162;
    PORTS["xdmcp"] = 177;
    PORTS["bgp"] = 179;
    PORTS["irc"] = 194;
    PORTS["dnsix"] = 195;
    PORTS["ldap"] = 389;
    PORTS["mobile_ip"] = 434;
    PORTS["mobil_ip_mn"] = 435;
    PORTS["https"] = 443;
    PORTS["snpp"] = 444;
    PORTS["pim_auto_rp"] = 496;
    PORTS["isakmp"] = 500;
    PORTS["biff"] = 512;
    PORTS["exec"] = 512;
    PORTS["login"] = 513;
    PORTS["who"] = 513;
    PORTS["cmd"] = 514;
    PORTS["syslog"] = 514;
    PORTS["lpd"] = 515;
    PORTS["talk"] = 517;
    PORTS["ntalk"] = 518;
    PORTS["rip"] = 520;
    PORTS["timed"] = 525;
    PORTS["uucp"] = 540;
    PORTS["klogin"] = 543;
    PORTS["kshell"] = 544;
    PORTS["dhcp"] = 547;
    PORTS["msdp"] = 639;
    PORTS["ldp"] = 646;
    PORTS["krb_prop"] = 754;
    PORTS["krbupdate"] = 760;
    PORTS["kpasswd"] = 761;
    PORTS["socks"] = 1080;
    PORTS["afs"] = 1483;
    PORTS["radius_old"] = 1645;
    PORTS["pptp"] = 1723;
    PORTS["radius"] = 1812;
    PORTS["radacct"] = 1813;
    PORTS["zephyr_clt"] = 2103;
    PORTS["zephyr_hm"] = 2104;
    PORTS["eklogin"] = 2105;
    PORTS["ekshell"] = 2106;
    PORTS["rkinit"] = 2108;
    PORTS["nfsd"] = 2049;
    PORTS["cvspserver"] = 2401;
    PORTS["non500_isakmp"] = 4500;
    PORTS["aol"] = 5120;
    PORTS["bgp"] = 179;
    PORTS["chargen"] = 19;
    PORTS["cifs"] = 3020;
    PORTS["citrix-ica"] = 1494;
    PORTS["cmd"] = 514;
    PORTS["ctiqbe"] = 2748;
    PORTS["daytime"] = 13;
    PORTS["discard"] = 9;
    PORTS["domain"] = 53;
    PORTS["echo"] = 7;
    PORTS["exec"] = 512;
    PORTS["finger"] = 79;
    PORTS["ftp"] = 21;
    PORTS["ftp-data"] = 20;
    PORTS["gopher"] = 70;
    PORTS["h323"] = 1720;
    PORTS["hostname"] = 101;
    PORTS["http"] = 80;
    PORTS["https"] = 443;
    PORTS["ident"] = 113;
    PORTS["imap4"] = 143;
    PORTS["irc"] = 194;
    PORTS["kerberos"] = 88;
    PORTS["klogin"] = 543;
    PORTS["kshell"] = 544;
    PORTS["ldap"] = 389;
    PORTS["ldaps"] = 636;
    PORTS["login"] = 513;
    PORTS["lotusnotes"] = 1352;
    PORTS["lpd"] = 515;
    PORTS["netbios-ssn"] = 139;
    PORTS["nfs"] = 2049;
    PORTS["nntp"] = 119;
    PORTS["pcanywhere-data"] = 5631;
    PORTS["pim-auto-rp"] = 496;
    PORTS["pop2"] = 109;
    PORTS["pop3"] = 110;
    PORTS["pptp"] = 1723;
    PORTS["rsh"] = 514;
    PORTS["r tsp"] = 554;
    PORTS["sip"] = 5060;
    PORTS["smtp"] = 25;
    PORTS["sqlnet"] = 1522;
    PORTS["ssh"] = 22;
    PORTS["sunrpc"] = 111;
    PORTS["tacacs"] = 49;
    PORTS["talk"] = 517;
    PORTS["telnet"] = 23;
    PORTS["uucp"] = 540;
    PORTS["whois"] = 43;
    PORTS["www"] = 80;

    int result;

    try
    {
        result = PORTS.at(token);
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
