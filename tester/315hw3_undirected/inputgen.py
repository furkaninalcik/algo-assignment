from random import randint

n = randint(10,850)
print( n )
k = int(randint(1,n//10)*2)
print(k)
w1 = randint(0,n-1)
w2 = randint(0,n-1)
print(w1,w2)
for i in range(k):
	print( randint(0,n-1),"", end = '' )
print("")

l = [ [] for i in range(n) ]

for i in range(n):
	for j in range(n):
		l[i].append( (randint(0,750)*( randint(0,10) < 3 ) if not i == j else 0) if i <= j else l[j][i] )
		print( l[i][j],"", end='' )
	print("")

