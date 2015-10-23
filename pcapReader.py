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
	packetTimes = []

	def __init__(self, filename):
		self.filename = filename
	
	def openFile(self):
		f = open(self.filename)
		pcap = dpkt.pcap.Reader(f)

		for ts, buf in pcap:
			if PacketReader.pktCounter == 0 or PacketReader.pktCounter%2 == 0:
				eth = dpkt.ethernet.Ethernet(buf)
				ip = eth.data
				if type(ip) is dpkt.ip.IP:
					print ts
					PacketReader.packetTimes.append(ts)
					dst_ip_addr_str = socket.inet_ntoa(ip.dst)
					src_ip_addr_str = socket.inet_ntoa(ip.src)
					print src_ip_addr_str + " " + dst_ip_addr_str
	
#					if src_ip_addr_str != dst_ip_addr_str:
					PacketReader.srcIP_list.append(src_ip_addr_str)
					PacketReader.dstIP_list.append(dst_ip_addr_str)
			PacketReader.pktCounter+=1

		f.close()
		return

	def printSrcIPAddrs(self):
		print PacketReader.srcIP_list
		return

	def printDstIPAddrs(self):
		print PacketReader.dstIP_list
		return
	
	def printTimes(self):
		print PacketReader.packetTimes
		return

#	def printNumPkts(self):
#		print "Number of packets = ", PacketReader.pktCounter/2
#		return

reader = PacketReader("test3.pcap")
reader.openFile()
reader.printSrcIPAddrs()
print " "
reader.printDstIPAddrs()
print " "
reader.printTimes()
#reader.printNumPkts()
