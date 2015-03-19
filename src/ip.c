#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "ip.h"


static error_t
copy_uint8_ip(void *value, long castedValue){
    error_t status = SUCCESS;

    if (castedValue > UCHAR_MAX || castedValue < 0){
        status |= ERR_GENERIC;
    }
    uint8_t *destination = (uint8_t*) value;
    *destination = (uint8_t) castedValue;

    return status;
}

static error_t
copy_uint16_ip(void *value, long castedValue){
    error_t status = SUCCESS;

    if (castedValue > USHRT_MAX || castedValue < 0){
        status |= ERR_GENERIC;
    }
    uint16_t *destination = (uint16_t*) value;
    *destination = (uint16_t)castedValue;

    return status;
}

static error_t
parse_int_ip(void *value, const char *string, error_t (*copy)(void*, long)){
    error_t status = SUCCESS;
    char *temp;
    long castedValue;

    castedValue = strtol(string, &temp, 10);
    status |= copy(value, castedValue);

    if (temp == string || *temp != '\0'){
       status |= ERR_GENERIC;
    }
    return status;
}

error_t
parse_address_ip(union ipAdr *newAddress, const char *rawIp){
    error_t status = SUCCESS;
    int i;
    char *token[4];
    char buff[IPSIZE];
    strncpy(buff, rawIp, IPSIZE);
    buff[IPSIZE-1] = '\0';

    for(i = 0; i < 4; i++){ //initialize tokens (no NULL-Ptr!)
        token[i] = "";
    }

    token[0] = strtok(buff, ".");
    for(i = 1; i < 4 && token[i-1] != NULL; i++){
        token[i] = strtok(NULL, ".");
    }
    if (token[i-1] == NULL){
        token[i-1] = ""; //no NULL-Ptr!
    }

    for(i = 0; i < 4; i++){
        status |= parse_int_ip(&newAddress->byte[i], token[i], copy_uint8_ip);
    }

    return status;
}

static error_t
transform_port_ip(union ipPrt *newPort, const char *rawPort){
    error_t status = SUCCESS;

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
        status |= ERR_GENERIC;
    }

    return status;
}

error_t
parse_port_ip(union ipPrt *newPort, const char *rawPort){
    error_t status = SUCCESS;
    if (transform_port_ip(newPort, rawPort) != SUCCESS){
        status |= parse_int_ip(&newPort->value, rawPort, copy_uint16_ip);
    }

    return status;
}

error_t
parse_protocol_ip(int *newProtocol, const char *rawProtocol){
    error_t status = SUCCESS;
    if (strncmp(rawProtocol, "tcp", 3) == 0){
       *newProtocol = PROTO_TCP;
    }
    else if(strncmp(rawProtocol, "udp", 3) == 0){
        *newProtocol = PROTO_UDP;
    }
    else if(strncmp(rawProtocol, "esp", 3) == 0){
        *newProtocol = PROTO_ESP;
    }
    else if(strncmp(rawProtocol, "icmp", 4) == 0){
        *newProtocol = PROTO_ICMP;
    }
    else if(strncmp(rawProtocol, "ip", 2) == 0){
        *newProtocol = PROTO_IP;
    }
    else{
        *newProtocol = PROTO_UNKNOWN;
        status |= ERR_GENERIC;
    }

    return status;
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
