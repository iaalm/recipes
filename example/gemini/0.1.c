//  use to transport IP packet tranparently
/*
 * Copyright (c) 2014 SerComm Corporation.
 * All Rights Reserved.
 * SerComm Corporation reserves the right to make changes to this document
 * without notice.
 * SerComm Corporation makes no warranty, representation or guarantee
 * regarding the suitability of its products for any particular purpose. SerComm
 * Corporation assumes no liability arising out of the application or use of any
 * product or circuit. SerComm Corporation specifically disclaims any and all
 * liability, including without limitation consequential or incidental damages;
 * neither does it convey any license under its patent rights, nor the rights of
 * others.
 * Partners of Sercomm have rights to read and change this document before
 * Project submission.
 */

#include <stdio.h>
#include <stdio.h>  
#include <string.h>
#include <string.h>  
#include <sys/epoll.h>
#include <sys/ioctl.h>  
#include <sys/socket.h>
#include <sys/socket.h>  
#include <sys/types.h>  
#include <unistd.h>
#include <errno.h>  
#include <fcntl.h>
#include <linux/icmp.h>  
#include <linux/if.h>  
#include <linux/if_arp.h>
#include <linux/if_ether.h>
#include <linux/if_packet.h>
#include <linux/if_tun.h>  
#include <linux/ip.h>  
#include <net/route.h>


#define MAC_HEAD	14
#define MAX_IF		10
#define MAX_BUFF	2000

typedef unsigned char mac_addr[6];

mac_addr SOURCE_MAC,GATEWAY_MAC;

int interface_up(char *interface_name)  
{  
	int s;  

	if((s = socket(PF_INET,SOCK_STREAM,0)) < 0)  
	{  
		printf("Error create socket :%m\n", errno);  
		return -1;  
	}  

	struct ifreq ifr;  
	strcpy(ifr.ifr_name,interface_name);  

	short flag;  
	flag = IFF_UP;  
	if(ioctl(s, SIOCGIFFLAGS, &ifr) < 0)  
	{  
		printf("Error up %s :%m\n",interface_name, errno);  
		return -1;  
	}  

	ifr.ifr_ifru.ifru_flags |= flag;  

	if(ioctl(s, SIOCSIFFLAGS, &ifr) < 0)  
	{  
		printf("Error up %s :%m\n",interface_name, errno);  
		return -1;  
	}  

	return 0;  

}  

int set_ipaddr(char *interface_name, char *ip)  
{  
	int s;  

	if((s = socket(PF_INET, SOCK_STREAM, 0)) < 0)  
	{  
		printf("Error up %s :%m\n",interface_name, errno);  
		return -1;  
	}  

	struct ifreq ifr;  
	strcpy(ifr.ifr_name, interface_name);  

	struct sockaddr_in addr;  
	bzero(&addr, sizeof(struct sockaddr_in));  
	addr.sin_family = PF_INET;  
	inet_aton(ip, &addr.sin_addr);  

	memcpy(&ifr.ifr_ifru.ifru_addr, &addr, sizeof(struct sockaddr_in));  

	if(ioctl(s, SIOCSIFADDR, &ifr) < 0)  
	{  
		printf("Error set %s ip :%m\n",interface_name, errno);  
		return -1;  
	}  

	return 0;  
}  

int tun_create(char *dev, int flags)  
{  
	struct ifreq ifr;  
	int fd, err;  

	if ((fd = open("/dev/net/tun", O_RDWR)) < 0)  
	{  
		printf("Error :%m\n", errno);  
		return -1;  
	}  

	memset(&ifr, 0, sizeof(ifr));  
	ifr.ifr_flags |= flags;  

	if (*dev != '\0')  
	{  
		strncpy(ifr.ifr_name, dev, IFNAMSIZ);  
	}  

	if ((err = ioctl(fd, TUNSETIFF, (void *)&ifr)) < 0)   
	{  
		printf("Error :%m\n", errno);  
		close(fd);  
		return -1;  
	}  

	strcpy(dev, ifr.ifr_name);  

	return fd;  
}  

