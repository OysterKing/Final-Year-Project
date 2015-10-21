#Comhghall McKeating
#dpkt pcap reader test.

import dpkt
import sys
import socket

class PacketReader:
	'Class to read pcap file.'
	numberOfPackets = 0
	srcIP_list = []
	dstIP_list = []

	def __init__(self, filename):
		self.filename = filename
	
	def openFile(self):
		f = open(self.filename)
		pcap = dpkt.pcap.Reader(f)
	
		for ts, buf in pcap:
			eth = dpkt.ethernet.Ethernet(buf)
			ip = eth.data
			tcp = ip.data
	
			dst_ip_addr_str = socket.inet_ntoa(ip.dst)
			src_ip_addr_str = socket.inet_ntoa(ip.src)

			if src_ip_addr_str != dst_ip_addr_str:
				PacketReader.srcIP_list.append(src_ip_addr_str)
				PacketReader.dstIP_list.append(dst_ip_addr_str)
				PacketReader.numberOfPackets += 1

		f.close()

	def printSrcIPAddrs(self):
		print PacketReader.srcIP_list

	def printDstIPAddrs(self):
		print PacketReader.dstIP_list

	def printNumPkts(self):
		print "Number of packets = ", PacketReader.numberOfPackets

reader = PacketReader("test.pcap")
reader.openFile()
reader.printSrcIPAddrs()
print " "
reader.printDstIPAddrs()
