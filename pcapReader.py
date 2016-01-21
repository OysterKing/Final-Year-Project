#Comhghall McKeating
#dpkt pcap reader test.

import dpkt
import sys
import socket
import binascii
import datetime
import decimal

class PacketReader:
	'Class to read pcap file.'
	pktCounter = 0
	srcIP_list = []
	dstIP_list = []
	fullSrcIP_list = []
	fullDstIP_list = []
	timePktDict = {}
	timeFileDict = {}
	readPktTimes = []
	pktTimes = []
	pcapFiles = []

	def __init__(self, fileNames):
		PacketReader.pcapFiles = fileNames
		print PacketReader.pcapFiles
	
	def openFiles(self):
		for i in range(len(PacketReader.pcapFiles)):
			print " "
			self.parseFile(PacketReader.pcapFiles[i]);
		return

	def parseFile(self, filename):
		f = open(filename)
		pcap = dpkt.pcap.Reader(f)
		udpCount = 0
		tcpCount = 0
		icmpCount = 0
		arpCount = 0
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
				udpCount+=1

#			if type(pktData) is dpkt.arp.ARP:
#				print "ARP"
#				arpCount+=1

			if type(pktData) is dpkt.ip.IP:
				ip = pktData

				if socket.inet_ntoa(ip.dst) != '255.255.255.255' or socket.inet_ntoa(ip.src) != '0.0.0.0':
					icmpCount+=1
					print "ID: ", ip.id
					print 'Timestamp: ', str(datetime.datetime.utcfromtimestamp(ts)), " ", socket.inet_ntoa(ip.src), " -> ", socket.inet_ntoa(ip.dst)

					#Get timestamp after decimal point.
					timestamp = str(ts - int(ts))
					timestampList = list(timestamp)
					print timestampList
					print "****BEFORE = ", timestamp

					#Sometimes the timestamps occur so closely together that we can't tell them apart. If this happens and we're
					# reading a host pcap file, we add one to the time since this is the final destination of the packet and
					# comes after the other duplicate timestamp. If it's a switch it comes before so we take one away.
					if PacketReader.readPktTimes.count(timestamp) > 0:
						previousFile = PacketReader.timeFileDict[timestamp]
#						PacketReader.timePktDict.has_key(str(ts - int(ts)))
						if  previousFile[0] == "h" and filename[38] == "s":
							indexOfp = previousFile.index('p')
							hostNum = previousFile[indexOfp - 2]
							dst = socket.inet_ntoa(ip.dst)
							print dst[7:], " and ", hostNum
							if dst[7:] == hostNum:
								print "DESTINATION CULPRIT = ", filename
								digitIndex = len(timestamp) - 1
								if timestampList[digitIndex] == '0':
									while timestampList[digitIndex] == '0':
										timestampList[digitIndex] = '9'
										if timestampList[digitIndex - 1] == '0':
											digitIndex -= 1
										else:
											timestampList[digitIndex -1] = str(int(timestampList[digitIndex]) + 1)
								
								else:	
									timestampList[len(timestamp) - 1] = str(int(timestampList[len(timestamp) - 1]) + 1)
									timestampList[len(timestamp) - 1] = str(int(timestamp[len(timestamp) - 1]) - 1)
								timestamp = ''.join(timestampList)
							else:
								print "SOURCE CULPRIT = ", filename
								digitIndex = len(timestamp) - 1
								if timestampList[digitIndex] == '9':
									while timestampList[digitIndex] == '9':
										timestampList[digitIndex] = '0'
										print timestampList
										if timestampList[digitIndex - 1] == '9':
											digitIndex -= 1
										else:
											timestampList[digitIndex -1] = str(int(timestampList[digitIndex]) + 1)

								else:	
									timestampList[len(timestamp) - 1] = str(int(timestampList[len(timestamp) - 1]) + 1)
									timestamp = ''.join(timestampList)


					srcIPstring = socket.inet_ntoa(ip.src)
					nodeNum = float(srcIPstring[7:])
					pktID = ip.id/nodeNum
					print ip.id, " -> ", pktID
						

					#Extract the relevant information from timestamp (values after decimal point)
					print timestamp, " *****AFTER"
					PacketReader.readPktTimes.append(timestamp)
					PacketReader.timePktDict[timestamp] = pktID
					PacketReader.timeFileDict[timestamp] = filename[38:]
					
					if filename[38] == "h":
						dst_ip_addr_str = socket.inet_ntoa(ip.dst)
						src_ip_addr_str = socket.inet_ntoa(ip.src)
						PacketReader.srcIP_list.append(src_ip_addr_str)
						PacketReader.dstIP_list.append(dst_ip_addr_str)

			PacketReader.pktCounter+=1

#		print PacketReader.srcIP_list
#		print PacketReader.dstIP_list
#		print tcpSeqNos
#		print "UDP pkts = " + str(udpCount/2)
#		print "TCP pkts = " + str(tcpCount/2)
#		print "ICMP pkts = " + str(icmpCount/2)

		for i in range(len(PacketReader.readPktTimes)):
			if PacketReader.readPktTimes.count(PacketReader.readPktTimes[i]) > 1:
				print "THERE ARE STILL DUPLICATES."

		print len(PacketReader.readPktTimes)
		print " "
		print PacketReader.timePktDict
		print " "
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
		print " "
		print PacketReader.readPktTimes
		print " "
		hostIPCount = 0

		for i in range(numberTimes + 1):
			if i != numberTimes:
				minimum = min(PacketReader.readPktTimes)
				packetNumber = PacketReader.timePktDict.get(minimum, None)
				filename = PacketReader.timeFileDict.get(minimum, None)
				print "p ", packets
			
			if (packets.count(packetNumber) == 0 and len(packets) != 0) or i == numberTimes:
				print packets
				print files
				for j in range(len(times) - 1):
					time = (float(times[j+1]) - float(times[j]))
					print "TIME: ", time, " = ", times[j+1], " - ", times[j]
					PacketReader.pktTimes.append(time)

	#Since switches don't have ip addresses, we have to manually insert a dummy ip address for each switch so
	# we can produce the correct animations.

				for k in range(len(files)):
					if k == 0:
						sourceIP = PacketReader.srcIP_list[hostIPCount]
						PacketReader.fullSrcIP_list.append(sourceIP)
						index = files[k + 1].index('-')
						switchNum = int(files[k + 1][index - 1]) - 1
						dstIP = "-.-.-." + str(switchNum)
						PacketReader.fullDstIP_list.append(dstIP)

					elif files[k][0] == "h":
						hostIPCount += 1


					else:
						index = files[k].index('-')
						switchNum = int(files[k][index - 1]) - 1
						sourceIP = "-.-.-." + str(switchNum)
						PacketReader.fullSrcIP_list.append(sourceIP)

						if files[k + 1][0] == "h":
							dstIP = PacketReader.dstIP_list[hostIPCount]
						else:
							index = files[k + 1].index('-')
							switchNum = int(files[k + 1][index - 1]) - 1
							dstIP = "-.-.-." + str(switchNum)

						PacketReader.fullDstIP_list.append(dstIP)

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

		
		print "times = ", PacketReader.pktTimes

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