int route_add(char * interface_name)  
{  
	int skfd;  
	struct rtentry rt;  

	struct sockaddr_in dst;  
	struct sockaddr_in gw;  
	struct sockaddr_in genmask;  

	memset(&rt, 0, sizeof(rt));  

	genmask.sin_addr.s_addr = inet_addr("0.0.0.0");  

	bzero(&dst,sizeof(struct sockaddr_in));  
	dst.sin_family = PF_INET;  
	dst.sin_addr.s_addr = inet_addr("0.0.0.0");  

	rt.rt_metric = 0;  
	rt.rt_dst = *(struct sockaddr*) &dst;  
	rt.rt_genmask = *(struct sockaddr*) &genmask;  

	rt.rt_dev = interface_name;  
	rt.rt_flags = RTF_UP | RTF_HOST ;  

	skfd = socket(AF_INET, SOCK_DGRAM, 0);  
	if(ioctl(skfd, SIOCADDRT, &rt) < 0)   
	{  
		printf("Error route add :%m\n", errno);  
		return -1;  
	}  
}
void ip_checksum(struct iphdr* ip){
	unsigned long sum = 0,i;
	unsigned short *j = (short*)ip;
	ip->check = 0;
	for(i = 0;i < ip->ihl * 2;i++)
		sum += *(j + i);
	sum = (sum>>16) + (sum&0xffff);
	sum += (sum>>16);
	ip->check = ~sum;
}
void mac_crc(unsigned char *ptr,unsigned  int len)  
{  
	unsigned int  CRC = 0;  
	unsigned int  i;  

	while(len--){  
		CRC = CRC^ *ptr++;  
		for(i = 0; i < 8; i++){  
			if(CRC & 0x01){  
				CRC = (CRC >> 1 )^ 0x8c;  
			}  
			else{  
				CRC >>= 1;  
			}  
		}                     
	}  
	ptr[len] = CRC >> 24;
	ptr[len+1] = 0xff & (CRC >> 16);
	ptr[len+2] = 0xff & (CRC >> 8);
	ptr[len+3] = 0xff & CRC;
}

int vsock_open(char *ip)
{
	int tun;
	char tun_name[10];
	tun_name[0] = '\0';  
	tun = tun_create(tun_name, IFF_TUN | IFF_NO_PI);  
	if (tun < 0)   
	{  
		return 1;  
	}  
	interface_up(tun_name);
	set_ipaddr(tun_name,ip);
	route_add(tun_name);
	puts(tun_name);
	return tun;
}

int rsock_open(char* device)
{
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

void recv_process(int vsock,int *rsock)
{
	int epfd = epoll_create(MAX_IF),ret;
	unsigned char buff[MAX_BUFF];
	struct epoll_event event;
	event.events = EPOLLIN;
	do
	{
		event.data.fd = *rsock;
		epoll_ctl(epfd,EPOLL_CTL_ADD,*rsock,&event);
	}while(*++rsock);
	while(epoll_wait(epfd,&event,1,-1) != -1)
	{
		if(!(event.events & EPOLLIN))
			perror("epoll_wait");
		ret = read(event.data.fd,buff,MAX_BUFF);
//#define DEBUG
#ifdef DEBUG
		int n;
		printf("recv %d bytes:",ret);
		for(n = 0;n < ret;n++)
			printf("%x ",buff[n]);
		putchar(10);
#endif
		switch((buff[12]<<8)+buff[13]){
			case 0x0800:
				puts("IP/ICMP");
				write(vsock,buff+MAC_HEAD,ret-MAC_HEAD);
				break;
			case 0x0806:
				puts("ARP");
				/*
				 * if not set this program for default gateway,need this for arp resolv
				if(buff[21] == 0x01)
				{
					memcpy(buff+6,buff,6);
					memcpy(buff+6,SOURCE_MAC,6);
					buff[21] = 0x02;
					memcpy(buff+32,buff+22,6);
					memcpy(buff+22,buff+28,4);
					memcpy(buff+28,buff+38,4);
					memcpy(buff+38,buff+22,4);
					memcpy(buff+22,SOURCE_MAC,6);
					write(event.data.fd,buff,ret);
				}
				*/
				break;
			case 0x8864:
				puts("PPPoE");
				break;
			default:
				printf("Unkonw :%x\n",(buff[12]<<8)+buff[13]);
				break;

		}
	}
}

void send_process(int vsock,int *rsock)
{
	int i = 0,ret;
	unsigned char buff[MAX_BUFF];
	while((ret = read(vsock,buff + MAC_HEAD,MAX_BUFF - MAC_HEAD)) != -1)
	{
		memcpy(buff,GATEWAY_MAC,6);
		memcpy(buff + 6,SOURCE_MAC,6);
		buff[12] = 0x08;
		buff[13] = 0x00;
		ret += MAC_HEAD;
		printf("%d:%d\n",i,rsock[i]);
		write(rsock[i],buff,ret);
		if(!rsock[++i])
			i = 0;
	}
}

int main(int argc, const char *argv[])
{
	int vsock	= vsock_open("192.168.1.2");
	int rsock[]	= {rsock_open("wlp3s0"),0};

	SOURCE_MAC[0]	= 0xC0;
	SOURCE_MAC[1]	= 0xF8;
	SOURCE_MAC[2]	= 0xDA;
	SOURCE_MAC[3]	= 0x2F;
	SOURCE_MAC[4]	= 0x38;
	SOURCE_MAC[5]	= 0x13;
	GATEWAY_MAC[0]	= 0x4C;
	GATEWAY_MAC[1]	= 0x1F;
	GATEWAY_MAC[2]	= 0xCC;
	GATEWAY_MAC[3]	= 0xAF;
	GATEWAY_MAC[4]	= 0x11;
	GATEWAY_MAC[5]	= 0xD6;

	int pid		= fork();
	if(pid == -1)
	{
		return -1;
	}
	if(pid == 0)
	{
		recv_process(vsock,rsock);
	}
	else
	{
		send_process(vsock,rsock);
	}
	return 0;
}
