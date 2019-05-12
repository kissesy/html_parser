#include "http_header.h"

int main(int argc, char** argv)
{
	if(argc != 2)
	{
		printf("use two argument!\n");
		exit(1); 
	}
	socket_setting(argv[1]);
	return 0;
}
