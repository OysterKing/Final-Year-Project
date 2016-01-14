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
import sys
#from utils import makeTerm, makeTerms
from subprocess import Popen

def customNet():
	link_opts = {"bw":1000, "delay":0, "loss": 0, "use_htb": False}
	filename = "netanim_topo.xml"
	topo = customTopo(link_opts = link_opts, filename = filename)

	net = Mininet(topo, switch = BridgeSwitch, controller = OVSController, link = TCLink)
	net.start()
	CLI(net)
	net.stop()

def main():
	customNet()

if __name__ == '__main__':
	main()