#! /usr/bin/python3

"""
1 ; ...
2 ; ...
4 ; ...
16 ; ...
"""

output = open("processed_results.txt", "w")

with open("res.txt") as res_f:
	res = res_f.readlines()

result = []
res.remove('\n')
for line in res:
        
	nb_thread, time = line[:].split(";",1)
        
	result.append((int(nb_thread), float(time)))
	
reference_time = result[0][1]
output.write("nb_thread ; speedup ; efficiency\n")
for nb_thread, time in result:
	speed_up = time/reference_time
	efficiency = speed_up/nb_thread
	output.write("{} ; {} ; {}\n".format(nb_thread, speed_up, efficiency))
	
output.close()
