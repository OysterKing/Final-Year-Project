#Comhghall McKeating
#dpkt pcap reader test.

import dpkt
import sys
import socket

class PacketReader:
	'Class to read pcap file.'
	pktCounter = 0
	srcIP_list = []
	dstIP_list = []
	readPktTimes = []
	pktTimes = []

	def __init__(self, filename):
		self.filename = filename
	
	def openFile(self):
		f = open(self.filename)
		pcap = dpkt.pcap.Reader(f)

		for ts, buf in pcap:			
			eth = dpkt.ethernet.Ethernet(buf)
			pktData = eth.data

			if type(pktData) is dpkt.arp.ARP:
				print "ARP"

			if type(pktData) is dpkt.ip.IP:
				ip = pktData
				print ts
				if socket.inet_ntoa(ip.dst) != '255.255.255.255' or socket.inet_ntoa(ip.src) != '0.0.0.0':
					PacketReader.readPktTimes.append(ts)

					if PacketReader.pktCounter == 0 or PacketReader.pktCounter%2 == 0:
						dst_ip_addr_str = socket.inet_ntoa(ip.dst)
						src_ip_addr_str = socket.inet_ntoa(ip.src)
						print src_ip_addr_str + " " + dst_ip_addr_str
						PacketReader.srcIP_list.append(src_ip_addr_str)
						PacketReader.dstIP_list.append(dst_ip_addr_str)

			PacketReader.pktCounter+=1

		print PacketReader.srcIP_list
		print PacketReader.dstIP_list
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
		for i in range (len(PacketReader.readPktTimes)/2):
			time = (PacketReader.readPktTimes[j+1] - PacketReader.readPktTimes[j]) * 1000
			PacketReader.pktTimes.append(time)
			j += 2
		print PacketReader.pktTimes


	def printTimes(self):
		print PacketReader.pktTimes
		return

#	def printNumPkts(self):
#		print "Number of packets = ", PacketReader.pktCounter/2
#		return

#reader = PacketReader("test3.pcap")
#reader.openFile()
#reader.calculateTimes()
#reader.printSrcIPAddrs()
#print " "
#reader.printDstIPAddrs()
#print " "
#reader.printTimes()
#reader.printNumPkts()
