#Comhghall McKeating
#dpkt pcap reader test.

import dpkt
import sys
import socket
import binascii
import datetime

class PacketReader:
	'Class to read pcap file.'
	pktCounter = 0
	srcIP_list = []
	dstIP_list = []
	timePktDict = {}
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
					print 'Timestamp: ', str(datetime.datetime.utcfromtimestamp(ts)), " ", socket.inet_ntoa(ip.src), " -> ", socket.inet_ntoa(ip.dst)

					#Get timestamp after decimal point.
					timestamp = ts - int(ts)

					#Sometimes the timestamps occur so closely together that we can't tell them apart. If this happens and we're
					# reading a host pcap file, we add one to the time since this is the final destination of the packet and
					# comes after the other duplicate timestamp. If it's a switch it comes before so we take one away.
					if PacketReader.readPktTimes.count(str(timestamp)) > 0:
						if filename[0] == "h":
							ts += 0.000001

						else:
							ts -= 0.000001

					#Extract the relevant information from timestamp (values after decimal point)
					print str(ts - int(ts)), " string"
					PacketReader.readPktTimes.append(str(ts - int(ts)))
					print filename, " ", icmpCount
					PacketReader.timePktDict[str(ts - int(ts))] = "icmp", icmpCount
					
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
		f.close()
		return

	def printSrcIPAddrs(self):
		print PacketReader.srcIP_list
		return

	def printDstIPAddrs(self):
		print PacketReader.dstIP_list
		return

	def calculateTimes(self):
		j = 0
		packets = []
		times = []
		numberNodes = len(PacketReader.pcapFiles)
		numberTimes = len(PacketReader.readPktTimes)
		print " "
		print PacketReader.readPktTimes
		print " "

		#For each of the saved times, find the packets that correspond to them. Every n-th packet,
		# where n = number of pcap files, is a new packet so we calculate the times for the packet we've
		# already saved and go again.
		for i in range(numberTimes + 1):
			if (i%numberNodes == 0 and i != 0):
				print i
				print times
				print packets
				for j in range (len(times) - 1):
					time = (float(times[j+1]) - float(times[j]))
					print "TIME: ", time, " = ", times[j+1], " - ", times[j]
					PacketReader.pktTimes.append(time)
				packets = []
				times = []

				if i != numberTimes:
					minimum = min(PacketReader.readPktTimes)
					packetNumber = PacketReader.timePktDict.get(minimum, None)
					del PacketReader.readPktTimes[PacketReader.readPktTimes.index(minimum)]
					print "pktNumber = ", packetNumber
					packets.append(PacketReader.timePktDict.get(minimum, None))
					times.append(minimum)

			else:
				minimum = min(PacketReader.readPktTimes)
				packetNumber = PacketReader.timePktDict.get(minimum, None)
				del PacketReader.readPktTimes[PacketReader.readPktTimes.index(minimum)]
				print "pktNumber = ", packetNumber
				packets.append(PacketReader.timePktDict.get(minimum, None))
				times.append(minimum)

		print "times = ", PacketReader.pktTimes


	def printTimes(self):
		for i in range (len(PacketReader.pktTimes)):
			print PacketReader.pktTimes[i], " (", PacketReader.srcIP_list[i], " -> ", PacketReader.dstIP_list[i], ")"
		return

#	def printNumPkts(self):
#		print "Number of packets = ", PacketReader.pktCounter/2
#		return

reader = PacketReader(["h1.pcap", "h2.pcap", "s1-eth1.pcap"])
reader.openFiles()
reader.calculateTimes()
reader.printSrcIPAddrs()
print " "
reader.printDstIPAddrs()
print " "
#reader.printTimes()
#reader.printNumPkts()
