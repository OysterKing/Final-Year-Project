from mininet.clean import cleanup
from mininet.cli import CLI
from mininet.term import cleanUpScreens
from mininet.net import Mininet
from mininet.link import TCLink
from mininet.util import dumpNodeConnections
from mininet.log import setLogLevel
from mininet.node import Controller, OVSController
from NetReader import basicTopo, dhcpTopo
from bridge_switch import BridgeSwitch
from router import Router
from translator import Translator
from pcapReader import PacketReader
from random_network import random_macs, random_subnet
import sys
from utils import makeTerm, makeTerms, makeTabbedTerm
from subprocess import Popen
import getpass
import socket, struct

def customNet(username, enableBlank, enableBasic, enableDhcp):
	user = username
	link_opts = {"bw":1000, "delay":10, "loss": 0, "use_htb": False}
	filename = "netanim_topo.xml"
	basic = enableBasic
	blank = enableBlank
	dhcp = enableDhcp

	print "enableBlank = ", enableBlank
	print "enableDhcp = ", enableDhcp
	print "enableBasic = ", enableBasic

	if(basic == "true" or blank == "true"):
		topo = basicTopo(link_opts = link_opts, filename = filename)
		net = Mininet(topo, switch = BridgeSwitch, controller = OVSController, link = TCLink)

	elif(dhcp == "true"):
		topo = dhcpTopo(link_opts = link_opts, filename = filename)
		net = Mininet(topo, switch = Router, controller = OVSController, link = TCLink)
	
	net.start()

	macs = random_macs(len(net.hosts))

	for offset, host in enumerate(net.hosts):
		#Set up default network with hardcoded ip addresses.
		if(basic == "true"):
			print "Capturing on hosts...", offset
			path = "/home/comhghall/Final-Year-Project/resources/" + str(host) + ".pcap"
			print "path = ", path
			host.cmd("tcpdump -u -w", path, "&")

		#Set up a blank network.
		elif(blank == "true" or dhcp == "true"):
			print "Capturing on hosts...", offset
			path = "/home/comhghall/Final-Year-Project/resources/" + str(host) + ".pcap"
			print "path = ", path
			host.cmd("tcpdump -u -w", path, "&")
			interface = host.intf()
			print "Setting interfaces down..."
			host.cmd("ifconfig", interface, "down")
			host.cmd("ifconfig", interface, "0.0.0.0")
			host.cmd("ifconfig", interface, hex(macs[offset]))
			host.cmd("ifconfig", interface, "down")

	for offset, switch in enumerate(net.switches):
		if(basic or blank):
			print "Capturing on switches...", offset
			print switch
			path = "/home/comhghall/Final-Year-Project/resources/" + str(switch) + "-eth0.pcap"
			print "path = ", path
			switch.cmd("tcpdump -i", switch, "-u -w", path, "&")

		if(dhcp):
			print "Capturing on switches...", offset
			print switch
			path = "/home/comhghall/Final-Year-Project/resources/" + str(switch) + "-eth0.pcap"
			switch.cmd("tcpdump -i", switch, "-u -w", path, "&")
			print "path = ", path
			switch.cmd("sysctl -w net.ipv4.ip_forward=1")
			if str(switch)[0] != "r":
				print "Bridge switch..."
				switch.cmd("brctl", switch, "down")
				switch.cmd("brclt delbr", switch)
				switch.cmd("brctl addbr", switch)
				for interface in switch.intfNames():
					if interface != "lo":
						switch.cmd("ifconfig", interface, "down")
				for interface in switch.intfNames():
					if interface != "lo":
						switch.cmd("brctl addif", switch, interface)
				switch.cmd("brctl", switch, "up")
				for interface in switch.intfNames():
					if interface != "lo":
						switch.cmd("ifconfig", interface, "up")
			else:
				print "Router..."
				switch.cmd("echo","",">/etc/dnsmasq.conf")
				for interface in switch.intfNames():
					if interface != "lo":
						switch.cmd("ifconfig", interface, "down")
						prefix,subnet_mask = random_subnet(24)
						dhcp_entry = "dhcp-range=" + socket.inet_ntoa(struct.pack('!L', prefix+10)) +"," + socket.inet_ntoa(struct.pack('!L', prefix+20))+",30s"
						print dhcp_entry
						switch.cmd("echo",dhcp_entry,">>/etc/dnsmasq.conf")
						switch.cmd("ifconfig", interface, "{0}/{1}".format(prefix+1, subnet_mask))
						switch.cmd("ifconfig", interface, "up")
				switch.cmd("dnsmasq")

	net.terms = makeTabbedTerm(net.hosts, term = "xfce")
	net.terms = makeTabbedTerm(net.switches, term = "xfce")

	CLI(net)
	net.stop()

def main():
	import os
	DEVNULL = open(os.devnull, 'wb')

	Popen(["sudo", "pkill", "ovs"], stdout=DEVNULL, stderr=DEVNULL)
	Popen(["sudo", "pkill", "dnsmasq"], stdout=DEVNULL, stderr=DEVNULL)
	#pass the username to the custom net function
	customNet(username = sys.argv[5], enableBlank = sys.argv[1], enableBasic = sys.argv[2], enableDhcp = sys.argv[3])
	
	arguments = sys.argv[1:]
	pcapFiles = []
	username = sys.argv[5]

	#sudo python NetInitialiser.py bw delay loss file.xml h1.pcap h2.pcap s1-eth1.pcap
	for i in range(6, len(sys.argv)):
		pcapFiles = sys.argv[i].split()

	print "pcap files = ", pcapFiles
	packetReader = PacketReader(pcapFiles, username)
	packetReader.openFiles()
	packetReader.calculateTimes()
	print " "
	print packetReader.getFullSrcIPList()
	print " "
	print packetReader.getFullDstIPList()
	translator = Translator(packetReader.getFullSrcIPList(), packetReader.getFullDstIPList(), packetReader.getPktTimes())
	print sys.argv[4]
	translator.getHostSwitchIDs(sys.argv[4])
	#username = getpass.getuser()
	translator.writeToXML("/home/" + username + "/Final-Year-Project/resources/netanim_topo.xml")

if __name__ == '__main__':
	main()