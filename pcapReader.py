#Comhghall McKeating
#dpkt pcap reader test.

import dpkt
import sys

f = open('test.pcap')
pcap = dpkt.pcap.Reader(f)

for ts, buf in pcap:
	eth = dpkt.ethernet.Ethernet(buf)
	ip = eth.data
	tcp = ip.data
	print 'test'

	if tcp.dport == 80 and len(tcp.data) > 0:
		http = dpkt.http.Request(tcp.data)
		print 'test'
		print http.uri

f.close()
