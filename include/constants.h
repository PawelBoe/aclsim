//Copyright (C) Pawel Böning, 2015
#ifndef CONSTANTS_H
#define CONSTANTS_H

//Options
typedef enum options{
    OP_STANDARD = 0,
    OP_HELP = 1,
    OP_ALL = 2,
    OP_NOMATCH = 3,
    OP_VERBOSE = 4,
    OP_FILTER = 5,
    OP_UNKNOWN = -1,
}option_t;

//Buffers
#define BUFSIZE 128
#define VECTORSIZE 128
#define RULESIZE 128
#define IPSIZE 16

//Errorcodes
typedef enum errors{
    SUCCESS = 0,
    ERR_GENERIC = 1,
} error_t;

//Rule actions
#define AC_DENY 0
#define AC_PERMIT 1
#define AC_REMARK 2
#define AC_UNKNOWN -1

//Match states
#define ST_DENY 0
#define ST_PERMIT 1
#define ST_REMARK 2
#define ST_NOMATCH 3
#define ST_ERROR -1

//Protocols
#define PROTO_IP 0
#define PROTO_TCP 1
#define PROTO_UDP 2
#define PROTO_ESP 3
#define PROTO_ICMP 4
#define PROTO_UNKNOWN -1

//Ports
#define PORT_ECHO 7                /** echo */
#define PORT_DISCARD 9             /** discard */
#define PORT_DAYTIME 13            /** daytime */
#define PORT_CHARGEN 19            /** chargen */
#define PORT_FTP_DATA 20           /** ftp-data */
#define PORT_FTP 21                /** ftp */
#define PORT_SSH 22                /** ssh */
#define PORT_TELNET 23             /** telnet */
#define PORT_SMTP 25               /** smtp */
#define PORT_TIME 37               /** time */
#define PORT_NAMESERVER 42         /** nameserver */
#define PORT_WHOIS 43              /** whois */
#define PORT_TACACS 49             /** tacacs */
#define PORT_DOMAIN 53             /** domain */
#define PORT_TACACS_DS 65          /** tacacs-ds */
#define PORT_BOOTPS 67             /** bootps */
#define PORT_BOOTPC 68             /** bootpc */
#define PORT_TFTP 69               /** tftp */
#define PORT_GOPHER 70             /** gopher */
#define PORT_FINGER 79             /** finger */
#define PORT_WWW 80                /** www */
#define PORT_KERBEROS_SEC 88       /** kerberos-sec */
#define PORT_HOSTNAME 101          /** hostname */
#define PORT_POP2 109              /** pop2 */
#define PORT_POP3 110              /** pop3 */
#define PORT_SUNRPC 111            /** sunrpc */
#define PORT_IDENT 113             /** ident */
#define PORT_NNTP 119              /** nntp */
#define PORT_NTP 123               /** ntp */
#define PORT_NETBIOS_NS 137        /** netbios-ns */
#define PORT_NETBIOS_DGM 138       /** netbios-dgm */
#define PORT_NETBIOS_SS 139        /** netbios-ss */
#define PORT_IMAP 143              /** imap */
#define PORT_SNMP 161              /** snmp */
#define PORT_SNMPTRAP 162          /** snmptrap */
#define PORT_XDMCP 177             /** xdmcp */
#define PORT_BGP 179               /** bgp */
#define PORT_IRC 194               /** irc */
#define PORT_DNSIX 195             /** dnsix */
#define PORT_LDAP 389              /** ldap */
#define PORT_MOBILE_IP 434         /** mobile-ip */
#define PORT_MOBIL_IP_MN 435       /** mobilip-mn */
#define PORT_HTTPS 443             /** https */
#define PORT_SNPP 444              /** snpp */
#define PORT_PIM_AUTO_RP 496       /** pim-auto-rp */
#define PORT_ISAKMP 500            /** isakmp */
#define PORT_BIFF 512              /** biff */
#define PORT_EXEC 512              /** exec */
#define PORT_LOGIN 513             /** login */
#define PORT_WHO 513               /** who */
#define PORT_CMD 514               /** cmd */
#define PORT_SYSLOG 514            /** syslog */
#define PORT_LPD 515               /** lpd */
#define PORT_TALK 517              /** talk */
#define PORT_NTALK 518             /** ntalk */
#define PORT_RIP 520               /** rip */
#define PORT_TIMED 525             /** timed */
#define PORT_UUCP 540              /** uucp */
#define PORT_KLOGIN 543            /** klogin */
#define PORT_KSHELL 544            /** kshell */
#define PORT_DHCP 547              /** dhcp */
#define PORT_MSDP 639              /** msdp */
#define PORT_LDP 646               /** ldp */
#define PORT_KRB_PROP 754          /** krb-prop */
#define PORT_KRBUPDATE 760         /** krbupdate */
#define PORT_KPASSWD 761           /** kpasswd */
#define PORT_SOCKS 1080            /** socks */
#define PORT_AFS 1483              /** afs */
#define PORT_RADIUS_OLD 1645       /** radius-old */
#define PORT_PPTP 1723             /** pptp */
#define PORT_RADIUS 1812           /** radius */
#define PORT_RADACCT 1813          /** radacct */
#define PORT_ZEPHYR_CLT 2103       /** zephyr-clt */
#define PORT_ZEPHYR_HM 2104        /** zephyr-hm */
#define PORT_EKLOGIN 2105          /** eklogin */
#define PORT_EKSHELL 2106          /** ekshell */
#define PORT_RKINIT 2108           /** rkinit */
#define PORT_NFSD 2049             /** nfsd */
#define PORT_CVSPSERVER 2401       /** cvspserver */
#define PORT_NON500_ISAKMP 4500    /** non500-isakmp */
#define PORT_UNKNOWN -1
#endif
