#Comhghall McKeating
#xml translator

import sys

class Translator:
	'Translates packets into xml lines.'
	def __init__(self, srcIP_Addrs, dstIP_Addrs):
		self.srcIP_Addrs = srcIP_Addrs
		self.dstIP_Addrs = dstIP_Addrs

	def convert(self, ip): 
		dotCount = 0		
		for index in range (len(ip)):
			if dotCount == 3:
				addr = ip[index:len(ip)]
				break
			
			elif ip[index] == '.':
				dotCount+=1
		return addr

#	def writeToXML(self):

list1 = ["10.0.0.1"]
list2 = ["10.0.0.2"]
translator = Translator(list1, list2)
print translator.convert("10.0.0.1")
