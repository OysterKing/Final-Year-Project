/*Comhghall McKeating 12328401
 * Final Year Project*/

#include "animatormode.h"
#include "animatorscene.h"
#include "drawmode.h"
#include "drawview.h"
#include "drawscene.h"
#include "iostream"
#include "fstream"
#include "QTextStream"
#include "QFile"
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pwd.h>

//#include "drawingconstants.h"

#define SSTR( x ) dynamic_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

using namespace std;
namespace netanim
{

DrawMode * pDrawMode = 0;

DrawMode *
DrawMode::getInstance()
{
    if(!pDrawMode)
    {
        pDrawMode = new DrawMode();
    }
    return pDrawMode;
}

DrawMode::DrawMode()
{
    init();
}

QWidget *
DrawMode::getCentralWidget()
{
    return m_centralWidget;
}

QString
DrawMode::getTabName()
{
    return "Draw";
}

void
DrawMode::init()
{
    m_state = INIT;
//    DrawView::getInstance()->setScene(InterfaceStatsScene::getInstance());
    initToolbars();
    m_hLayout = new QHBoxLayout;
//    m_hLayout->addWidget(m_toolbarScrollArea);
    m_hLayout->addWidget(DrawView::getInstance());

    m_vLayout = new QVBoxLayout;
    m_vLayout->addWidget(m_topToolBar);
    m_hLayout->addWidget(m_sideToolBar);
    m_vLayout->addSpacing(10);
    m_vLayout->addLayout(m_hLayout);
    m_centralWidget = new QWidget;
    m_centralWidget->setLayout(m_vLayout);
    m_minPoint.setX(0.0);
    m_minPoint.setY(0.0);
    m_maxPoint.setX(1000.0);
    m_maxPoint.setY(1000.0);
    DrawScene::getInstance()->setCanvasBoundaries(m_minPoint, m_maxPoint);
    DrawScene::getInstance()->addGrid();
    setWindowTitle("NetAnim");

    initControls();
}

void
DrawMode::initControls()
{

}

void
DrawMode::initToolbars()
{
    initTopToolbar();
    initSideToolbar();
}

void
DrawMode::initTopToolbar()
{
    m_topToolBar = new QToolBar;

    m_addHostButton = new QToolButton;
    m_addHostButton->setToolTip("Add node");
    m_addHostButton->setText("ADD NODE");
    m_addHostButton->setCheckable(true);
    connect (m_addHostButton, SIGNAL(clicked()), this, SLOT (addHostButtonSlot()));
    m_topToolBar->addWidget(m_addHostButton);

    m_addSwitchButton = new QToolButton;
    m_addSwitchButton->setToolTip("Add switch");
    m_addSwitchButton->setText("ADD SWITCH");
    m_addSwitchButton->setCheckable(true);
    connect (m_addSwitchButton, SIGNAL(clicked()), this, SLOT (addSwitchButtonSlot()));
    m_topToolBar->addWidget(m_addSwitchButton);

    m_saveButton = new QToolButton;
    m_saveButton->setToolTip("Save");
    m_saveButton->setText("SAVE");
    connect (m_saveButton, SIGNAL(clicked()), this, SLOT (saveButtonSlot()));
    m_topToolBar->addWidget(m_saveButton);

    m_runButton = new QToolButton;
    m_runButton->setToolTip("Run");
    m_runButton->setText("RUN");
    connect (m_runButton, SIGNAL(clicked()), this, SLOT (runButtonSlot()));
    m_topToolBar->addWidget(m_runButton);
}

void
DrawMode::initSideToolbar()
{
    m_sideToolBar = new QToolBar;
    m_sideToolBar->setOrientation(Qt::Vertical);
//    m_sideToolBar->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Expanding);

    m_linkFromLabel = new QLabel;
    m_linkFromLabel->setText("FROM");
    m_sideToolBar->addWidget(m_linkFromLabel);

    m_linkFromEdit = new QLineEdit;
    m_sideToolBar->addWidget(m_linkFromEdit);

    m_linkToLabel = new QLabel;
    m_linkToLabel->setText("TO");
    m_sideToolBar->addWidget(m_linkToLabel);

    m_linkToEdit = new QLineEdit;
    m_sideToolBar->addWidget(m_linkToEdit);

    m_bwLabel = new QLabel;
    m_bwLabel->setText("BANDWIDTH");
    m_sideToolBar->addWidget(m_bwLabel);

//    QWidget *separator = new QWidget(this);
//    separator->setSizePolicy(QSizePolicy::Expanding,
//    QSizePolicy::Expanding);
//    m_sideToolBar->addWidget(separator);

    m_bwEdit = new QLineEdit;
    m_sideToolBar->addWidget(m_bwEdit);

//    m_sideToolBar->addSeparator();

    m_delayLabel = new QLabel;
    m_delayLabel->setText("DELAY");
    m_sideToolBar->addWidget(m_delayLabel);

    m_delayEdit = new QLineEdit;
    m_sideToolBar->addWidget(m_delayEdit);

//    m_sideToolBar->addSeparator();

    m_lossLabel = new QLabel;
    m_lossLabel->setText("LOSS");
    m_sideToolBar->addWidget(m_lossLabel);

    m_lossEdit = new QLineEdit;
    m_sideToolBar->addWidget(m_lossEdit);

    m_addLinkButton = new QToolButton;
    m_addLinkButton->setToolTip("Add link");
    m_addLinkButton->setText("CREATE LINK");
    connect(m_addLinkButton, SIGNAL(clicked()), this, SLOT (addLinkButtonSlot()));
    m_sideToolBar->addWidget(m_addLinkButton);

    m_sideToolBar->adjustSize();
}

void
DrawMode::setFocus(bool focus)
{
    if(focus)
    {
        //reload
    }
}

void
DrawMode::systemReset()
{
    m_state = INIT;
    //perform some form of reset
    m_state = READY;
}

void
DrawMode::addHostButtonSlot()
{
    if(m_addHostButton->isChecked()){
        m_addSwitchButton->setDisabled(true);
        m_saveButton->setDisabled(true);
    }

    else{
        m_addSwitchButton->setEnabled(true);
        m_saveButton->setEnabled(true);
    }
    DrawScene::getInstance()->enableMousePositionLabel(m_addHostButton->isChecked());
    DrawScene::getInstance()->enableHostAddition(m_addHostButton->isChecked());
}

void
DrawMode::addSwitchButtonSlot()
{
    if(m_addSwitchButton->isChecked()){
        m_addHostButton->setDisabled(true);
        m_saveButton->setDisabled(true);
    }

    else{
        m_addHostButton->setEnabled(true);
        m_saveButton->setEnabled(true);
    }
    DrawScene::getInstance()->enableMousePositionLabel(m_addSwitchButton->isChecked());
    DrawScene::getInstance()->enableSwitchAddition(m_addSwitchButton->isChecked());
}

void
DrawMode::saveButtonSlot()
{
    std::vector<QString> hosts;
    std::vector<QString> switches;
    std::vector<QString> links;
    std::vector<QString> linkOptions;
    std::map<QString, int> hostSysIdMap;
    std::map<QString, int> switchSysIdMap;
    std::map<QString, QString> hostIpMap;
    std::map<QString, QString> hostMacMap;
    std::map<QString, QString> switchMacMap;
    std::map<QString, QPointF> hostLocMap;
    std::map<QString, QPointF> switchLocMap;

    hosts = DrawScene::getInstance()->getHostVector();
    switches = DrawScene::getInstance()->getSwitchVector();
    links = DrawScene::getInstance()->getLinksVector();
    linkOptions = DrawScene::getInstance()->getLinkOptsVector();
    hostIpMap = DrawScene::getInstance()->getHostIpMap();
    hostMacMap = DrawScene::getInstance()->getHostMacMap();
    hostLocMap = DrawScene::getInstance()->getHostLocMap();
    hostSysIdMap = DrawScene::getInstance()->getHostSysIdMap();
    switchMacMap = DrawScene::getInstance()->getSwitchMacMap();
    switchLocMap = DrawScene::getInstance()->getSwitchLocMap();
    switchSysIdMap = DrawScene::getInstance()->getSwitchSysIdMap();

    QString id, x, y, name, fromName, toName, fromIp, fromMac, toIp, toMac, fromId, toId, bw, delay, loss, option;
    QPointF position;

    //ask the user to enter the name of his topology.

    QFile xmlFile("/home/comhghall/Final-Year-Project/resources/netanim_topo.xml");
    xmlFile.open(QIODevice::WriteOnly);
    QTextStream outStream(&xmlFile);
    outStream << "<anim ver=\"netanim-3.106\" filetype=\"animation\" >\n";

    for(int i = 0; i < hosts.size(); i++){
        name = hosts.at(i);
        id = QString::number(hostSysIdMap.find(name)->second);
        position = hostLocMap.find(name)->second;
        x = QString::number(position.x());
        y = QString::number(position.y());

        outStream << "<node id=\"" + id + "\" sysId=\"0\" locX=\"" + x + "\" locY=\"" + y + "\" />\n";
        outStream << "<nu p=\"c\" t=\"0\" id=\"" + id + "\" r=\"255\" g=\"0\" b=\"0\" />\n";
    }

    for(int i = 0; i < switches.size(); i++){
        name = switches.at(i);
        id = QString::number(switchSysIdMap.find(name)->second);
        position = switchLocMap.find(name)->second;
        x = QString::number(position.x());
        y = QString::number(position.y());

        outStream << "<node id=\"" + id + "\" sysId=\"0\" locX=\"" + x + "\" locY=\"" + y + "\" />\n";
        outStream << "<nu p=\"c\" t=\"0\" id=\"" + id + "\" r=\"0\" g=\"255\" b=\"0\" />\n";
    }

    for(int i = 0; i < links.size(); i++){
        name = links.at(i);
        toName = name.left(3);
        fromName = name.right(3);
        option = linkOptions.at(i);
        QStringList optionList = option.split(" ", QString::SkipEmptyParts);
        bw = optionList[0];
        delay = optionList[1];
        loss = optionList[2];

        if(toName.at(0) == 'h'){
            toId = QString::number(hostSysIdMap.find(toName)->second);
            toIp = hostIpMap.find(toName)->second;
            toMac = hostMacMap.find(toName)->second;
        }

        else if(toName.at(0) == 's'){
            toId = QString::number(switchSysIdMap.find(toName)->second);
            toIp = "--.--.--";
            toMac = switchMacMap.find(toName)->second;
        }

        if(fromName.at(0) == 'h'){
            fromId = QString::number(hostSysIdMap.find(fromName)->second);
            fromIp = hostIpMap.find(fromName)->second;
            fromMac = hostMacMap.find(fromName)->second;
        }

        else if(fromName.at(0) == 's'){
            fromId = QString::number(switchSysIdMap.find(fromName)->second);
            fromIp = "--.--.--";
            fromMac = switchMacMap.find(fromName)->second;
        }
        outStream << "<link fromId=\"" + fromId + "\" toId=\"" + toId + "\" fd=\"" + fromIp + "~" + fromMac + "\" td=\"" + toIp + "~" + toMac + "\" ld=\"\" />" + bw + " " + delay + " " + loss + "\n";
    }

    outStream << "</anim>";
    xmlFile.close();
}

void
DrawMode::addLinkButtonSlot()
{
    QString to = m_linkToEdit->text();
    QString from = m_linkFromEdit->text();
    QString bandwidth = m_bwEdit->text();
    QString delay = m_delayEdit->text();
    QString loss = m_lossEdit->text();
    to = to.toLower();
    from = from.toLower();
    bandwidth = bandwidth.toLower();
    delay = delay.toLower();
    loss = loss.toLower();
    std::vector<QString> hosts;
    std::vector<QString> switches;
    hosts = DrawScene::getInstance()->getHostVector();
    switches = DrawScene::getInstance()->getSwitchVector();

//    if(to.at(0) != 'h' || to.at(0) != 's'){
        //error incorrect input
//    }

//    if(to.at(0) == 'h' && from.at(0) == 'h'){
        //error can't link host to host
//    }

    std::vector<QString>::iterator foundToHost = std::find(hosts.begin(), hosts.end(), to);
    std::vector<QString>::iterator foundFromHost = std::find(hosts.begin(), hosts.end(), from);
    std::vector<QString>::iterator foundToSwitch = std::find(switches.begin(), switches.end(), to);
    std::vector<QString>::iterator foundFromSwitch = std::find(switches.begin(), switches.end(), from);

    //add check to see if link already exists using link map
    if(foundToSwitch != switches.end() && foundFromSwitch != switches.end()){
        DrawScene::getInstance()->addLink(to, from, bandwidth, delay, loss);
    }

    else if(foundToHost != hosts.end() && foundFromSwitch != switches.end()){
        DrawScene::getInstance()->addLink(to, from, bandwidth, delay, loss);
    }

    else if(foundToSwitch != switches.end() && foundFromHost != hosts.end()){
        DrawScene::getInstance()->addLink(to, from, bandwidth, delay, loss);
    }

    else{
        //error
    }

}

void
DrawMode::runButtonSlot()
{
    std::vector<QString> hosts;
    std::vector<QString> switches;

    hosts = DrawScene::getInstance()->getHostVector();
    switches = DrawScene::getInstance()->getSwitchVector();
    QString pcapFiles = "";
    //Get the user's linux username.
    struct passwd *pwd;
    pwd = getpwuid(getuid());
    const char* linuxUsername = pwd->pw_name;

    for(int i = 0; i < hosts.size(); i++){
        pcapFiles += "/home/" + QString::fromUtf8(linuxUsername) + "/Final-Year-Project/resources/h" + QString::number(i + 1) + ".pcap ";
    }

    for(int i = 0; i < switches.size(); i++){
        pcapFiles += "/home/" + QString::fromUtf8(linuxUsername) + "/Final-Year-Project/resources/s" + QString::number(i + 1) + "-eth0.pcap ";
    }

    char* fileString = new char[pcapFiles.length() + 1];
    strcpy(fileString, pcapFiles.toLatin1().constData());
    string tempNetInitPath = std::string("/home/") + linuxUsername + std::string("/Final-Year-Project/NetInitialiser.py");
    string tempXmlPath = std::string("/home/") + linuxUsername + std::string("/Final-Year-Project/resources/netanim_topo.xml");
    char* netInitPath = strdup(tempNetInitPath.c_str());
    char* xmlPath = strdup(tempXmlPath.c_str());
    char* user = strdup(linuxUsername);

    std::cout << fileString;

    pid_t child_pid;
    char* child_args[] = {"usr/bin/xterm", "-hold", "-e", "/usr/bin/sudo", "/usr/bin/python", netInitPath, "bw", "delay", "loss", xmlPath, user, fileString, NULL};
    int child_status;
    pid_t wait_result;
    child_pid = fork();

    switch(child_pid){
        case -1:
            break;

        case 0:
            execvp("/usr/bin/xterm", child_args);
            abort();

        default:
            wait_result = waitpid(child_pid, &child_status, 0);
            if(wait_result != child_pid){
                //something went wrong
//                m_mybutton->setToolTip("X");
            }

            else{
                //child terminated successfully
//                m_mybutton->setToolTip("Y");
            }
    }

    wait_result = waitpid(child_pid, &child_status, WUNTRACED | WCONTINUED);
    if(wait_result != child_pid){
        //same as above
  //      m_mybutton->setToolTip("Z");
    }

    if(WIFEXITED(child_status)){
        //child's exit code = WEXITSTATUS(child_status);
 //       m_mybutton->setToolTip("A");
        m_runButton->setToolTip("A");
    }
}
}
