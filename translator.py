#Comhghall McKeating
#xml translator

import sys
from pcapReader import PacketReader

class Translator:
	'Translates packets into xml lines.'
	hostCount = 0

	def __init__(self, srcIP_Addrs, dstIP_Addrs, pktTimes):
		self.srcIP_Addrs = srcIP_Addrs
		self.dstIP_Addrs = dstIP_Addrs
		self.pktTimes = pktTimes

	def countNumberHosts(self, filename):
		with open(filename, 'r') as file:
			data = file.readlines()

		for i in range (len(data)):
			print "HEY"
			if data[i].startswith("<nu") and data[i].count('r="255"'):
				Translator.hostCount += 1

	def convertIP(self, ip): 
		dotCount = 0		
		for index in range (len(ip)):
			if dotCount == 3:	#last part of ip address will tell us which node it is.
				addr = ip[index:len(ip)]
				break
			
			elif ip[index] == '.':
				dotCount+=1
		
		if ip.startswith("-"):
			print Translator.hostCount
			nodeID = int(addr) + Translator.hostCount

		else:
			nodeID = int(addr) - 1

		nodeIDstring = str(nodeID)
		return nodeIDstring

	def writeToXML(self, filename): #lets assume that information regarding topology and packet travel time is already in XML file.
		j = 0
		with open(filename, 'r') as file:
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
packetReader = PacketReader(["h1.pcap", "h2.pcap", "s1-eth1.pcap"])
packetReader.openFiles()
packetReader.calculateTimes()
packetReader.calculateFullSrcDst()
translator = Translator(packetReader.fullSrcIP_list, packetReader.fullDstIP_list, packetReader.pktTimes)
translator.countNumberHosts("netanim_topo.xml")
#print translator.convertIp("10.0.0.1")
translator.writeToXML("netanim_topo.xml")
