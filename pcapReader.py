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

class PacketReader:
	'Class to read pcap file.'
	pktCounter = 0
	srcIP_list = []
	dstIP_list = []
	fullSrcIP_list = []
	fullDstIP_list = []
	timePktDict = {}
	timeFileDict = {}
	fileIpDict = {}
	readPktTimes = []
	pktTimes = []
	pcapFiles = []
	username = ''

	def __init__(self, fileNames, username):
		PacketReader.pcapFiles = fileNames
		PacketReader.username = username
	
	def openFiles(self):
		for i in range(len(PacketReader.pcapFiles)):
			self.parseFile(PacketReader.pcapFiles[i]);
			os.remove(PacketReader.pcapFiles[i])
		return

	def parseFile(self, filename):
		f = open(filename)
		print filename
		pcap = PcapReader(filename)
		udpCount = 0
		tcpCount = 0
		icmpCount = 0
		arpCount = 0
		username = getpass.getuser()
		print "username = ", PacketReader.username
		pcapFileIndex = filename.rfind(PacketReader.username)
		pcapFileIndex = pcapFileIndex + 30 + len(PacketReader.username)
		print "INDEX  =", pcapFileIndex
#		tcpDPorts = []
#		tcpSPorts = []
#		tcpData = []
#		tcpSeqNos = []

		for p in pcap:

			pkt = p.payload
			if IP in pkt:
				ip_src = pkt[IP].src
				ip_dst = pkt[IP].dst
				seqNo = pkt[IP].id
				print str(ip_src)
				print str(ip_dst)
				print str(seqNo)

		f.close()
		return

	def printSrcIPAddrs(self):
		print PacketReader.srcIP_list
		return

	def printDstIPAddrs(self):
		print PacketReader.dstIP_list
		return

#This function calculates the time it takes each packet to travel from host to switch, switch to switch and switch to host.
#It also adds a full path in the form of a full source IP list and a full destination IP list. These lists contain the source host
# and destination host IP addresses but also the dummy IP addresses of the switches inbetween.
	def calculateTimes(self):
		j = 0
		packets = []
		times = []
		files = []
		numberNodes = len(PacketReader.pcapFiles)
		numberTimes = len(PacketReader.readPktTimes)
		hostIPCount = 0

		while len(PacketReader.readPktTimes) > 0:
			minimum = min(PacketReader.readPktTimes)
			minPktId = PacketReader.timePktDict[minimum]
			del PacketReader.timePktDict[minimum]

			packets.append(minPktId)
			times.append(minimum)
			filename = PacketReader.timeFileDict[minimum]
			del PacketReader.timeFileDict[minimum]
			files.append(filename)

			del PacketReader.readPktTimes[PacketReader.readPktTimes.index(minimum)]

			#get all other instances of that packet.
			valueKeyTupleList = PacketReader.timePktDict.items()
			for item in valueKeyTupleList:
				if item[1] == minPktId:
					print item
					time = item[0]
					times.append(time)
					#filename = PacketReader.timeFileDict[time]
					#files.append(filename)
					del PacketReader.timePktDict[time]
					#del PacketReader.timeFileDict[time]
					del PacketReader.readPktTimes[PacketReader.readPktTimes.index(time)]

			print "BEFORE SORT -------- ", times
			#sort list of times in ascending order
			times = sorted(times, key = float)
			print "AFTER SORT -------- ", times

			for i in range(1, len(times)):
				filename = PacketReader.timeFileDict[times[i]]
				files.append(filename)
				del PacketReader.timeFileDict[times[i]]

			for j in range(len(times) - 1):
				time = (float(times[j+1]) - float(times[j]))
#				print "TIME: ", time, " = ", times[j+1], " - ", times[j]
				PacketReader.pktTimes.append(time)
				print files
				print times
				srcIp = PacketReader.fileIpDict[files[j]]
				PacketReader.fullSrcIP_list.append(srcIp)

			for k in range(1, len(files)):
				print files
				dstIp = PacketReader.fileIpDict[files[k]]
				PacketReader.fullDstIP_list.append(dstIp)

			packets = []
			times = []
			files = []



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
