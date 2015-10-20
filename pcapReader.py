#Comhghall McKeating
#dpkt pcap reader test.

import dpkt
import sys
import socket

f = open('test.pcap')
pcap = dpkt.pcap.Reader(f)

for ts, buf in pcap:
	eth = dpkt.ethernet.Ethernet(buf)
	ip = eth.data
	tcp = ip.data

	dst_ip_addr_str = socket.inet_ntoa(ip.dst)
	print dst_ip_addr_str

#	if tcp.dport == 80 and len(tcp.data) > 0:
#		http = dpkt.http.Request(tcp.data)
#		print 'test'
#		print http.uri

f.close()
