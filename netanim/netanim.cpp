/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: John Abraham <john.abraham.in@gmail.com>
 */
#include "netanim.h"
#include "animatormode.h"
#include "statsmode.h"
#include "packetsmode.h"
#include "drawmode.h"
#include "demomode.h"
#include "dirent.h"
#include "string.h"
#include <string>
#ifdef WITH_NS3
#include "designer/designermode.h"
#endif

namespace netanim
{

NetAnim::NetAnim ():
  m_tabWidget (new QTabWidget)
{

  AnimatorMode * animatorTab = AnimatorMode::getInstance ();
  m_tabWidget->addTab (animatorTab->getCentralWidget (), animatorTab->getTabName ());
  m_TabMode[0] = animatorTab;


  StatsMode * statsTab = StatsMode::getInstance ();
  m_tabWidget->addTab (statsTab->getCentralWidget (), statsTab->getTabName ());
  m_TabMode[1] = statsTab;


  PacketsMode * packetsTab = PacketsMode::getInstance ();
  m_tabWidget->addTab (packetsTab->getCentralWidget (), packetsTab->getTabName ());
  m_TabMode[2] = packetsTab;

  DrawMode * drawTab = DrawMode::getInstance();
  m_tabWidget->addTab(drawTab->getCentralWidget(), drawTab->getTabName());
  m_TabMode[3] = drawTab;

  DIR *dir;
  struct dirent *ent;
  int i = 4;
  QString file;

  if ((dir = opendir ("/home/comhghall/Final-Year-Project/demos/")) != NULL) {
    /* print all the files and directories within directory */
    while ((ent = readdir (dir)) != NULL) {
        file = ent->d_name;
        if(file[0] == 'D'){
            DemoMode * demoTab = DemoMode::getInstance();
            demoTab->setTabName(file);
            m_tabWidget->addTab(demoTab->getCentralWidget(), demoTab->getTabName());
            m_TabMode[i] = demoTab;
            std::cout << ent->d_name;
            std::cout << "\n";
            qDebug(demoTab->getTabName().toLatin1());
            i++;
        }
    }
    closedir (dir);
  }

//  DemoMode * demoTab_2 = DemoMode::getInstance();
//  m_tabWidget->addTab(demoTab_2->getCentralWidget(), demoTab_2->getTabName());
//  m_TabMode[i] = demoTab_2;

#ifdef WITH_NS3
  DesignerMode * designerMode = new DesignerMode;
  m_tabWidget->addTab (designerMode->getCentralWidget (), designerMode->getTabName ());
#endif
  QObject::connect (m_tabWidget, SIGNAL (currentChanged (int)), this, SLOT (currentTabChangedSlot (int)));
  m_tabWidget->setCurrentIndex (0);
  QRect geometry = QApplication::desktop ()->screenGeometry ();
  int minimumDimension = std::min (geometry.width (), geometry.height ());
  m_tabWidget->setGeometry (0, 0, minimumDimension, minimumDimension);
  m_tabWidget->showMaximized ();
  m_tabWidget->show ();
  animatorTab->start ();
}


void
NetAnim::currentTabChangedSlot (int currentIndex)
{
  for (TabIndexModeMap_t::const_iterator i = m_TabMode.begin ();
      i != m_TabMode.end ();
      ++i)
    {
      if (currentIndex == i->first)
        {
          i->second->setFocus (true);
          continue;
        }
      i->second->setFocus (false);
    }

}

QTabWidget *
NetAnim::getTabWidget()
{
  return m_tabWidget;
}

} // namespace netanim

