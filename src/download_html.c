#include "http_header.h"
#define BUF_SIZE 1024

int download_html(const char* hostname, int socket)
{
	char buffer[BUFSIZ]; 
	char request_template[] = "GET / HTTP/1.1\r\nHost: %s\r\n\r\n";
	char request[BUF_SIZE];
    int request_len; 
	ssize_t nbytes_total, nbytes_last; 

	request_len = snprintf(request, BUF_SIZE, request_template, hostname);
	if(request_len >= BUF_SIZE)
	{
		fprintf(stderr, "request length large: %d\n", request_len);
		return -1; 
	}

	nbytes_total =0;
	while(nbytes_total < request_len)
	{
		nbytes_last = write(socket, request+nbytes_total, request_len - nbytes_total); 
		if(nbytes_last == -1)
		{
			perror("write error");
			return -1; 
		}
		nbytes_total += nbytes_last; 
	}	
	int fd = open("index.html", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if(fd == -1)
	{
		perror("file");
		return -1; 
	}
	/* Read the response. */
	fprintf(stderr, "debug: before first read\n");
	while ((nbytes_total = read(socket, buffer, BUFSIZ)) > 0) {
		fprintf(stderr, "debug: after a read\n");
		write(fd, buffer, nbytes_total); 
	}
	fprintf(stderr, "debug: after last read\n");
	if (nbytes_total == -1) {
		perror("read");
		return -1; 

	}
	close(fd); 
}
