#Comhghall McKeating
#xml translator

import sys
from pcapReader import PacketReader

class Translator:
	'Translates packets into xml lines.'
	hostIDs = []
	switchIDs = []

	def __init__(self, srcIP_Addrs, dstIP_Addrs, pktTimes, ipNodeDict):
		self.srcIP_Addrs = srcIP_Addrs
		self.dstIP_Addrs = dstIP_Addrs
		self.pktTimes = pktTimes
		self.ipNodeDict = ipNodeDict

	def getHostSwitchIDs(self, filename):
		with open(filename, 'r') as file:
			data = file.readlines()

		for i in range (len(data)):
			if data[i].startswith("<nu") and data[i].count('r="255"'):
				print "h.", data[i - 1][10]
				nodeID = int(data[i - 1][10])
				Translator.hostIDs.append(nodeID)

			elif data[i].startswith("<nu") and data[i].count('g="255"'):
				print "s.", data[i -1][10]
				nodeID = int(data[i - 1][10])
				Translator.switchIDs.append(nodeID)

			elif data[i].startswith("<nu") and data[i].count('b="255"'):
				print "r.", data[i -1][10]
				nodeID = int(data[i - 1][10])
				Translator.switchIDs.append(nodeID)

	def convertIP(self, ip): 
		node = self.ipNodeDict[ip]
		nodeIDstring = ""
		if node[0] == 'r':
			nodeIDstring = str(self.switchIDs[0])

		elif node[0] == 's':
			num = int(node[1])
			nodeIDstring = str(self.switchIDs[num - 1])

		elif node[0] == 'h':
			num = int(node[1])
			nodeIDstring = str(self.hostIDs[num - 1])

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
