from mininet.clean import cleanup
from mininet.cli import CLI
from mininet.term import cleanUpScreens
from mininet.net import Mininet
from mininet.link import TCLink
from mininet.util import dumpNodeConnections
from mininet.log import setLogLevel
from mininet.node import Controller, OVSController
from NetReader import customTopo
from bridge_switch import BridgeSwitch
from translator import Translator
from pcapReader import PacketReader
import sys
from utils import makeTerm, makeTerms, makeTabbedTerm
from subprocess import Popen
import getpass

def customNet(username, enableBlank, enableBasic, enableDhcp):
	user = username
	link_opts = {"bw":1000, "delay":10, "loss": 0, "use_htb": False}
	filename = "netanim_topo.xml"
	topo = customTopo(link_opts = link_opts, filename = filename)

	net = Mininet(topo, switch = BridgeSwitch, controller = OVSController, link = TCLink)
	net.start()

	for offset, host in enumerate(net.hosts):
		print "Capturing on hosts...", offset
#		net.terms = makeTabbedTerm([net.hosts[offset]], term="xfce")
		path = "/home/comhghall/Final-Year-Project/resources/" + str(host) + ".pcap"
		print "path = ", path
		host.cmd("tcpdump -u -w", path, "&")
#		tcpdump = net.terms[offset]
#		tcpdump = tcpdump.Popen("tcpdump", "-u", "-w", pcap)
#		Popen(["tcpdump", "-u", "-w", pcap])
#		print type(tcpdump)

	for offset, switch in enumerate(net.switches):
		print "Capturing on switches...", offset
		print switch
		path = "/home/comhghall/Final-Year-Project/resources/" + str(switch) + "-eth0.pcap"
		print "path = ", path
		switch.cmd("tcpdump -i", switch, "-u -w", path, "&")
#		net.terms = makeTabbedTerm([net.switches[offset]], term="xfce")

	net.terms = makeTabbedTerm(net.hosts, term = "xfce")
	net.terms = makeTabbedTerm(net.switches, term = "xfce")

	CLI(net)
	net.stop()

def main():
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