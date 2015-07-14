#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include <sys/socket.h>  
#include <sys/ioctl.h>  
#include <linux/if.h>  
#include <linux/if_tun.h>  
#include <linux/ip.h>  
#include <linux/icmp.h>  
#include <sys/types.h>  
#include <errno.h>  
#include <net/route.h>
#include <sys/socket.h>
//#include <netpacket/packet.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
#include <linux/if_arp.h>
//int tun_create(ip);
int if_open(char* device){
	struct sockaddr_ll sll;
	struct ifreq ifr;
	int if_fd   =   socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

	int one = 1; 
	setsockopt (if_fd, IPPROTO_IP, IP_HDRINCL, &one, sizeof(one));

	memset(&ifr, 0, sizeof(ifr));
	strcpy(ifr.ifr_name, device);
	ioctl(if_fd, SIOCGIFFLAGS, &ifr);
	ifr.ifr_flags   |=  IFF_PROMISC;
	ioctl(if_fd, SIOCSIFFLAGS, &ifr);

	ioctl(if_fd, SIOCGIFINDEX, &ifr);
	sll.sll_family  =   AF_PACKET;
	sll.sll_ifindex =   ifr.ifr_ifindex;
	sll.sll_protocol    =   htons(ETH_P_ALL);
	bind(if_fd, (struct sockaddr *)&sll, sizeof(sll));
	return if_fd;
}

int main(){
	unsigned char buff[2000];
	int if_fd = if_open("wlp3s0");
	int ret,i;

	//一下三种功能相同
	ret = read(if_fd,buff,2000);
	//ret = recvfrom(if_fd,buff,2000,0,NULL,0);
	//ret = recv(if_fd,buff,2000,0);
	printf("%d:",ret);
	for(i = 0;i < ret;i++)
		printf(" %02x",buff[i]);
	buff[0]++;
	//一下三种功能相同
	write(if_fd,buff,ret);
	//sendto(if_fd,buff,ret,0,NULL, 0);
	//send(if_fd,buff,ret,0);
	return 0;
}
