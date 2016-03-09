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

class PacketReader:
	'Class to read pcap file.'
	pktCounter = 0
	icmpPkts = []
	arpPkts = []
	dhcpPkts = []
	fullSrcIP_list = []
	fullDstIP_list = []
	timeFilePktList = []
	nodeIpDict = {}
	pcapFiles = []
	timestamps = []

	username = ''

	def __init__(self, fileNames, username):
		PacketReader.pcapFiles = fileNames
		PacketReader.username = username
	
	def openFiles(self):
		for i in range(len(PacketReader.pcapFiles)):
			self.parseFile(PacketReader.pcapFiles[i]);
			os.remove(PacketReader.pcapFiles[i])
		PacketReader.calculateTimes(self)
		return

	def parseFile(self, filename):
		f = open(filename)
		print filename
		pcap = PcapReader(filename)
		username = getpass.getuser()
		print "username = ", PacketReader.username
		pcapFileIndex = filename.rfind(PacketReader.username)
		pcapFileIndex = pcapFileIndex + 30 + len(PacketReader.username)
		print "INDEX  =", pcapFileIndex

		if filename[pcapFileIndex] == 'h':
			nodeName = filename[pcapFileIndex:pcapFileIndex + 2]

		elif filename[pcapFileIndex] == 'r' or filename[pcapFileIndex] == 's':
			fileStr = filename[pcapFileIndex:]
			nodeName = fileStr[:7]

		for p in pcap:

			pkt = p.payload
			timestamp = '%.30f' % p.time
			PacketReader.timestamps.append(timestamp)

			if DHCP in pkt:
				pkt.show()
				options = pkt[DHCP].options
				#print "+++++++ ", options, " ++++++", type(options)
				dhcp_msgType = options[0][1]
				print dhcp_msgType, " -----------"
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

				elif filename[pcapFileIndex] == 'r':
					PacketReader.nodeIpDict[nodeName] = options[1][1]

			elif ARP in pkt:
				pkt.show()
				arp_op = pkt[ARP].op
				print arp_op
				arp_psrc = pkt[ARP].psrc
				arp_pdst = pkt[ARP].pdst
				arpPkt = ARP_pkt(operation=arp_op, p_src=arp_psrc, p_dst=arp_pdst, timestamp=timestamp)
				PacketReader.arpPkts.append(arpPkt)
				pktTuple = (timestamp, nodeName, arpPkt)
				PacketReader.timeFilePktList.append(pktTuple)

			elif ICMP in pkt:
				pkt.show()
				icmp_src = pkt[IP].src
				icmp_dst = pkt[IP].dst
				icmp_seqNo = pkt[IP].id
				icmp_type = pkt[ICMP].type
				icmpPkt = ICMP_pkt(p_type=icmp_type, ip_src=icmp_src, ip_dst=icmp_dst, p_id=icmp_seqNo, icmp_type=icmp_type, timestamp=timestamp)
				pktTuple = (timestamp, nodeName, icmpPkt)
				PacketReader.timeFilePktList.append(pktTuple)

		if filename[pcapFileIndex] == 'h':
			nodeName = filename[pcapFileIndex:pcapFileIndex + 2]

		elif filename[pcapFileIndex] == 'r' or filename[pcapFileIndex] == 's':
			fileStr = filename[pcapFileIndex:]
			nodeName = fileStr[:7]

		f.close()
		return

	def calculateTimes(self):
		sortedTupleList = sorted(PacketReader.timeFilePktList)
		for i in range(len(sortedTupleList)):
			if sortedTupleList[i][2].getPktType() == "ARP":
				if sortedTupleList[i][2].getOp() == 1:
					arp_operation = "who-has"

				elif sortedTupleList[i][2].getOp() == 2:
					arp_operation = "is-at"

				print "ARP:	", arp_operation, "	", sortedTupleList[i][0], "	", sortedTupleList[i][1]

			elif sortedTupleList[i][2].getPktType() == "ICMP":
				if sortedTupleList[i][2].getIcmp_type() == 0:
					icmpType = "echo-request"
				elif sortedTupleList[i][2].getIcmp_type() == 8:
					icmpType = "echo"

				print "ICMP:	", icmpType, "	", sortedTupleList[i][0], "	", sortedTupleList[i][1]

			elif sortedTupleList[i][2].getPktType() == "DHCP":
				if sortedTupleList[i][2].getMsgType() == 1:
					dhcpMsgType = "discover"
				elif sortedTupleList[i][2].getMsgType() == 2:
					dhcpMsgType = "offer"
				elif sortedTupleList[i][2].getMsgType() == 3:
					dhcpMsgType = "request"
				elif sortedTupleList[i][2].getMsgType == 5:
					dhcpMsgType = "ack"

				print "DHCP:	", dhcpMsgType, "	", sortedTupleList[i][0], "	", sortedTupleList[i][1]

	def printTimes(self):
		for i in range (len(PacketReader.pktTimes)):
			print PacketReader.pktTimes[i], " (", PacketReader.srcIP_list[i], " -> ", PacketReader.dstIP_list[i], ")"
		return

	def getPktTimes(self):
		return PacketReader.pktTimes

	def getFullSrcIPList(self):
		return PacketReader.fullSrcIP_list

	def getFullDstIPList(self):
		return PacketReader.fullDstIP_list

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
