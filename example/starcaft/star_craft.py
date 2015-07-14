import copy

n = 6
can = {}
worth = {}
def die(n):
	tab = [1] * n
	tab[0] = 0
	while tab != [6] * n:
		c = 0
		while tab[c] == 6:
			tab[c] = 1
			c = c + 1
		tab[c] = tab[c] + 1
		yield tab

def output(attack,defence,ad,dd):
	print("%d+%d attack %d+%d:"%(attack,ad,defence,dd))
	m = min(attack,defence)
	attack = attack + ad
	defence = defence + dd
	total = 6 ** (attack+defence)
	tab = {}
	for i in die(attack):
		i = copy.copy(i)
		i.sort(reverse=True)
		for j in die(defence): 
			j = copy.copy(j)
			j.sort(reverse=True)
			count = [0,0]
			c = 0
			while c < m:
				if i[c] <= j[c]:
					count[0] = count[0] - 1
				else:
					count[1] = count[1] - 1
				c = c + 1
			count = tuple(count)
			if count not in tab:
				tab[count] = 0
			tab[count] = tab[count] + 1

	c = 0
	for i in tab:
		if i[0] >= i[1]:
			c = c + tab[i]/total
	can[(attack-ad,ad,defence-dd,dd)] = c
	print('can:%f'%c)
	c = 0
	for i in tab:
		if i[0] > i[1]:
			c = c + tab[i]/total
	print('worth:%f'%c)
	worth[(attack-ad,ad,defence-dd,dd)] = c
	for i in tab:
		print("\t%d:%d---%f"%(i[0],i[1],tab[i]/total))

if __name__ == '__main__':
	for i in [(0,0),(0,1),(1,0),(1,1)]:
		for a in range(3,0,-1):
			for d in range(2,0,-1):
				output(a,d,i[0],i[1])
	print('can')
	for j in [(2,0),(1,0),(2,1),(1,1)]:
		print("\t\t",end='')
		print(j,end='')
	print('')
	for i in [(3,0),(2,0),(1,0),(3,1),(2,1),(1,1)]:
		print(i,end='\t')
		for j in [(2,0),(1,0),(2,1),(1,1)]:
			print("\t%f"%can[i+j],end='')
		print('')
	print('worth')
	for j in [(2,0),(1,0),(2,1),(1,1)]:
		print("\t\t",end='')
		print(j,end='')
	print('')
	for i in [(3,0),(2,0),(1,0),(3,1),(2,1),(1,1)]:
		print(i,end='\t')
		for j in [(2,0),(1,0),(2,1),(1,1)]:
			print("\t%f"%worth[i+j],end='')
		print('')

