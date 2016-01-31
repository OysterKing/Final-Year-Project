#Comhghall McKeating
#dpkt pcap reader test.

import dpkt
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
		pcap = dpkt.pcap.Reader(f)
		udpCount = 0
		tcpCount = 0
		icmpCount = 0
		arpCount = 0
		username = getpass.getuser()
		print "username = ", PacketReader.username
		pcapFileIndex = filename.rfind(PacketReader.username)
		pcapFileIndex = pcapFileIndex + 1 + len(PacketReader.username)
		print "INDEX  =", pcapFileIndex
#		tcpDPorts = []
#		tcpSPorts = []
#		tcpData = []
#		tcpSeqNos = []

		for ts, buf in pcap:			
			eth = dpkt.ethernet.Ethernet(buf)
			pktData = eth.data
			tcp = pktData.data
			
			if type(tcp) is dpkt.tcp.TCP:
#				tcpDPorts.append(tcp.dport)
#				tcpSPorts.append(tcp.sport)
#				tcpData.append(tcp.data)
#				tcpSeqNos.append(tcp.seq)
				tcpCount+=1

			elif type(tcp) is dpkt.udp.UDP:
#				print "UDP PACKET"
#				udp = tcp
#				print udp.__hdr__
#				print udp.sport
#				print udp.dport
				udpCount+=1

#			if type(pktData) is dpkt.arp.ARP:
#				print "ARP"
#				arpCount+=1

			if type(pktData) is dpkt.ip.IP:
				ip = pktData

				#Filter out any useless error packets such as those from 0.0.0.0 to 255.255.255.255 etc.
				if socket.inet_ntoa(ip.dst) != '255.255.255.255' or socket.inet_ntoa(ip.src) != '0.0.0.0':

					#Since each pcap file corresponds to a host, we can manually add their ip addresses to a dictionary so we can easily
					# trace packets and construct the packet path.
					if filename[pcapFileIndex] == "h":
						fileStr = filename[pcapFileIndex:]
						indexOfDot = fileStr.index(".")
						if indexOfDot == 2:
							PacketReader.fileIpDict[filename[pcapFileIndex:]] = "10.0.0." + fileStr[1]

						else:
							PacketReader.fileIpDict[filename[pcapFileIndex:]] = "10.0.0." + fileStr[1:indexOfDot - 1]

					#Switches don't have ip addresses but for the purposes of the animator, we need to give each a dummy ip address so that the
					# translator can differentiate between them.
					else:
						fileStr = filename[pcapFileIndex:]
						indexOfDash = fileStr.index("-")
						if indexOfDash == 2:
							switchNum = int(fileStr[1]) - 1
							PacketReader.fileIpDict[filename[pcapFileIndex:]] = "-.-.-." + str(switchNum)

						else:
							switchNum = int(fileStr[1:indexOfDash - 1]) - 1
							PacketReader.fileIpDict[filename[pcapFileIndex:]] = "-.-.-." + switchNum
						
#					print 'Timestamp: ', str(datetime.datetime.utcfromtimestamp(ts)), " ", socket.inet_ntoa(ip.src), " -> ", socket.inet_ntoa(ip.dst)

					#Get timestamp after decimal point.
					timestamp = str(ts - int(ts))
					timestampList = list(timestamp)

					#Sometimes the timestamps occur so closely together that we can't tell them apart. If this happens and we're
					# reading a host pcap file, we add one to the time since this is the final destination of the packet and
					# comes after the other duplicate timestamp. If it's a switch it comes before so we take one away.
					if PacketReader.readPktTimes.count(timestamp) > 0:
						previousFile = PacketReader.timeFileDict[timestamp]
						print "THERE IS A DUPLICATE IN ", filename[pcapFileIndex:], " FOLLOWING ", previousFile
						print "BEFORE : ", timestamp
