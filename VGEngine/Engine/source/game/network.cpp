#include "engine\game\network.h"
#include "engine\utility\logger.h"

network::network()
{
#ifdef OS_ANDROID


	int sockfd, sendbytes;
	char buf[BUFLEN];
	struct hostent *host;
	struct sockaddr_in serv_addr;

	if ((host = gethostbyname("127.0.0.1")) == NULL)
	{
		Log("network", "gethostbyname failed", 0);
		exit(1);
	}

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		Log("network", "socket failed", 0);
		exit(1);
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERVPORT);
	serv_addr.sin_addr = *((struct in_addr *)host->h_addr);
	bzero(&(serv_addr.sin_zero), 8);

	// Connect
	if (connect(sockfd, (struct sockaddr *)&serv_addr, \
		sizeof(struct sockaddr)) == -1)
	{
		Log("network", "connect failed", 0);
		exit(1);
	}

	if ((sendbytes = send(sockfd, "test", 4, 0)) == -1)
	{
		Log("network", "send failed", 0);
		exit(1);
	}

	close(sockfd);
#endif
}


network::~network()
{
}
