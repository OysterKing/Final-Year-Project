#Comhghall McKeating
#xml translator

import sys
from pcapReader import PacketReader

class Translator:
	'Translates packets into xml lines.'
	hostIDs = []
	switchIDs = []

	def __init__(self, srcIP_Addrs, dstIP_Addrs, pktTimes):
		self.srcIP_Addrs = srcIP_Addrs
		self.dstIP_Addrs = dstIP_Addrs
		self.pktTimes = pktTimes

	def getHostSwitchIDs(self, filename):
		with open(filename, 'r') as file:
			data = file.readlines()

		for i in range (len(data)):
			print "HEY"
			if data[i].startswith("<nu") and data[i].count('r="255"'):
				print "h.", data[i - 1][10]
				nodeID = int(data[i - 1][10])
				Translator.hostIDs.append(nodeID)

			elif data[i].startswith("<nu") and data[i].count('g="255"'):
				print "s.", data[i -1][10]
				nodeID = int(data[i - 1][10])
				Translator.switchIDs.append(nodeID)

	def convertIP(self, ip): 
		dotCount = 0		
		for index in range (len(ip)):
			if dotCount == 3:	#last part of ip address will tell us which node it is.
				addr = ip[index:len(ip)]
				break
			
			elif ip[index] == '.':
				dotCount+=1
		
		if ip.startswith("-"):
			nodeID = int(addr)
			nodeIDstring = str(Translator.switchIDs[nodeID])

		#Host ips always are of the form x.x.x.1 to x.x.x.n so we subtract one to get the correct index in the hostIDs list.
		else:
			nodeID = int(addr) - 1
			nodeIDstring = str(Translator.hostIDs[nodeID])

		return nodeIDstring

	def writeToXML(self, filename): #lets assume that information regarding topology and packet travel time is already in XML file.
		j = 0
		with open(filename, 'r') as file:
			data = file.readlines()

		for i in range(len(data)):
			if data[i].count("link") > 0:
				indexOfEnd = data[i].index(">")
				data[i] = data[i][0:indexOfEnd + 1] + "\n"

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

		with open('/home/comhghall/Final-Year-Project/resources/test.xml', 'w') as file:
			file.writelines(data)
		return

#packetReader = PacketReader(["h1.pcap", "h2.pcap", "s1-eth1.pcap"])
#packetReader.openFiles()
#packetReader.calculateTimes()
#packetReader.calculateFullSrcDst()
#translator = Translator(packetReader.getFullSrcIPList, packetReader.getFullDstIPList, packetReader.getPktTimes)
#translator.getHostSwitchIDs("netanim_topo.xml")
#print translator.convertIp("10.0.0.1")
#translator.writeToXML("netanim_topo.xml")
