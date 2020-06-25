// client code for UDP socket programming 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h> 
#define IP_PROTOCOL 0
#define IP_ADDRESS "127.0.0.1" // localhost
#define PORT_NO 16060
#define NET_BUF_SIZE 1029

//#define sendrecvflag 0

// function to clear buffer 
void clearBuf(char* b) 
{ 
	int i; 
	for (i = 0; i < NET_BUF_SIZE; i++) 
		b[i] = '\0'; 
}


// driver code 
int main()
{ 
	int sockfd, nBytes,i;
	char ch;
	char net_buf[NET_BUF_SIZE];
	struct sockaddr_in addr_con;
	int addrlen = sizeof(addr_con);
	addr_con.sin_family = AF_INET; 
	addr_con.sin_port = htons(PORT_NO); 
	addr_con.sin_addr.s_addr = inet_addr(IP_ADDRESS);
	FILE* fp;
	
	// creating the socket() 
	sockfd = socket(AF_INET, SOCK_DGRAM, IP_PROTOCOL);
					
	if (sockfd < 0) 
		printf("\nfile descriptor not received!!\n"); 
	else
		printf("\nfile descriptor %d received\n", sockfd);

		//recvFile(sockfd);

	while (1) {

	        printf("\nPlease enter file name to receive:\n"); 
		scanf("%s", net_buf);
		//fp = fopen(net_buf,"w");

		sendto(sockfd, net_buf, NET_BUF_SIZE, MSG_TRUNC, (struct sockaddr*)&addr_con,addrlen);
		printf("\n---------Data Received---------\n");

		//clear the buffer data
		clearBuf(net_buf);

		// receive the data from the socket
		nBytes = recvfrom(sockfd, net_buf, NET_BUF_SIZE, 
							MSG_TRUNC, (struct sockaddr*)&addr_con, 
							&addrlen);
		
		fp=fopen("received.txt","w");
		if( fp == NULL ){
  		printf("Error IN Opening File ");
  			return 0;
 		}

 		fprintf(fp,"%s",net_buf);
		fclose(fp);
		clearBuf(net_buf);
		 printf("File received successfully !! \n");
 		 printf("New File created is received.txt !! \n");

	}
 	return 0;
 
} 
