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
#include <unistd.h>
#include <string.h>  
#include <sys/epoll.h>
#include <sys/ioctl.h>  
#include <sys/types.h>  
#include <sys/socket.h>  
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
#include <netdb.h>


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

int route_change(char * interface_name)  
{  
	int skfd;  
	struct rtentry rt;  

	struct sockaddr_in dst;  
	struct sockaddr_in gw;  
	struct sockaddr_in genmask;  

	memset(&rt, 0, sizeof(rt));  

	genmask.sin_family = PF_INET;  
	genmask.sin_addr.s_addr = inet_addr("0.0.0.0");  

	bzero(&dst,sizeof(struct sockaddr_in));  
	dst.sin_addr.s_addr = inet_addr("0.0.0.0");  

	dst.sin_family = PF_INET;  
	rt.rt_dst = *(struct sockaddr*) &dst;  
	rt.rt_genmask = *(struct sockaddr*) &genmask;  

	//rt.rt_dev = "ppp0";  
	skfd = socket(AF_INET, SOCK_DGRAM, 0);  
	if(ioctl(skfd, SIOCDELRT, &rt) < 0)   
	{  
		printf("Error route del :%m\n", errno);  
		return -1;  
	}  
	rt.rt_metric = 15;  
	rt.rt_flags = RTF_UP;  
	rt.rt_dev = interface_name;  

	if(ioctl(skfd, SIOCADDRT, &rt) < 0)   
	{  
		printf("Error route add :%m\n", errno);  
		return -1;  
	}  
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
	route_change(tun_name);
	puts(tun_name);
	return tun;
}

int rsock_open(char *hostname,int port)
{
	int clientfd;
	struct hostent *hp;
	struct sockaddr_in serveraddr;

	if((clientfd = socket(AF_INET,SOCK_STREAM,0)) < 0)
		return -1;

	if((hp = gethostbyname(hostname)) == NULL)
		return -2;
	bzero((void *)&serveraddr,sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	bcopy((void *)hp->h_addr_list[0],
	      (void *)&serveraddr.sin_addr.s_addr,hp->h_length);
	serveraddr.sin_port = htons((unsigned short)port);
	if(connect(clientfd,(struct sockaddr *) &serveraddr,sizeof(serveraddr)) < 0)
		return -1;
	return clientfd;
}

void recv_process(int vsock,int *rsock)
{
	int epfd = epoll_create(MAX_IF),ret,head,len;
	unsigned char buff[MAX_BUFF];
	struct epoll_event event;
	event.events = EPOLLIN;
	do
	{
		event.data.fd = *rsock;
		epoll_ctl(epfd,EPOLL_CTL_ADD,*rsock,&event);
	}while(*++rsock);
	//use epoll for a lockless mutli-receive
	while(epoll_wait(epfd,&event,1,-1) != -1)
	{
		if(!(event.events & EPOLLIN))
			perror("epoll_wait");
		recv(event.data.fd,&head,2,MSG_WAITALL);
		recv(event.data.fd,&len,2,MSG_WAITALL);
		ret = recv(event.data.fd,buff,len,MSG_WAITALL);
#define DEBUG
#ifdef DEBUG
		int n;
		printf("recv %d bytes:",len);
		for(n = 0;n < len;n++)
			printf("%x ",buff[n]);
		putchar(10);
#endif
#undef DEBUG
		write(vsock,buff,len);
	}
}

void send_process(int vsock,int *rsock)
{
	int i = 0,head,ret,len;
	unsigned char buff[MAX_BUFF];
	while((len = read(vsock,buff,MAX_BUFF)) != -1)
	{
#define DEBUG
#ifdef DEBUG
		int n;
		printf("send %d bytes:",len);
		for(n = 0;n < len;n++)
			printf("%x ",buff[n]);
		putchar(10);
#endif
#undef DEBUG
		head = 0x4A04;		//little ending
		send(rsock[i],&head,2,0);
		send(rsock[i],&len,2,0);
		send(rsock[i],buff,len,0);
		if(!rsock[++i])
			i = 0;
	}
}

int main(int argc, char *argv[])
{
	int vsock	= vsock_open("192.168.1.2");
	int rsock[]	= {rsock_open("192.168.1.2",1234),0};

	int pid		= fork();
	if(pid == -1)
	{
		return -1;
	}
	if(pid == 0)
	{
		argv[0][0] = 'r';
		recv_process(vsock,rsock);
	}
	else
	{
		argv[0][0] = 's';
		send_process(vsock,rsock);
	}
	return 0;
}
