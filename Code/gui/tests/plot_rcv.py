import numpy as np
import matplotlib.pyplot as plt
import struct

with open('rcv_data_test.txt') as f:
    lines = f.read().splitlines()
parse1=lines[0:5999]
#parse2=lines[6000:-1]
for i in range (0,len(parse1)):
	parse1[i]=parse1[i].rsplit('\'',1)[0]
	parse1[i]=parse1[i].split('\\x')[0]
	parse1[i]=parse1[i].split('b\'')[1]
	parse1[i]=float(parse1[i])
	print (parse1[i])
	#parse1[i]=parse1[i].decode("utf-8", "strict")

	
#print(len(parse2))

plt.plot(parse1)
plt.show()
