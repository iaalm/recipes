#!/usr/bin/python3

from math import sqrt

i = 2;
k = 0;
while(i < (1 << 16)):
	j = 2
	l = sqrt(i)
	while(j < l):
		if(i % j == 0):
			k += 1
			break
		j += 1
	i += 1
print (k)
