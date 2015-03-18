#include <stdlib.h>
#include <string.h>
#include "ip.h"


union ipAdr
parse_address_ip(char *rawIp){
    int i;
    char *token[4];
    char buff[IPSIZE];
    strncpy(buff, rawIp, IPSIZE);
    buff[IPSIZE-1] = '\0';
    union ipAdr newAddress;

    token[0] = strtok(buff, ".");
    for(i = 1; i < 4; i++){
        token[i] = strtok(NULL, ".");
    }

    for(i = 0; i < 4; i++){
        newAddress.byte[i] = atoi(token[i]);
    }

    return newAddress;
}

error_t
transform_port_ip(union ipPrt *newPort, char *rawPort){
    error_t transformState = SUCCESS;

    if (strncmp(rawPort, "smtp", 4) == 0){
        newPort->value = PORT_SMTP;
    }
    else if(strncmp(rawPort, "domain", 6) == 0){
        newPort->value = PORT_DOMAIN;
    }
    else if(strncmp(rawPort, "syslog", 6) == 0){
        newPort->value = PORT_SYSLOG;
    }
    else if(strncmp(rawPort, "snmp", 4) == 0){
        newPort->value = PORT_SNMP;
    }
    else if(strncmp(rawPort, "tftp", 4) == 0){
        newPort->value = PORT_TFTP;
    }
    else if(strncmp(rawPort, "netbios-ss", 10) == 0){
        newPort->value = PORT_NETBIOS_SS;
    }
    else if(strncmp(rawPort, "isakmp", 6) == 0){
        newPort->value = PORT_ISAKMP;
    }
    else if(strncmp(rawPort, "non500-isakmp", 13) == 0){
        newPort->value = PORT_NON500_ISAKMP;
    }
    else if(strncmp(rawPort, "bgp", 3) == 0){
        newPort->value = PORT_BGP;
    }
    else if(strncmp(rawPort, "ssh", 3) == 0){
        newPort->value = PORT_SSH;
    }
    else if(strncmp(rawPort, "www", 3) == 0){
        newPort->value = PORT_WWW;
    }
    else if(strncmp(rawPort, "ftp", 3) == 0){
        newPort->value = PORT_FTP;
    }
    else if(strncmp(rawPort, "ftp-data", 8) == 0){
        newPort->value = PORT_FTP_DATA;
    }
    else if(strncmp(rawPort, "telnet", 6) == 0){
        newPort->value = PORT_TELNET;
    }
    else if(strncmp(rawPort, "https", 5) == 0){
        newPort->value = PORT_HTTPS;
    }

    else{
        transformState = ERR_VALUE;
    }

    return transformState;
}

union ipPrt
parse_port_ip(char *rawPort){
    union ipPrt newPort;
    if (transform_port_ip(&newPort, rawPort) != SUCCESS){
        newPort.value = atoi(rawPort);
    }
    return newPort;
}

int
parse_protocol_ip(char *rawProtocol){
    int newProtocol;
    if (strncmp(rawProtocol, "tcp", 3) == 0){
       newProtocol = PROTO_TCP;
    }
    else if(strncmp(rawProtocol, "udp", 3) == 0){
        newProtocol = PROTO_UDP;
    }
    else if(strncmp(rawProtocol, "esp", 3) == 0){
        newProtocol = PROTO_ESP;
    }
    else if(strncmp(rawProtocol, "icmp", 4) == 0){
        newProtocol = PROTO_ICMP;
    }
    else if(strncmp(rawProtocol, "ip", 2) == 0){
        newProtocol = PROTO_IP;
    }
    else{
        newProtocol = PROTO_UNKNOWN;
    }

    return newProtocol;
}

void
transform_wildcard_ip(union ipAdr *address, union ipAdr *wildcard){
    int i;
    union ipAdr tmp;

    for (i = 0; i < 4; i++){
        tmp.byte[i] = address->byte[i] &~ wildcard->byte[i];
    }
    *address = tmp;

    for (i = 0; i < 4; i++){
        tmp.byte[i] = address->byte[i] | wildcard->byte[i];
    }
    *wildcard = tmp;
}
