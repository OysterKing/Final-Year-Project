# Final-Year-Project
The aim of this project is to develop a GUI-based application allowing users to create simple network topologies, run IP traffic over these networks, and analyse the IP packet flow in slow motion for a better understanding of how core Internet protocols work. A desirable goal is to wrap the solution as a virtual machine instance that can be replicated for as many sessions as needed by a tutor/demonstrator.

19/10/15:
Added a basic pcap file reader to learn how information is parsed.

20/10/15:
Added a line to parse the destination ip address of each packet and convert it to a string.

21/10/15:
Made the pcap reader into a class to be used by the translator. Saved the source and destination ip addresses in lists.
