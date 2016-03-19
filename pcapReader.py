#Comhghall McKeating
#dpkt pcap reader test.

import dpkt
from scapy.all import *
import sys
import socket
import binascii
import datetime
import decimal
import getpass
import os

class ARP_pkt:
	operation = ""
	p_src = ""
	p_dst = ""
	timestamp = 0.0
	def __init__(self, operation, p_src, p_dst, timestamp):
		self.operation = operation
		self.p_src = p_src
		self.p_dst = p_dst
		self.timestamp = timestamp

	def getPktType(self):
		return "ARP"

	def getOp(self):
		return self.operation

	def getP_src(self):
		return self.p_src

	def getP_dst(self):
		return self.p_dst

	def getTimestamp(self):
		return self.timestamp

class ICMP_pkt:
	icmp_type = ""
	ip_src = ""
	ip_dst = ""
	p_id = ""
	p_type = ""
	timestamp = 0.0
	def __init__(self, p_type, ip_src, ip_dst, p_id, icmp_type, timestamp):
		self.p_type = p_type
		self.ip_src = ip_src
		self.ip_dst = ip_dst
		self.p_id = p_id
		self.timestamp = timestamp
		self.icmp_type = icmp_type

	def getPktType(self):
		return "ICMP"

	def getIcmp_type(self):
		return self.icmp_type

	def getTimestamp(self):
		return self.timestamp

	def getP_type(self):
		return self.p_type

	def getIp_src(self):
		return self.ip_src

	def getIp_dst(self):
		return self.ip_dst

	def getP_id(self):
		return self.p_id

class DHCP_pkt:
	msgType = ""
	p_src = ""
	p_dst = ""
	p_id = ""
	timestamp = 0.0
	def __init__(self, msgType, p_src, p_dst, p_id, timestamp):
		self.msgType = msgType
		self.p_src = p_src
		self.p_dst = p_dst
		self.p_id = p_id
		self.timestamp = timestamp

	def getPktType(self):
		return "DHCP"

	def getTimestamp(self):
		return self.timestamp

	def getMsgType(self):
		return self.msgType

	def getP_src(self):
		return self.p_src

	def getP_dst(self):
		return self.p_dst

	def getP_id(self):
		return self.p_id

class TCP_pkt:
	srcPrt = ""
	dstPrt = ""
	srcIp = ""
	dstIp = ""
	timestamp = 0.0

	def __init__(self, srcPrt, dstPrt, srcIp, dstIp, timestamp):
		self.srcPrt = srcPrt
		self.dstPrt = dstPrt
		self.timestamp = timestamp
		self.srcIp = srcIp
		self.dstIp = dstIp

	def getPktType(self):
		return "TCP"

	def getSrcPrt(self):
		return self.srcPrt

	def getDstPrt(self):
		return self.srcPrt

	def getSrcIp(self):
		return self.srcIp

	def getDstIp(self):
		return self.dstIp

class UDP_pkt:
	srcPrt = ""
	dstPrt = ""
	srcIp = ""
	dstIp = ""
	timestamp = 0.0

	def __init__(self, srcPrt, dstPrt, srcIp, dstIp, timestamp):
		self.srcPrt = srcPrt
		self.dstPrt = dstPrt
		self.timestamp = timestamp
		self.srcIp = srcIp
		self.dstIp = dstIp

	def getPktType(self):
		return "UDP"

	def getSrcPrt(self):
		return self.srcPrt

	def getDstPrt(self):
		return self.srcPrt

	def getSrcIp(self):
		return self.srcIp

	def getDstIp(self):
		return self.dstIp

