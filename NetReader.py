import sys
import socket
import struct

try:
	from mininet.topo import Topo

	class customTopo(Topo):

		def __init__(self, blocking = False, link_opts = {}, xmlFilename = "netanim_topo.xml", **opts):

			Topo.__init__(self, **opts)
			hostIDs = []
			switchIDs = []
			hostCount = 0
			switchCount = 0

			with open(xmlFilename, 'r') as file:
				data = file.readlines()

			for i in range(len(data)):
				if data[i].startswith("<nu") and data[i].count('r="255"'):
					#host
					hostCount += 1
					name = "h" + str(hostCount)
					host = self.addHost(name)
					hostIDs.append(int(data[i - 1][10]))

				elif data[i].startswith("<nu") and data[i].count('g="255"'):
					#switch
					switchCount += 1
					name = "s" + str(switchCount)
					switch = self.addSwitch(name, blocking = blocking)
					switchIDs.append(int(data[i - 1][10]))

			hostCount = 0
			switchCount = 1 #hardcoded for testing

			#Need to wait until all hosts and switches have been added before
			# adding links. Need to find proper way of getting host and switch ids.
			for i in range(len(data)):
				if data[i].startswith("<link"):
					#link
					fromID = int(data[i][14])
					toID = int(data[i][23])
					for j in range(len(hostIDs)):
						if hostIDs[j] == fromID:
							hostCount += 1
							fromNode = str("h" + str(hostCount))

						elif hostIDs[j] == toID:
							hostCount += 1
							toNode = str("h" + str(hostCount))

					for k in range(len(switchIDs)):
						if switchIDs[k] == fromID:
							#switchCount += 1
							fromNode = str("s" + str(switchCount))

						elif switchIDs[k] == toID:
							#switchCount += 1
							toNode = str("s" + str(switchCount))

					print fromNode
					print toNode
					self.addLink(fromNode, toNode, **link_opts)

except ImportError:
	pass