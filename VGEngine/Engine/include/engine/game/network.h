#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#ifdef OS_WINDOWS
# include <winsock2.h>
#endif
#ifdef OS_ANDROID
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/socket.h> 
#include <unistd.h>
#include <sys/types.h>  
#endif

#define SERVPORT 8591
#define BUFLEN 100


class network
{
public:
	network();
	~network();
	

private:
	
	
};

