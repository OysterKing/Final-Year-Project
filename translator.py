#Comhghall McKeating
#xml translator

import sys

class Translator:
	'Translates packets into xml lines.'
	def __init__(self, srcIP_Addrs, dstIP_Addrs):
		self.srcIP_Addrs = srcIP_Addrs
		self.dstIP_Addrs = dstIP_Addrs

	def convert(self, ip): 
		dotCount = 0		
		for index in range (len(ip)):
			if dotCount == 3:	#last part of ip address will tell us which node it is.
				addr = ip[index:len(ip)]
				break
			
			elif ip[index] == '.':
				dotCount+=1
		
		nodeID = int(addr) - 1
		nodeIDstring = str(nodeID)
		return nodeIDstring

	def writeToXML(self): #lets assume that information regarding topology and packet travel time is already in XML file.
		with open('test.xml', 'r') as file:
			data = file.readlines()

		entryIndex = len(data)-2

		for i in range (len(self.srcIP_Addrs)):
			fid = self.convert(self.srcIP_Addrs[i])
			tid = self.convert(self.dstIP_Addrs[i])
#			need to find out how to time the packets.
			packetLine = '<p fId="' + fid + '" fbTx="2" lbTx="2.0016864" tId="' + tid + '" fbRx="2.002" lbRx="2.0036864" />\n'
			data[entryIndex] += packetLine
		print data[entryIndex]

		with open('test.xml', 'w') as file:
			file.writelines(data)
		return

list1 = ["10.0.0.1", "10.0.0.2", "10.0.0.1"]
list2 = ["10.0.0.2", "10.0.0.1", "10.0.0.2"]
translator = Translator(list1, list2)
print translator.convert("10.0.0.1")
translator.writeToXML()
