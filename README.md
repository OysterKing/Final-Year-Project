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

26/10/15:
Edited the pcap reader to deal with error packets that are sent from address 0.0.0.0 to 255.255.255.255. I put in a small check to see if a packet is an ARP packet and I plan to accomodate these packets. The translator has been tested on a pcap file containing packets captured after a pingall command and works.

27/10/15:
Changed pcapReader so I can now parse packets caught during an iperf command and count how many are udp and tcp.

30/10/15:
Added the NetAnim files that I plan to extend.

Added a test button to understand how the buttons are added to the GUI and how they are given functionality.

02/11/15:
Added code to animatormode.cpp to run a c program with embedded python when the test button is clicked.

Removed c file that has python embedded. I now run the python script directly from NetAnim using execv().

03/11/15:
The test button now runs the python script that Christian sent me (it opens terminals and starts mininet for each host). 

08/11/15:
Added drawmode class and drawview class and added functionality to netanim.cpp to initialise them as a new tab.

09/11/15:
Added a toolbar to drawmode and a button labelled X. I also have a "view" box which I can hopefully later turn into the area where a user can drag and drop terminals and links to make a topology.

11/11/15:
Added code to the draw classes to give a tiny area similar to the simulation area in animator mode. Also added functionality to test button to show a grid. Only shows tiny black pixel in area.

12/11/15:
Added code to drawscene and drawview to get a grid initialised in the draw tab. The function setCanvasBoundaries in drawscene instantiates the grid.

13/11/15:
Added code to draw scene and draw mode so that the test button now is checkable and, when checked, shows the position of the mouse in terms of x and y when moved over the grid.

14/11/15:
Added some calls to a mouse click event in drawscene to see if I could add an item to the grid that could later be made into a node. I think I have to make a node class first then write a method called "addItem" in drawscene before I can actually add a permanent graphics item.

15/11/15:
Added a new "item" class to define the widgets for nodes and switches. Added a dNode class which will be the drawing node that is added to the drawview. Also added a couple of new constants to animatorconstants.

16/11/15:
Managed to add a node when the mouse clicks the grid. Added calls to dNode and dNodeMgr to drawscene which allows the creation of nodes in the draw tab when the 'X' button is clicked.
Added a new "item" class to define the widgets for nodes and switches. Added a dNode class which will be the drawing node that is added to the drawview. Also added a couple of new constants to animatorconstants.

17/11/15:
Added a new button that, when clicked, adds a switch. For the moment switches are dNode objects, since nodes and switches, at least in this program, are very similar. I also added some extra functionality to the buttons; now when a button is checked the other buttons are disabled until the button is unchecked.
Added a new class to define the link that will be used between the hosts and switches.
Changed references to "node" in draw scene etc to "host" so now I have addHost and addSwitch instead of addNode and addSwitch.

18/11/15:
Added a new side tool bar to the draw tab with two editable fields; to and from. User will type the id of the host they wish to link and the id of the swithc they wish to link it to. Then they'll press the link button beneath.
Added a text item in drawscene that displays the host id when a host is added in the form "h.x" where x is the node id. Now when the user adds a node he or she can see that node's id straight away.

19/11/15:
Added some private integer variables to drawscene to keep track of the number of nodes, hosts and switches that have been added. Now, when a user adds a host or switch, the host's or switch's id is displayed correctly. I can use this when adding links.
Added functionality to the add link button in drawmode and the addlink method in drawscene. Now the user can make host to switch and switch to switch connections by typing the names of the hosts and switches into the TO and FROM box then hitting the link button.
I introduced the idea that a host and a switch has a system id and a normal id. The normal id is its host or switch id and is not unique whereas its system id is.

20/11/15:
Added some code to the add switch and add node methods in drawscene so that they now automatically assign the hosts ip addresses and mac addresses and the switches mac addresses. Extended dlink class to have strings representing bandwidth, loss, delay and max queue size. Also defined appropriate getters for these. They are instantiated by the dlink constructor.