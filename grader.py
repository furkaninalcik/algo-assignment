from subprocess import Popen, PIPE, call
import sys
import time

grade = 0
times = []

if not len(sys.argv) == 2:
	print( "Give your executable name as command line arg" )
	sys.exit(0)

for k in range(1,11):
	start = time.time()
	p2 = Popen(["./"+sys.argv[1],"Inputs/i"+str(k)+".in"], stdout = PIPE )
	out, _ = p2.communicate()
	end = time.time()
	with open('Your_Outputs/your_o'+str(k)+'.out', 'w') as f: 
		f.write(out.decode("utf-8") )
	q = Popen( ["diff", "Expected_Outputs/o"+str(k)+".out" , "Your_Outputs/your_o"+str(k)+".out"], stdout = PIPE )

	diff, e = q.communicate()
	
	#if diff:
	#	print(diff.decode())
	
	times.append( end-start )
	
	if e:
		print("Error :",e)
	
	if len( diff.decode("utf-8") ) == 0:
		grade += 10
		print( "Phase",k,"was successful !" )
	else:
		print( "Phase",k,"was failed !" )
		
print( str(grade)+"/100" )

i = 0
for row in times:
	i += 1
	print(row)
