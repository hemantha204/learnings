// server code for UDP socket programming 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h> 
#define IP_PROTOCOL 0
#define PORT_NO 16060 
#define NET_BUF_SIZE 1029
#define KEY 'H' 
//#define sendrecvflag 0
#define nofile "File Not Found!" 

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
	int sockfd, nBytes;
	struct sockaddr_in addr_con;
	int addrlen = sizeof(addr_con); 
	addr_con.sin_family = AF_INET;
	addr_con.sin_port = htons(PORT_NO); 
	addr_con.sin_addr.s_addr = INADDR_ANY; 
	char net_buf[NET_BUF_SIZE]; 
	char net_buf_1[NET_BUF_SIZE];
	FILE* fp;

	// socket() 
	sockfd = socket(AF_INET, SOCK_DGRAM, IP_PROTOCOL); 

	if (sockfd < 0) 
		printf("\nfile descriptor not received!!\n"); 
	else
		printf("\nfile descriptor %d received\n", sockfd); 

	// bind() 
	if (bind(sockfd, (struct sockaddr*)&addr_con, sizeof(addr_con)) == 0)
		printf("\nSuccessfully binded!\n"); 
	else
		printf("\nBinding Failed!\n");

            // process the data to buffer
    while (1) { 
		printf("\nWaiting for file name...\n"); 

		//Clear the buffer data
		clearBuf(net_buf); 
                 
                // receive file name
		nBytes = recvfrom(sockfd, net_buf, 
						NET_BUF_SIZE, MSG_TRUNC, 
						(struct sockaddr*)&addr_con, &addrlen); 

		fp = fopen(net_buf, "r"); 
		printf("\nFile Name Received: %s\n", net_buf); 
		if (fp == NULL) 
			printf("\nFile open failed!\n"); 
		else
			printf("\nFile Successfully opened!\n");

 		char ch;
		int i=0; 		
		while ( (ch=fgetc(fp)) != EOF )
		{
			//printf("\nData in char =%c\n", ch);
 			net_buf_1[i] = ch;
			i++;
		}
 		// close the file
 		printf("File Sent successfully !!! \n");  
		sendto(sockfd, net_buf_1, NET_BUF_SIZE, MSG_TRUNC,(struct sockaddr*)&addr_con, addrlen);  

			clearBuf(net_buf);
			fclose (fp);
	     }
	return 0; 
} 