class PacketReader:
	'Class to read pcap file.'
	pktCounter = 0
	arpPkts = []
	icmpPkts = []
	dhcpPkts = []
	fullSrcIP_list = []
	fullDstIP_list = []
	pktTimes = []
	timeFilePktList = []
	ipNodeDict = {}
	nodeIpDict = {}
	pcapFiles = []
	timestamps = []
	linksList = []
	metaInfoList = []
	nodeMacDict = {}

	username = ''

	def __init__(self, fileNames, username):
		PacketReader.pcapFiles = fileNames
		PacketReader.username = username
		with open("/home/comhghall/Final-Year-Project/resources/linkMap.txt", 'r') as file:
			PacketReader.linksList = file.readlines()
			file.close()
	
	def openFiles(self):
		for i in range(len(PacketReader.pcapFiles)):
			self.parseFile(PacketReader.pcapFiles[i]);
			os.remove(PacketReader.pcapFiles[i])
		PacketReader.calculateTimes(self)
		return

	def parseFile(self, filename):
		f = open(filename)
		pcap = PcapReader(filename)
		username = getpass.getuser()
		pcapFileIndex = filename.rfind(PacketReader.username)
		pcapFileIndex = pcapFileIndex + 30 + len(PacketReader.username)

		if filename[pcapFileIndex] == 'h':
			nodeName = filename[pcapFileIndex:pcapFileIndex + 2]
			#By default, host h1 will have ip 10.0.0.1, if a new ip is given to h1 it will overwrite the default ip.
			defaultIp = "10.0.0." + nodeName[1]
			defaultMac = "00:00:00:00:00:0" + nodeName[1]
			PacketReader.nodeIpDict[nodeName] = defaultIp
			PacketReader.ipNodeDict[defaultIp] = nodeName
			PacketReader.nodeMacDict[nodeName] = defaultMac

		elif filename[pcapFileIndex] == 'r':
			fileStr = filename[pcapFileIndex:]
			nodeName = fileStr[:7]

		elif filename[pcapFileIndex] == 's':
			fileStr = filename[pcapFileIndex:]
			nodeName = fileStr[:7]
			switchIp = "--.--.-" + fileStr[1]
			PacketReader.nodeIpDict[nodeName] = switchIp
			PacketReader.ipNodeDict[switchIp] = nodeName

		for p in pcap:

			pkt = p.payload
			timestamp = '%.30f' % p.time
			PacketReader.timestamps.append(timestamp)

			if DHCP in pkt:
				#pkt.show()
				options = pkt[DHCP].options
				dhcp_msgType = options[0][1]
				dhcp_src = pkt[IP].src
				dhcp_dst = pkt[IP].dst
				dhcp_id = pkt[IP].id
				dhcpPkt = DHCP_pkt(msgType=dhcp_msgType, p_src=dhcp_src, p_dst=dhcp_dst, p_id=dhcp_id, timestamp=timestamp)
				pktTuple = (timestamp, nodeName, dhcpPkt)
				PacketReader.timeFilePktList.append(pktTuple)

				#If we're reading a host, we can track the dhcp acknowledge message to see what ip that host gets.
				#Otherwise we wouldn't know what host had what ip; we'd just have the ips.
				if filename[pcapFileIndex] == 'h':
					PacketReader.nodeIpDict[nodeName] = dhcp_dst
					PacketReader.ipNodeDict[dhcp_dst] = nodeName

				elif filename[pcapFileIndex] == 'r':
					PacketReader.nodeIpDict[nodeName] = options[1][1]
					PacketReader.ipNodeDict[options[1][1]] = nodeName

			elif TCP in pkt:
				#pkt.show()
				srcPrt = pkt[TCP].sport
				dstPrt = pkt[TCP].dport
				srcIp = pkt[IP].src
				dstIp = pkt[IP].dst
				tcpPkt = TCP_pkt(srcPrt = srcPrt, dstPrt = dstPrt, srcIp = srcIp, dstIp = dstIp, timestamp = timestamp)
				pktTuple = (timestamp, nodeName, tcpPkt)
				PacketReader.timeFilePktList.append(pktTuple)

			elif UDP in pkt and IP in pkt:
			#	pkt.show()
				srcPrt = pkt[UDP].sport
				dstPrt = pkt[UDP].dport
				srcIp = pkt[IP].src
				dstIp = pkt[IP].dst
				udpPkt = UDP_pkt(srcPrt = srcPrt, dstPrt = dstPrt, srcIp = srcIp, dstIp = dstIp, timestamp = timestamp)
				pktTuple = (timestamp, nodeName, udpPkt)
				PacketReader.timeFilePktList.append(pktTuple)

			elif ARP in pkt:
				#pkt.show()
				arp_op = pkt[ARP].op
				arp_psrc = pkt[ARP].psrc
				arp_pdst = pkt[ARP].pdst
				arpPkt = ARP_pkt(operation=arp_op, p_src=arp_psrc, p_dst=arp_pdst, timestamp=timestamp)
				PacketReader.arpPkts.append(arpPkt)
				pktTuple = (timestamp, nodeName, arpPkt)
				PacketReader.timeFilePktList.append(pktTuple)

			elif ICMP in pkt:
				#pkt.show()
				icmp_src = pkt[IP].src
				icmp_dst = pkt[IP].dst
				icmp_seqNo = pkt[IP].id
				icmp_type = pkt[ICMP].type
				icmpPkt = ICMP_pkt(p_type=icmp_type, ip_src=icmp_src, ip_dst=icmp_dst, p_id=icmp_seqNo, icmp_type=icmp_type, timestamp=timestamp)
				pktTuple = (timestamp, nodeName, icmpPkt)
				PacketReader.timeFilePktList.append(pktTuple)
				if icmp_src[:6] == "10.0.0" and nodeName[0] == 'h':
					if nodeName[1] == icmp_src[7]:
						PacketReader.ipNodeDict[icmp_src] = nodeName
						PacketReader.nodeIpDict[nodeName] = icmp_src

		if filename[pcapFileIndex] == 'h':
			nodeName = filename[pcapFileIndex:pcapFileIndex + 2]

		elif filename[pcapFileIndex] == 'r' or filename[pcapFileIndex] == 's':
			fileStr = filename[pcapFileIndex:]
			nodeName = fileStr[:7]

		f.close()
		return

	def calculateTimes(self):
		sortedTupleList = sorted(PacketReader.timeFilePktList)
		whoHasTupleList = []
		isAtTupleList = []
		echoReqTupleList = []
		echoTupleList = []
		discTupleList = []
		offerTupleList = []
		ackTupleList = []
		reqTupleList = []
		tcpTupleList = []
		udpTupleList = []

		for i in range(len(sortedTupleList)):
			if sortedTupleList[i][2].getPktType() == "ARP":
				if sortedTupleList[i][2].getOp() == 1:
					arp_operation = "who-has"
					pTo = sortedTupleList[i][2].getP_dst()
					pFrom = sortedTupleList[i][2].getP_src()
					pTuple = (sortedTupleList[i][0], arp_operation, sortedTupleList[i][1], pTo, pFrom)
					whoHasTupleList.append(pTuple)
					if i != len(sortedTupleList) - 1:
						if sortedTupleList[i + 1][2].getPktType() != "ARP":
							self.calcTravelTimes(pkts = whoHasTupleList)
							whoHasTupleList = []
						elif sortedTupleList[i + 1][2].getOp() != 1:
							self.calcTravelTimes(pkts = whoHasTupleList)
							whoHasTupleList = []
					elif i == len(sortedTupleList) - 1:
						self.calcTravelTimes(pkts = whoHasTupleList)
						whoHasTupleList = []

				elif sortedTupleList[i][2].getOp() == 2:
					arp_operation = "is-at"
					pTo = sortedTupleList[i][2].getP_dst()
					pFrom = sortedTupleList[i][2].getP_src()
					pTuple = (sortedTupleList[i][0], arp_operation, sortedTupleList[i][1], pTo, pFrom)
					isAtTupleList.append(pTuple)
					if i != len(sortedTupleList) - 1:
						if sortedTupleList[i + 1][2].getPktType() != "ARP":
							self.calcTravelTimes(pkts = isAtTupleList)
							isAtTupleList = []
						elif sortedTupleList[i + 1][2].getOp() != 2:
							self.calcTravelTimes(pkts = isAtTupleList)
							isAtTupleList = []
					elif i == len(sortedTupleList) - 1:
						self.calcTravelTimes(pkts = isAtTupleList)
						isAtTupleList = []

				#print "ARP:	", arp_operation, "	", sortedTupleList[i][0], "	", sortedTupleList[i][1], " ", pFrom, " -> ", pTo

			elif sortedTupleList[i][2].getPktType() == "TCP":
				tcpType = "TCP"
				pTo = sortedTupleList[i][2].getDstIp()
				pFrom = sortedTupleList[i][2].getSrcIp()
				pTuple = (sortedTupleList[i][0], tcpType, sortedTupleList[i][1], pTo, pFrom)
				tcpTupleList.append(pTuple)
				if i != len(sortedTupleList) - 1:
					if sortedTupleList[i + 1][2].getPktType() != "TCP":
						self.calcTravelTimes(pkts = tcpTupleList)
						tcpTupleList = []
					else:
						continue
				elif i == len(sortedTupleList) - 1:
					self.calcTravelTimes(pkts = tcpTupleList)
					tcpTupleList = []

			elif sortedTupleList[i][2].getPktType() == "UDP":
				udpType = "UDP"
				pTo = sortedTupleList[i][2].getDstIp()
				pFrom = sortedTupleList[i][2].getSrcIp()
				pTuple = (sortedTupleList[i][0], udpType, sortedTupleList[i][1], pTo, pFrom)
				udpTupleList.append(pTuple)
				if i != len(sortedTupleList) - 1:
					if sortedTupleList[i + 1][2].getPktType() != "UDP":
						self.calcTravelTimes(pkts = udpTupleList)
						udpTupleList = []
					else:
						continue
				elif i == len(sortedTupleList) - 1:
					self.calcTravelTimes(pkts = udpTupleList)
					udpTupleList = []

			elif sortedTupleList[i][2].getPktType() == "ICMP":
				if sortedTupleList[i][2].getIcmp_type() == 0:
					icmpType = "echo-request"
					pTo = sortedTupleList[i][2].getIp_dst()
					pFrom = sortedTupleList[i][2].getIp_src()
					pTuple = (sortedTupleList[i][0], icmpType, sortedTupleList[i][1], pTo, pFrom)
					echoReqTupleList.append(pTuple)
					if i != len(sortedTupleList) - 1:
						if sortedTupleList[i + 1][2].getPktType() != "ICMP":
							self.calcTravelTimes(pkts = echoReqTupleList)
							echoReqTupleList = []
						elif sortedTupleList[i + 1][2].getIcmp_type() != 0:
							self.calcTravelTimes(pkts = echoReqTupleList)
							echoReqTupleList = []
					elif i == len(sortedTupleList) - 1:
						self.calcTravelTimes(pkts = echoReqTupleList)
						echoReqTupleList = []

				elif sortedTupleList[i][2].getIcmp_type() == 8:
					icmpType = "echo"
					pTo = sortedTupleList[i][2].getIp_dst()
					pFrom = sortedTupleList[i][2].getIp_src()
					pTuple = (sortedTupleList[i][0], icmpType, sortedTupleList[i][1], pTo, pFrom)
					echoTupleList.append(pTuple)
					if i != len(sortedTupleList) - 1:
						if sortedTupleList[i + 1][2].getPktType() != "ICMP":
							self.calcTravelTimes(pkts = echoTupleList)
							echoTupleList = []
						elif sortedTupleList[i + 1][2].getIcmp_type() != 8:
							self.calcTravelTimes(pkts = echoTupleList)
							echoTupleList = []
					elif i == len(sortedTupleList) - 1:
						self.calcTravelTimes(pkts = echoTupleList)
						echoTupleList = []

				#print "ICMP:	", icmpType, "	", sortedTupleList[i][0], "	", sortedTupleList[i][1], " ", pFrom, " -> ", pTo

			elif sortedTupleList[i][2].getPktType() == "DHCP":
				if sortedTupleList[i][2].getMsgType() == 1:
					dhcpMsgType = "discover"
					pTo = sortedTupleList[i][2].getP_dst()
					pFrom = sortedTupleList[i][2].getP_src()
					pTuple = (sortedTupleList[i][0], dhcpMsgType, sortedTupleList[i][1], pTo, pFrom)
					discTupleList.append(pTuple)
					if i != len(sortedTupleList) - 1:
						if sortedTupleList[i + 1][2].getPktType() != "DHCP":
							self.calcTravelTimes(pkts = discTupleList)
							discTupleList = []
						elif sortedTupleList[i + 1][2].getMsgType() != 1:
							self.calcTravelTimes(pkts = discTupleList)
							discTupleList = []
					elif i == len(sortedTupleList) - 1:
						self.calcTravelTimes(pkts = discTupleList)
						discTupleList = []

				elif sortedTupleList[i][2].getMsgType() == 2:
					dhcpMsgType = "offer"
					pTo = sortedTupleList[i][2].getP_dst()
					pFrom = sortedTupleList[i][2].getP_src()
					pTuple = (sortedTupleList[i][0], dhcpMsgType, sortedTupleList[i][1], pTo, pFrom)
					offerTupleList.append(pTuple)
					if i != len(sortedTupleList) - 1:
						if sortedTupleList[i + 1][2].getPktType() != "DHCP":
							self.calcTravelTimes(pkts = offerTupleList)
							offerTupleList = []
						elif sortedTupleList[i + 1][2].getMsgType() != 2:
							self.calcTravelTimes(pkts = offerTupleList)
							offerTupleList = []
					elif i == len(sortedTupleList) - 1:
						self.calcTravelTimes(pkts = offerTupleList)
						offerTupleList = []

				elif sortedTupleList[i][2].getMsgType() == 3:
					dhcpMsgType = "request"
					pTo = sortedTupleList[i][2].getP_dst()
					pFrom = sortedTupleList[i][2].getP_src()
					pTuple = (sortedTupleList[i][0], dhcpMsgType, sortedTupleList[i][1], pTo, pFrom)
					reqTupleList.append(pTuple)
					if i != len(sortedTupleList) - 1:
						if sortedTupleList[i + 1][2].getPktType() != "DHCP":
							self.calcTravelTimes(pkts = reqTupleList)
							reqTupleList = []
						elif sortedTupleList[i + 1][2].getMsgType() != 3:
							self.calcTravelTimes(pkts = reqTupleList)
							reqTupleList = []
					elif i == len(sortedTupleList) - 1:
						self.calcTravelTimes(pkts = reqTupleList)
						reqTupleList = []

				elif sortedTupleList[i][2].getMsgType == 5:
					dhcpMsgType = "ack"
					pTo = sortedTupleList[i][2].getP_dst()
					pFrom = sortedTupleList[i][2].getP_src()
					pTuple = (sortedTupleList[i][0], dhcpMsgType, sortedTupleList[i][1], pTo, pFrom)
					ackTupleList.append(pTuple)
					if i != len(sortedTupleList) - 1:
						if sortedTupleList[i + 1][2].getPktType() != "DHCP":
							self.calcTravelTimes(pkts = ackTupleList)
							ackTupleList = []
						elif sortedTupleList[i + 1][2].getMsgType() != 5:
							self.calcTravelTimes(pkts = ackTupleList)
							ackTupleList = []
					elif i == len(sortedTupleList) - 1:
						self.calcTravelTimes(pkts = ackTupleList)
						ackTupleList = []

				#print "DHCP:	", dhcpMsgType, "	", sortedTupleList[i][0], "	", sortedTupleList[i][1], " ", pFrom, " -> ", pTo

	def calcTravelTimes(self, pkts):
		if pkts == []:
			print "empty"

		#Deal with broadcast packets.
		elif pkts[0][1] == "who-has":
			bcastNode = pkts[0][2]
			bcastSwitch = ""
			bcastSwitch2 = ""
			fullBcast = []
	#		switchTs = []
	#		hostTs = []
			
			links = PacketReader.linksList
			#print links
			for i in range(len(links)):
				if links[i][:2] == bcastNode:
					bcastSwitch = links[i][3:5]
					#del links[i]

			for i in range(len(links)):
				if links[i][3:5] == bcastSwitch and links[i][:2] != bcastNode and links[i][0] == 'h':
					fullBcast.append(bcastNode)
					fullBcast.append(bcastSwitch)
					fullBcast.append(links[i][:2])

			for i in range(len(links)):
				if links[i][:2] == bcastSwitch:
					bcastSwitch2 = links[i][3:5]
					#del links[i]

				elif links[i][3:5] == bcastSwitch and links[i][0] == 's':
					bcastSwitch2 = links[i][:2]

			for i in range(len(links)):
				if links[i][3:5] == bcastSwitch2 and links[i][:2] != bcastSwitch:
					fullBcast.append(bcastNode)
					fullBcast.append(bcastSwitch)
					fullBcast.append(bcastSwitch2)
					fullBcast.append(links[i][:2])

			for i in range(len(fullBcast) - 1):
				for j in range(len(pkts)):
					if pkts[j][2][:2] == fullBcast[i]:
						currentPktIndex = j
				for j in range(len(pkts)):
					if pkts[j][2][:2] == fullBcast[i + 1]:
						nextPktIndex = j

				if fullBcast[i][0] == 'h' and fullBcast[i + 1][0] == 'h':
					continue

				else:
					for j in range(i, len(fullBcast)):
						if fullBcast[j][0] == 'h' and fullBcast[j][:2] != bcastNode:
							toIp = PacketReader.nodeIpDict[fullBcast[j]]
							break

					time1 = pkts[currentPktIndex][0]
					time2 = pkts[nextPktIndex][0]

					if time1 == time2:
						travelTime = 0.0000001

					else:
						travelTime = float(time2) - float(time1)
					#print time2, " - ", time1, " = ", travelTime
				
					PacketReader.pktTimes.append(travelTime)

			for i in range(len(fullBcast) - 1):
				if fullBcast[i][0] == 'h' and fullBcast[i + 1][0] == 's':
					switchId = fullBcast[i + 1] + "-eth0"
					srcIp = PacketReader.nodeIpDict[fullBcast[i]]
					dstIp = PacketReader.nodeIpDict[switchId]
					PacketReader.fullSrcIP_list.append(srcIp)
					PacketReader.fullDstIP_list.append(dstIp)
					metaInfo = "ns3::ArpHeader (request source mac: ..-..-..:..:..:..:..:.. source ipv4: " + pkts[0][4] + " dest mac: ..-..-..:..:..:..:..:.. dest ipv4: " + pkts[0][3] + ")"
					#print metaInfo
					PacketReader.metaInfoList.append(metaInfo)

				elif fullBcast[i][0] == 'h' and fullBcast[i + 1][0] == 'r':
					switchId = fullBcast[i + 1] + "-eth1"
					srcIp = PacketReader.nodeIpDict[fullBcast[i]]
					dstIp = PacketReader.nodeIpDict[switchId]
					PacketReader.fullSrcIP_list.append(srcIp)
					PacketReader.fullDstIP_list.append(dstIp)
					metaInfo = "ns3::ArpHeader (request source mac: ..-..-..:..:..:..:..:.. source ipv4: " + pkts[0][4] + " dest mac: ..-..-..:..:..:..:..:.. dest ipv4: " + pkts[0][3] + ")"
					#print metaInfo
					PacketReader.metaInfoList.append(metaInfo)

				elif fullBcast[i][0] == 's' and fullBcast[i + 1][0] == 's':
					switch2Id = fullBcast[i + 1] + "-eth0"
					switch1Id = fullBcast[i][:2] + "-eth0"
					srcIp = PacketReader.nodeIpDict[switch1Id]
					dstIp = PacketReader.nodeIpDict[switch2Id]
					PacketReader.fullSrcIP_list.append(srcIp)
					PacketReader.fullDstIP_list.append(dstIp)
					metaInfo = "ns3::ArpHeader (request source mac: ..-..-..:..:..:..:..:.. source ipv4: " + pkts[0][4] + " dest mac: ..-..-..:..:..:..:..:.. dest ipv4: " + pkts[0][3] + ")"
					#print metaInfo
					PacketReader.metaInfoList.append(metaInfo)

				elif fullBcast[i][0] == 'r' and fullBcast[i + 1][0] == 'h':
					switchId = fullBcast[i] + "-eth1"
					srcIp = PacketReader.nodeIpDict[switchId]
					dstIp = PacketReader.nodeIpDict[fullBcast[i + 1]]
					PacketReader.fullSrcIP_list.append(srcIp)
					PacketReader.fullDstIP_list.append(dstIp)
					metaInfo = "ns3::ArpHeader (request source mac: ..-..-..:..:..:..:..:.. source ipv4: " + pkts[0][4] + " dest mac: ..-..-..:..:..:..:..:.. dest ipv4: " + pkts[0][3] + ")"
					#print metaInfo
					PacketReader.metaInfoList.append(metaInfo)								

				elif fullBcast[i][0] == 's' and fullBcast[i + 1][0] == 'h':
					switchId = fullBcast[i] + "-eth0"
					srcIp = PacketReader.nodeIpDict[switchId]
					dstIp = PacketReader.nodeIpDict[fullBcast[i + 1]]
					PacketReader.fullSrcIP_list.append(srcIp)
					PacketReader.fullDstIP_list.append(dstIp)
					metaInfo = "ns3::ArpHeader (request source mac: ..-..-..:..:..:..:..:.. source ipv4: " + pkts[0][4] + " dest mac: ..-..-..:..:..:..:..:.. dest ipv4: " + pkts[0][3] + ")"
					#print metaInfo
					PacketReader.metaInfoList.append(metaInfo)				

				elif fullBcast[i][0] == 'h' and fullBcast[i + 1][0] == 'h':
					continue



		else:
			for i in range(len(pkts) - 1):
				
				time1 = pkts[i][0]

				time2 = pkts[i + 1][0]

				if pkts[i][2][0] == 'h' and pkts[i + 1][2][0] == 's':
					switchId = pkts[i + 1][2]
					srcIp = PacketReader.nodeIpDict[pkts[i][2]]
					dstIp = PacketReader.nodeIpDict[switchId]
					PacketReader.fullSrcIP_list.append(srcIp)
					PacketReader.fullDstIP_list.append(dstIp)
					if time1 == time2:
						travelTime = 0.0000001

					else:
						travelTime = float(time2) - float(time1)
					#print time2, " - ", time1, " = ", travelTime
					PacketReader.pktTimes.append(travelTime)
					if pkts[0][1] == "is-at":
						metaInfo = "ns3::ArpHeader (reply source mac: ..-..-..:..:..:..:..:.. source ipv4: " + pkts[0][4] + " dest mac: ..-..-..:..:..:..:..:.. dest ipv4: " + pkts[0][3] + ")"
					elif pkts[0][1] == "echo-request":
						metaInfo = "ns3::Icmpv4Header (type=0, code=0)"
					elif pkts[0][1] == "echo":
						metaInfo = "ns3::Icmpv4Header (type=8, code=0)"
					elif pkts[0][1] == "offer" or pkts[0][1] == "request" or pkts[0][1] == "ack" or pkts[0][1] == "UDP":
						metaInfo = "ns3::UdpHeader (length: 512 " + pkts[0][1] + " &gt; " + pkts[0][1] + ")"
					elif pkts[0][1] == "TCP":
						metaInfo = "ns3::TcpHeader (0000 &gt; 0000 Seq=0 Ack=0 Win=0)"
					#print metaInfo
					PacketReader.metaInfoList.append(metaInfo)

				elif pkts[i][2][0] == 'r' and pkts[i + 1][2][0] == 'r':
					continue

				elif pkts[i][2][0] == 'h' and pkts[i + 1][2][0] == 'r':
					switchId = pkts[i + 1][2][:2] + "-eth1"
					srcIp = PacketReader.nodeIpDict[pkts[i][2]]
					dstIp = PacketReader.nodeIpDict[switchId]
					PacketReader.fullSrcIP_list.append(srcIp)
					PacketReader.fullDstIP_list.append(dstIp)
					if time1 == time2:
						travelTime = 0.0000001

					else:
						travelTime = float(time2) - float(time1)
					#print time2, " - ", time1, " = ", travelTime
					PacketReader.pktTimes.append(travelTime)
					if pkts[0][1] == "is-at":
						metaInfo = "ns3::ArpHeader (reply source mac: ..-..-..:..:..:..:..:.. source ipv4: " + pkts[0][4] + " dest mac: ..-..-..:..:..:..:..:.. dest ipv4: " + pkts[0][3] + ")"
					elif pkts[0][1] == "echo-request":
						metaInfo = "ns3::Icmpv4Header (type=0, code=0)"
					elif pkts[0][1] == "echo":
						metaInfo = "ns3::Icmpv4Header (type=8, code=0)"
					elif pkts[0][1] == "offer" or pkts[0][1] == "request" or pkts[0][1] == "ack" or pkts[0][1] == "UDP":
						metaInfo = "ns3::UdpHeader (length: 512 " + pkts[0][1] + " &gt; " + pkts[0][1] + ")"
					elif pkts[0][1] == "TCP":
						metaInfo = "ns3::TcpHeader (0000 &gt; 0000 Seq=0 Ack=0 Win=0)"
					#print metaInfo
					PacketReader.metaInfoList.append(metaInfo)

				elif pkts[i][2][0] == 's' and pkts[i + 1][2][0] == 's':
					switch2Id = pkts[i + 1][2]
					switch1Id = pkts[i][2]
					srcIp = PacketReader.nodeIpDict[switch1Id]
					dstIp = PacketReader.nodeIpDict[switch2Id]
					PacketReader.fullSrcIP_list.append(srcIp)
					PacketReader.fullDstIP_list.append(dstIp)
					if time1 == time2:
						travelTime = 0.0000001

					else:
						travelTime = float(time2) - float(time1)
					#print time2, " - ", time1, " = ", travelTime
					PacketReader.pktTimes.append(travelTime)
					if pkts[0][1] == "is-at":
						metaInfo = "ns3::ArpHeader (reply source mac: ..-..-..:..:..:..:..:.. source ipv4: " + pkts[0][4] + " dest mac: ..-..-..:..:..:..:..:.. dest ipv4: " + pkts[0][3] + ")"
					elif pkts[0][1] == "echo-request":
						metaInfo = "ns3::Icmpv4Header (type=0, code=0)"
					elif pkts[0][1] == "echo":
						metaInfo = "ns3::Icmpv4Header (type=8, code=0)"
					elif pkts[0][1] == "offer" or pkts[0][1] == "request" or pkts[0][1] == "ack" or pkts[0][1] == "UDP":
						metaInfo = "ns3::UdpHeader (length: 512 " + pkts[0][1] + " &gt; " + pkts[0][1] + ")"
					elif pkts[0][1] == "TCP":
						metaInfo = "ns3::TcpHeader (0000 &gt; 0000 Seq=0 Ack=0 Win=0)"
					#print metaInfo
					PacketReader.metaInfoList.append(metaInfo)

				elif pkts[i][2][0] == 'r' and pkts[i + 1][2][0] == 'h':
					switchId = pkts[i][2][:2] + "-eth1"
					srcIp = PacketReader.nodeIpDict[switchId]
					dstIp = PacketReader.nodeIpDict[pkts[i + 1][2]]
					PacketReader.fullSrcIP_list.append(srcIp)
					PacketReader.fullDstIP_list.append(dstIp)	
					if time1 == time2:
						travelTime = 0.0000001

					else:
						travelTime = float(time2) - float(time1)
					#print time2, " - ", time1, " = ", travelTime
					PacketReader.pktTimes.append(travelTime)
					if pkts[0][1] == "is-at":
						metaInfo = "ns3::ArpHeader (reply source mac: ..-..-..:..:..:..:..:.. source ipv4: " + pkts[0][4] + " dest mac: ..-..-..:..:..:..:..:.. dest ipv4: " + pkts[0][3] + ")"
					elif pkts[0][1] == "echo-request":
						metaInfo = "ns3::Icmpv4Header (type=0, code=0)"
					elif pkts[0][1] == "echo":
						metaInfo = "ns3::Icmpv4Header (type=8, code=0)"
					elif pkts[0][1] == "offer" or pkts[0][1] == "request" or pkts[0][1] == "ack" or pkts[0][1] == "UDP":
						metaInfo = "ns3::UdpHeader (length: 512 " + pkts[0][1] + " &gt; " + pkts[0][1] + ")"
					elif pkts[0][1] == "TCP":
						metaInfo = "ns3::TcpHeader (0000 &gt; 0000 Seq=0 Ack=0 Win=0)"
					#print metaInfo
					PacketReader.metaInfoList.append(metaInfo)

				elif pkts[i][2][0] == 's' and pkts[i + 1][2][0] == 'h':
					switchId = pkts[i][2]
					srcIp = PacketReader.nodeIpDict[switchId]
					dstIp = PacketReader.nodeIpDict[pkts[i + 1][2]]
					PacketReader.fullSrcIP_list.append(srcIp)
					PacketReader.fullDstIP_list.append(dstIp)	
					if time1 == time2:
						travelTime = 0.0000001

					else:
						travelTime = float(time2) - float(time1)
					#print time2, " - ", time1, " = ", travelTime
					PacketReader.pktTimes.append(travelTime)
					if pkts[0][1] == "is-at":
						metaInfo = "ns3::ArpHeader (reply source mac: ..-..-..:..:..:..:..:.. source ipv4: " + pkts[0][4] + " dest mac: ..-..-..:..:..:..:..:.. dest ipv4: " + pkts[0][3] + ")"
					elif pkts[0][1] == "echo-request":
						metaInfo = "ns3::Icmpv4Header (type=0, code=0)"
					elif pkts[0][1] == "echo":
						metaInfo = "ns3::Icmpv4Header (type=8, code=0)"
					elif pkts[0][1] == "offer" or pkts[0][1] == "request" or pkts[0][1] == "ack" or pkts[0][1] == "UDP":
						metaInfo = "ns3::UdpHeader (length: 512 " + pkts[0][1] + " &gt; " + pkts[0][1] + ")"
					elif pkts[0][1] == "TCP":
						metaInfo = "ns3::TcpHeader (0000 &gt; 0000 Seq=0 Ack=0 Win=0)"
					#print metaInfo
					PacketReader.metaInfoList.append(metaInfo)			

				elif pkts[i][2][0] == 'h' and pkts[i + 1][2][0] == 'h':
					continue

	def printTimes(self):
		for i in range (len(PacketReader.pktTimes)):
			print PacketReader.pktTimes[i], " (", PacketReader.srcIP_list[i], " -> ", PacketReader.dstIP_list[i], ")"
		return

	def getTimePktTuples(self):
		return PacketReader.timePktTupleList

	def getPktTimes(self):
		return PacketReader.pktTimes

	def getFullSrcIPList(self):
		return PacketReader.fullSrcIP_list

	def getFullDstIPList(self):
		return PacketReader.fullDstIP_list

	def getIpNodeDict(self):
		return PacketReader.ipNodeDict

	def getMetaInfo(self):
		return PacketReader.metaInfoList

#	def printNumPkts(self):
#		print "Number of packets = ", PacketReader.pktCounter/2
#		return

#reader = PacketReader(["h1.pcap", "h2.pcap", "s1-eth1.pcap"])
#reader.openFiles()
#reader.calculateTimes()
#reader.calculateFullSrcDst()
#reader.printSrcIPAddrs()
#print " "
#reader.printDstIPAddrs()
#print " "
#print reader.getFullSrcIPList()
#print reader.getFullDstIPList()
#reader.printTimes()
#reader.printNumPkts()
