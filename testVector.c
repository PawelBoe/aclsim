#include <stdio.h>
#include "include/vector.h"

int main(){

	struct vector test;
	char *str = "tcp 123.121.123.121 55445 111.222.111.222 54321 011 COMMENT";
	test = parse_vector(str, 2);
	printf("|%d|%s|%u %u %u %u|%u|%u %u %u %u|%u|%s|%s|\n", test.number ,test.protocol, 
	test.srcIp.byte[0], test.srcIp.byte[1], test.srcIp.byte[2], test.srcIp.byte[3], test.srcPrt.value, 
	test.dstIp.byte[0], test.dstIp.byte[1], test.dstIp.byte[2], test.dstIp.byte[3], test.dstPrt.value, 
	test.flags, test.comment);
	return 0;
}
