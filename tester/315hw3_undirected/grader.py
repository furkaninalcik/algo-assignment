from subprocess import Popen, PIPE, call
import sys

grade = 0

if not len(sys.argv) == 2:
	print( "Give your executable name as command line arg" )
	sys.exit(0)

for k in range(1,11):

	p1 = Popen(["cat", 'Inputs/i'+str(k)+'.in' ], stdout = PIPE)
	p2 = Popen(["./"+sys.argv[1]], stdin = p1.stdout, stdout = PIPE )
	out, _ = p2.communicate()
	with open('Your_Outputs/your_o'+str(k)+'.out', 'w') as f: 
		f.write(out.decode("utf-8") )
	q = Popen( ["diff", "Expected_Outputs/o"+str(k)+".out" , "Your_Outputs/your_o"+str(k)+".out"], stdout = PIPE )

	diff, _ = q.communicate()
	if len( diff.decode("utf-8") ) == 0:
		grade += 10
		print( "Phase",k,"was successful !" )
	else:
		print( "Phase",k,"was failed !" )
		
print( str(grade)+"/100" )
