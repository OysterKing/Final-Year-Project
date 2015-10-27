#Comhghall McKeating
#xml translator

import sys
from pcapReader import PacketReader

class Translator:
	'Translates packets into xml lines.'
	def __init__(self, srcIP_Addrs, dstIP_Addrs, pktTimes):
		self.srcIP_Addrs = srcIP_Addrs
		self.dstIP_Addrs = dstIP_Addrs
		self.pktTimes = pktTimes

	def convertIP(self, ip): 
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
		j = 0
		with open('test.xml', 'r') as file:
			data = file.readlines()

		entryIndex = len(data)-2
		fbtx = 2
		for i in range (len(self.srcIP_Addrs)):
			fid = self.convertIP(self.srcIP_Addrs[i])
			tid = self.convertIP(self.dstIP_Addrs[i])
			lbtx = str(self.pktTimes[j]/4 + fbtx)
			fbrx = str(self.pktTimes[j]/2 + fbtx)
			lbrx = str(self.pktTimes[j] + fbtx)
			fbtx_str = str(fbtx)
#			need to find out how to time the packets.
			packetLine = '<p fId="' + fid + '" fbTx="' + fbtx_str + '" lbTx="' + lbtx + '" tId="' + tid + '" fbRx="' + fbrx + '" lbRx="' + lbrx + '" />\n'
			fbtx = float(lbrx)
			j+=1

			data[entryIndex] += packetLine
		print data[entryIndex]

		with open('test.xml', 'w') as file:
			file.writelines(data)
		return

#list1 = ["10.0.0.1", "10.0.0.2", "10.0.0.1"]
#list2 = ["10.0.0.2", "10.0.0.1", "10.0.0.2"]
packetReader = PacketReader("iperf.pcap")
packetReader.openFile()
packetReader.calculateTimes()
translator = Translator(packetReader.srcIP_list, packetReader.dstIP_list, packetReader.pktTimes)
#print translator.convertIp("10.0.0.1")
translator.writeToXML()
