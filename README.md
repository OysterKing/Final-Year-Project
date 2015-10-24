# Final-Year-Project
The aim of this project is to develop a GUI-based application allowing users to create simple network topologies, run IP traffic over these networks, and analyse the IP packet flow in slow motion for a better understanding of how core Internet protocols work. A desirable goal is to wrap the solution as a virtual machine instance that can be replicated for as many sessions as needed by a tutor/demonstrator.

19/10/15:
Added a basic pcap file reader to learn how information is parsed.

20/10/15:
Added a line to parse the destination ip address of each packet and convert it to a string.

21/10/15:
Made the pcap reader into a class to be used by the translator. Saved the source and destination ip addresses in lists.

22/10/15:
Wrote a small translator class. At the moment it just extracts the last part of an ip address and prints it. Also added return statements to fucntions in pcapReader.

Updated the translator class so it now writes to an XML file that netanim can run. It writes a line for each packet. I need to figure out how to time each of the packets so the animation runs correctly.

23/10/15:
Updated the pcapReader class. It now reads the timestamps of the packets in the pcap file made by tcpdump and saves them in a list.

24/10/15:
The translator now writes the animation times to the XML file correctly using the times given by pcapreader. Pcap reader now converts the timestamps to packet times.
