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
	readPktTimes = []
	pktTimes = []

	def __init__(self, filename):
		self.filename = filename
	
	def openFile(self):
		f = open(self.filename)
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

			ethSrc = binascii.hexlify(eth.src)
			ethDst = binascii.hexlify(eth.dst)
	
			macSrc = self.decodeMacAddr(ethSrc)
			macDst = self.decodeMacAddr(ethDst)



			
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
				icmpCount+=1
				ip = pktData
				#print ts
				
				if socket.inet_ntoa(ip.dst) != '255.255.255.255' or socket.inet_ntoa(ip.src) != '0.0.0.0':
					print 'Timestamp: ', str(datetime.datetime.utcfromtimestamp(ts))
					print ts, " ", socket.inet_ntoa(ip.src), " -> ", socket.inet_ntoa(ip.dst)
					PacketReader.readPktTimes.append(ts)
					
					if PacketReader.pktCounter == 0 or PacketReader.pktCounter%2 == 0:
						
						dst_ip_addr_str = socket.inet_ntoa(ip.dst)
						src_ip_addr_str = socket.inet_ntoa(ip.src)
						print "MAC PATH: ", macSrc, " -> ", macDst, " (", ts, ") (", src_ip_addr_str, " -> ", dst_ip_addr_str, ")"
#						print src_ip_addr_str + " " + dst_ip_addr_str
						PacketReader.srcIP_list.append(src_ip_addr_str)
						PacketReader.dstIP_list.append(dst_ip_addr_str)

			PacketReader.pktCounter+=1

		print PacketReader.srcIP_list
		print PacketReader.dstIP_list
#		print tcpSeqNos
		print "UDP pkts = " + str(udpCount/2)
		print "TCP pkts = " + str(tcpCount/2)
		print "ICMP pkts = " + str(icmpCount/2)
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
			print PacketReader.readPktTimes[j+1], " - ", PacketReader.readPktTimes[j], " * 1000 = ", time
			PacketReader.pktTimes.append(time)
			j += 2
		print "times = ", PacketReader.pktTimes


	def printTimes(self):
		for i in range (len(PacketReader.pktTimes)):
			print PacketReader.pktTimes[i], " (", PacketReader.srcIP_list[i], " -> ", PacketReader.dstIP_list[i], ")"
		return

#This function accepts a 12 hex digit string and converts it to colon separated string.
	def decodeMacAddr(self, mac_addr):
		s = list()
		for i in range(12/2):
			s.append(str(int(mac_addr[i*2:i*2+2], 16)))
		r = ":".join(s)
		return r


#	def printNumPkts(self):
#		print "Number of packets = ", PacketReader.pktCounter/2
#		return

reader = PacketReader("h2.pcap")
reader.openFile()
reader.calculateTimes()
reader.printSrcIPAddrs()
print " "
reader.printDstIPAddrs()
print " "
reader.printTimes()
#reader.printNumPkts()
