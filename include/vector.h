#ifndef VECTOR_H
#define VECTOR_H


struct vector{
	int number;
	char *protocol;
	char *srcIp;
	char *srcPrt;
	char *dstIp;
	char *dstPrt;
	char *flags;
	char *comment;
};

struct vector
parse_vector(char*);

#endif
