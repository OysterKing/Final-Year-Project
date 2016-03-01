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

21/11/15:
Added functionality to the run button so that it saves the topology created in draw to an xml file in a format that netanim can read. The pcap translator will add the missing lines. I added various data maps to drawscene to allow me to access the required data in drawmode.

05/01/16:
Added checks to the pcap reader to decode the mac addresses of the ethernet source and destinations in an effort to track packets accross the network.

08/01/16:
Added a line to convert the timestamps to a more legible datetime format.

11/01/16:
Had a corrupt tree in my github repository so committing two days work now. Changed the calculate times function to work with the timestamps saved from each pcap file as opposed to a merged pcap file. Each packet now has a travel time between switches and hosts.

11/01/16:
Edited the translator file so that it adds correct animations. Unfortunately I have an issue with sorting out the ids in the animations."

12/01/16:
Edited the translator file so that is now reads the correct host and switch ids that the user has added to their custom topology. The function getHostSwitchIDs iterated through the xml file and extracts the host and switch IDs and saves them to separate lists. The convertIP function now uses the last number in the ip address to correctly access these lists and return the node id.

13/01/16:
Created a new class called NetReader that will read the xml file containing the custom topology and create a corresponding mininet topology. Need to add another class that initialises and launches mininet.
Created a new class called NetInitialiser that starts up the custom topology on mininet read by the NetReader.

14/01/16:
Had to clone the project again do to a corrupt file, some changes to files may be undocumented. Added a small change to the NetReader class to correctly create the links between the hosts and switches.

15/01/16:
Linked the python scripts together so that now pcapReader and Translator are called from NetInitialiser after the mininet session has finished. Command line arguments are used to pass parameters to these classes.
Added a new button to the draw tab that allows users to run mininet on the topology that they have created with preset results.

19/01/16:
Updated the pcap reader so that it can now deal with a variable number of switches as opposed to just one. Needs to be more thoroughly tested. Now use packet sequence number to sort them out and time them correctly.

20/01/16:
Updated the pcap reader to more accurately separate duplicate timestamps by moving the last digit after the decimal point either up or down depending on where in the sequence it should come.

21/01/16:
Attempted to change the duplicate time algorithm to account for when the last digit of a time is 9 or 0. Not perfect yet.

22/01/16:
Fixed the time duplicate algorithm so that it changes them correctly though I may need to consider adding more to the timestamps so that the animation looks nicer. Deleted a line in NetInitialiser.

23/01/16:
Fixed the way I add the ip addresses to source and destination lists so now all the animations run correctly for any number of switches.
Added comments and deleted a lot of print statements used for debugging.

26/01/16:
The file paths are no longer hardcoded in pcapReader, drawmode or NetInitialiser.

27/01/16:
NetInitialiser now opens all terminals in a tabbed format which is more readible and neat. It also runs tcpdump on each of the hosts and switches in the background. Changed the filepath so that pcap files arent saved in the netanim folder.

30/01/16:
Had another corrupt git repository so had to clone again. I deleted some of the functions and lists that are no longer needed in pcap reader.
Added a line to pcap reader to delete the pcap files when they are no longer needed; this prevents later errors since the pcap files are always labelled the same.

31/01/16:
Fixed an error where I was looking at the incorrect index when checking for duplicate timestamps in pcapReader.
Hardcoded in some default delay to try prevent duplicate timestamps from occurring.
Added new fields to draw mode and made the buttons more clear.

01/02/16:
Fixed an error where labels weren't appearing correctly in the side toolbar of drawmode.
Users can now customise delay, bandwidth and loss for each link. This information is then displayed on the link instead of "h.0->s.0".

02/02/16:
Added bridge_switch file that contains settings for the mininet switches. Should have been included earlier.

03/02/16:
I encountered an error regarding multiple packets in transit. I fixed this by changing the calulateTimes method in pcapReader. It is now more efficient, neat and works correctly, taking into account the possibility of multiple packets on the network.

04/02/16:
Changed filepaths so that now the program works out of the Final-Year-Project folder and the pcap and xml files are saved in a sub folder called resources.

06/02/16:
Added code to netanim to write the link options chosen by the user to the temporary xml file. The NetReader then parse this information for each link and initiates them in mininet. Translator deletes this extra information when it is writing the final executable xml file.
Changed the aesthetic of the buttons in the draw window so that they now have a border.

07/02/16:
Added a delete button that deletes nodes and labels.

09/02/16:
Added a new window to netanim. An instance of this window is opened for every file in a folder called "demos". At the moment the window is blank.
Added code so that now each tab added as a demo is named after each file in the demo directory.
Added the demo view and demo scene classes.

11/02/16:
Added a parse function to demomode to parse the demo xml text files. At the moment it just prints the file to the console.

12/02/16:
Added an xml manager class that can read and write xml files. This will be used to write and read demo text.

15/02/16:
Added a read xml function to the xml manager to parse the demo text xml files. Each detail is saved in a vector of strings and can be accessed later when adding the text items to the graphics scene.

16/02/16:
Connected the xml parser to the demo scene so that now what is in the xml demo file is displayed as a text item in the demo windows.

17/02/16:
Deleted redundant demoscene and demoview classes and moved the addTextItem function to demomode which now instantiates a simple QGraphicsScene and QGraphicsView object.
Added a new function to demomode that adds all the text items after the tab has been given its name. This means I can display two different demo files in two different windows.

18/02/16:
Added some default x and y positions for the text items in demomode that are incremented with each piece of text. This leads to a nicer layout.

19/02/16:
Added  new class, demowritemode to allow users to write their own demos.
Added a text box to the demowrite tab and a save button that doesn't do anything just yet.
Connected the save button to a slot function that creates a folder with the demo name and puts the xmlt text file inside it.

24/02/16:
Added a new set of arguments to the net intiliaser that signal what mode to run mininet in and whether or not to run a dhcp server. I added three new buttons to facilitate these modes.
Also added some functions to the demowriter in attempt to add a rich text editor.

25/02/16:
Added code to the netInitialiser and the netReader to facilitate the different modes of running (blank, basic, or dhcp).

27/02/16:
Fixed an issue in net initialiser that was causing the if statements not to trip. Turns out I was treating the enableDhcp etc. variables as Booleans when they were, in fact, strings.

29/02/16:
My lesson management module now supports rich text formatting. Users can underline text, change its color, make it bold etc.

01/02/16:
Changed the demo mode to now display the rich text that is written in the lesson management module.
Deleted xml manager as it is no longer needed.
Added an add image button to the lesson module to load an image fiel into the text editor. CHanged the text editor in demo mode into a QTextBrowser so that images could be displayed.