#include "http_header.h"

int socket_setting(const char* hostname)
{
	struct protoent *protoent;
	in_addr_t in_addr;
	int socket_file_descriptor;
	struct hostent *hostent;
	struct sockaddr_in sockaddr_in;
	unsigned short server_port = 80;

	/* Build the socket. */
	protoent = getprotobyname("tcp");
	if (protoent == NULL) {
		perror("getprotobyname");
		exit(EXIT_FAILURE);

	}
	socket_file_descriptor = socket(AF_INET, SOCK_STREAM, protoent->p_proto);
	if (socket_file_descriptor == -1) {
		perror("socket");
		exit(EXIT_FAILURE);

	}

	/* Build the address. */
	hostent = gethostbyname(hostname);
	if (hostent == NULL) {
		fprintf(stderr, "error: gethostbyname(\"%s\")\n", hostname);
		exit(EXIT_FAILURE);

	}
	in_addr = inet_addr(inet_ntoa(*(struct in_addr*)*(hostent->h_addr_list)));
	if (in_addr == (in_addr_t)-1) {
		fprintf(stderr, "error: inet_addr(\"%s\")\n", *(hostent->h_addr_list));
		exit(EXIT_FAILURE);

	}
	sockaddr_in.sin_addr.s_addr = in_addr;
	sockaddr_in.sin_family = AF_INET;
	sockaddr_in.sin_port = htons(server_port);

	/* Actually connect. */
	if (connect(socket_file_descriptor, (struct sockaddr*)&sockaddr_in, sizeof(sockaddr_in)) == -1) {
		perror("connect");
		exit(EXIT_FAILURE);

	}

	download_html(hostname ,socket_file_descriptor); 

	close(socket_file_descriptor);
	exit(EXIT_SUCCESS);
}
