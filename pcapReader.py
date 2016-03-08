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
	def __init__(self, operation, p_src, p_dst, timestamp):
		operation = operation
		p_src = p_src
		p_dst = p_dst
		timestamp = timestamp

	def getOp(self):
		return operation

	def getP_src(self):
		return p_src

	def getP_dst(self):
		return p_dst

	def getTimestamp(self):
		return timestamp

class ICMP_pkt:
	def __init__(self, p_type, ip_src, ip_dst, p_id, icmp_type, timestamp):
		p_type = p_type
		ip_src = ip_src
		ip_dst = ip_dst
		p_id = p_id
		timestamp = timestamp
		icmp_type = icmp_type

	def getIcmp_type(self):
		return icmp_type

	def getTimestamp(self):
		return timestamp

	def getP_type(self):
		return p_type

	def getIp_src(self):
		return ip_src

	def getIp_dst(self):
		return ip_dst

	def getP_id(self):
		return p_id

class DHCP_pkt:
	def __init__(self, msgType, p_src, p_dst, p_id, timestamp):
		msgType = msgType
		p_src = p_src
		p_dst = p_dst
		p_id = p_id
		timestamp = timestamp

	def getTimestamp(self):
		return timestamp

	def getMsgType(self):
		return msgType

	def getP_src(self):
		return p_src

	def getP_dst(self):
		return p_dst

	def getP_id(self):
		return p_id

class PacketReader:
	'Class to read pcap file.'
	pktCounter = 0
	icmpPkts = []
	arpPkts = []
	dhcpPkts = []
	fullSrcIP_list = []
	fullDstIP_list = []
	timePktDict = {}
	timeFileDict = {}
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

		for p in pcap:

			pkt = p.payload
			timestamp = '%.30f' % p.time
			PacketReader.timestamps.append(timestamp)

			if ICMP in pkt:
				pkt.show()
				icmp_src = pkt[IP].src
				icmp_dst = pkt[IP].dst
				icmp_seqNo = pkt[IP].id
				icmp_type = pkt[ICMP].type
				icmpPkt = ICMP_pkt(icmp_type, icmp_src, icmp_dst, icmp_seqNo, icmp_type, timestamp)
				PacketReader.icmpPkts.append(icmpPkt)
				if not PacketReader.timePktDict.has_key(timestamp):
					PacketReader.timePktDict[timestamp] = icmpPkt
				else:
					print "----- KEY COLLISION -----"

				if not PacketReader.timeFileDict.has_key(timestamp):
					PacketReader.timeFileDict[timestamp] = icmpPkt
				else:
					print "----- KEY COLLISION -----"

			elif DHCP in pkt:
				pkt.show()
				options = pkt[DHCP].options
				#print "+++++++ ", options, " ++++++", type(options)
				dhcp_msgType = options[0][1]
				dhcp_src = pkt[IP].src
				dhcp_dst = pkt[IP].dst
				dhcp_id = pkt[IP].id
				dhcpPkt = DHCP_pkt(dhcp_msgType, dhcp_src, dhcp_dst, dhcp_id, timestamp)
				PacketReader.dhcpPkts.append(dhcpPkt)
				if not PacketReader.timePktDict.has_key(timestamp):
					PacketReader.timePktDict[timestamp] = dhcpPkt
				else:
					print "----- KEY COLLISION -----"

				if not PacketReader.timeFileDict.has_key(timestamp):
					PacketReader.timeFileDict[timestamp] = dhcpPkt
				else:
					print "----- KEY COLLISION -----"
				#If we're reading a host, we can track the dhcp acknowledge message to see what ip that host gets.
				#Otherwise we wouldn't know what host had what ip; we'd just have the ips.
				if filename[pcapFileIndex] == 'h':
					nodeName = filename[pcapFileIndex:pcapFileIndex + 2]
					PacketReader.nodeIpDict[nodeName] = dhcp_dst

				elif filename[pcapFileIndex] == 'r':
					fileStr = filename[pcapFileIndex:]
					nodeName = fileStr[:7]
					PacketReader.nodeIpDict[nodeName] = options[1][1]

			elif ARP in pkt:
				pkt.show()
				arp_op = pkt[ARP].op
				arp_psrc = pkt[ARP].psrc
				arp_pdst = pkt[ARP].pdst
				arpPkt = ARP_pkt(arp_op, arp_psrc, arp_pdst, timestamp)
				PacketReader.arpPkts.append(arpPkt)
				if not PacketReader.timePktDict.has_key(timestamp):
					PacketReader.timePktDict[timestamp] = arpPkt
				else:
					print "----- KEY COLLISION -----"

		if filename[pcapFileIndex] == 'h':
			nodeName = filename[pcapFileIndex:pcapFileIndex + 2]

		elif filename[pcapFileIndex] == 'r' or filename[pcapFileIndex] == 's':
			fileStr = filename[pcapFileIndex:]
			nodeName = fileStr[:7]

		if not PacketReader.timeFileDict.has_key(timestamp):
					PacketReader.timeFileDict[timestamp] = nodeName
		else:
			print "----- KEY COLLISION -----"

		print PacketReader.nodeIpDict
		print PacketReader.timestamps

		f.close()
		return

	def calculateTimes(self):
		sortedTimestamps = sorted(PacketReader.timestamps)
		arpTempTime = []
		arpSrcIps = []
		ops = []
		allTimes = []
		for i in range(len(sortedTimestamps)):
			print type(sortedTimestamps[i])
			if not PacketReader.timePktDict.has_key(sortedTimestamps[i]) or not PacketReader.timeFileDict.has_key(sortedTimestamps[i]):
				continue

			pkt = PacketReader.timePktDict[sortedTimestamps[i]]
			nodeName = PacketReader.timeFileDict[sortedTimestamps[i]]
			if type(pkt) == "ARP_pkt":
				if pkt.getOp == "who-has":
					ops.append("who-has")
				elif pkt.getOp == "is-at":
					ops.append("is-at")

			if type(pkt) == "DHCP_pkt":
				if pkt.getMsgType == "request":
					ops.append("request")
				elif pkt.getMsgType == "ack":
					ops.append("ack")
				elif pkt.getMsgType == "offer":
					ops.append("offer")
				elif pkt.getMsgType == "discover":
					ops.append("discover")

			if type(pkt) == "ICMP_pkt":
				if pkt.getIcmp_type == "echo-reply":
					ops.append("echo-reply")
				elif pkt.getIcmp_type == "echo-request":
					ops.append("echo-request")

		print ops

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