#						PacketReader.timePktDict.has_key(str(ts - int(ts)))
						if  previousFile[0] == "h" and filename[pcapFileIndex] == "s":
							print "CHANGING THE TIMESTAMP IN ", filename, " FROM ", previousFile
							indexOfp = previousFile.index('p')
							hostNum = previousFile[indexOfp - 2]
							dst = socket.inet_ntoa(ip.dst)

							if dst[7:] == hostNum:
								digitIndex = len(timestamp) - 1
								if timestampList[digitIndex] == '0':
									intStamp = int(timestamp[2:]) - 1
									timestampList = list(str(intStamp))
									timestamp = ''.join(timestampList)
									timestamp = "0." + timestamp
								else:	
									timestampList[len(timestamp) - 1] = str(int(timestampList[len(timestamp) - 1]) + 1)
									timestampList[len(timestamp) - 1] = str(int(timestamp[len(timestamp) - 1]) - 1)
								timestamp = ''.join(timestampList)

							else:
								digitIndex = len(timestamp) - 1
								if timestampList[digitIndex] == '9':
									intStamp = int(timestamp[2:]) + 1
									timestampList = list(str(intStamp))
									timestamp = ''.join(timestampList)
									timestamp = "0." + timestamp
									
								else:	
									timestampList[len(timestamp) - 1] = str(int(timestampList[len(timestamp) - 1]) + 1)
									timestamp = ''.join(timestampList)

						print "AFTER : ", timestamp

					srcIPstring = socket.inet_ntoa(ip.src)
					nodeNum = float(srcIPstring[7:])
					pktID = ip.id/nodeNum

					#Extract the relevant information from timestamp (values after decimal point)
					PacketReader.readPktTimes.append(timestamp)
					PacketReader.timePktDict[timestamp] = pktID
					PacketReader.timeFileDict[timestamp] = filename[pcapFileIndex:]
					
					if filename[pcapFileIndex] == "h":
						dst_ip_addr_str = socket.inet_ntoa(ip.dst)
						src_ip_addr_str = socket.inet_ntoa(ip.src)
						PacketReader.srcIP_list.append(src_ip_addr_str)
						PacketReader.dstIP_list.append(dst_ip_addr_str)
#						print ip.__hdr__


			PacketReader.pktCounter+=1

#		print tcpSeqNos
#		print "UDP pkts = " + str(udpCount/2)
		print "TCP pkts = " + str(tcpCount)
#		print "ICMP pkts = " + str(icmpCount/2)

		for i in range(len(PacketReader.readPktTimes)):
			if PacketReader.readPktTimes.count(PacketReader.readPktTimes[i]) > 1:
				print "THERE ARE STILL DUPLICATES."

		print PacketReader.timeFileDict
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

		for i in range(numberTimes + 1):
			if i != numberTimes:
				minimum = min(PacketReader.readPktTimes)
				packetNumber = PacketReader.timePktDict.get(minimum, None)
				filename = PacketReader.timeFileDict.get(minimum, None)
			
			if (packets.count(packetNumber) == 0 and len(packets) != 0) or i == numberTimes:
				for j in range(len(times) - 1):
					time = (float(times[j+1]) - float(times[j]))
#					print "TIME: ", time, " = ", times[j+1], " - ", times[j]
					PacketReader.pktTimes.append(time)
					print files
					srcIp = PacketReader.fileIpDict[files[j]]
					PacketReader.fullSrcIP_list.append(srcIp)

				for k in range(1, len(files)):
					print files
					dstIp = PacketReader.fileIpDict[files[k]]
					PacketReader.fullDstIP_list.append(dstIp)

				packets = []
				times = []
				files = []
				packets.append(packetNumber)
				files.append(filename)
				times.append(minimum)
				if i != numberTimes:
					del PacketReader.readPktTimes[PacketReader.readPktTimes.index(minimum)]

			else:
				print packets
				packets.append(packetNumber)
				files.append(filename)
				times.append(minimum)
				del PacketReader.readPktTimes[PacketReader.readPktTimes.index(minimum)]


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
