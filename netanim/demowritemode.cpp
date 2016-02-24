/*Comhghall McKeating 12328401
 * Final Year Project.*/

#include "demowritemode.h"
#include "xmlmanager.h"
#include <QTextEdit>
#include <sys/stat.h>

#define SSTR( x ) dynamic_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

namespace netanim
{

DemoWriteMode * pDemoWriteMode = 0;

DemoWriteMode *
DemoWriteMode::getInstance()
{
    pDemoWriteMode = new DemoWriteMode;
    return pDemoWriteMode;
}

DemoWriteMode::DemoWriteMode()
{
    init();
}

void
DemoWriteMode::setFocus(bool focus)
{
    if(focus)
    {
        //reload
    }
}

QString
DemoWriteMode::getTabName()
{
    return "+";
}

void
DemoWriteMode::setTabName(QString name)
{
    m_tabname = name;
}

QWidget *
DemoWriteMode::getCentralWidget()
{
    return m_centralWidget;
}

void
DemoWriteMode::init()
{
    m_state = INIT;
    m_gLayout = new QGridLayout;
    m_textEditor = new QTextEdit;
    setupTextActions();

    connect(m_textEditor, SIGNAL(currentCharFormatChanged(QTextCharFormat)),
                this, SLOT(currentCharFormatChanged(QTextCharFormat)));

    QFont textFont("Helvetica");
    textFont.setStyleHint(QFont::SansSerif);
    m_textEditor->setFont(textFont);
//    fontChanged(m_textEditor->font());
//    colorChanged(m_textEditor->textColor());

    m_saveButton = new QToolButton;
    m_saveButton->setText("SAVE");
    connect(m_saveButton, SIGNAL(clicked()), this, SLOT(saveButtonSlot()));

    m_filenameEdit = new QLineEdit;

    QLabel * filenameEditLabel = new QLabel;
    filenameEditLabel->setText("DEMO NAME:");

    m_gLayout->addWidget(m_textEditor, 1, 0);
    m_gLayout->addWidget(m_saveButton, 4, 0);
    m_gLayout->addWidget(filenameEditLabel, 2, 0);
    m_gLayout->addWidget(m_filenameEdit, 3, 0);

    m_centralWidget = new QWidget;
    m_centralWidget->setLayout(m_gLayout);

    m_minPoint.setX(0.0);
    m_minPoint.setY(0.0);
    m_maxPoint.setX(1000.0);
    m_maxPoint.setY(1000.0);
    setWindowTitle("NetAnim");
}

void
DemoWriteMode::saveButtonSlot()
{
    XmlManager xmlManager;
    QString text = m_textEditor->toPlainText();
    QString demoName = "D_" + m_filenameEdit->text();
    QString xmlTextName = demoName + "_text.xml";

    QString fullDirPath = "/home/comhghall/Final-Year-Project/demos/" + demoName;
    QString fullWritepath = fullDirPath + "/" + xmlTextName;
    const char * stdDirPath = fullDirPath.toStdString().c_str();

    mkdir(stdDirPath, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    qDebug(text.toLatin1());
    xmlManager.writeXmlFile(fullWritepath, text);
}

void
DemoWriteMode::addImageButtonSlot()
{

}

void
DemoWriteMode::setupTextActions()
{
    QToolBar *tb = new QToolBar();
    m_gLayout->addWidget(tb, 0, 0);

    QLabel * boldLabel = new QLabel();
    boldLabel->setText("B");
    actionTextBold = new QAction(boldLabel);

    actionTextBold->setShortcut(Qt::CTRL + Qt::Key_B);
    actionTextBold->setPriority(QAction::LowPriority);
    QFont bold;
    bold.setBold(true);
    actionTextBold->setFont(bold);
    connect(actionTextBold, SIGNAL(triggered()), this, SLOT(textBold()));
    tb->addAction(actionTextBold);
    actionTextBold->setCheckable(true);
}

void
DemoWriteMode::textBold()
{
    QTextCharFormat fmt;
    fmt.setFontWeight(actionTextBold->isChecked() ? QFont::Bold : QFont::Normal);
    mergeFormatOnWordOrSelection(fmt);
}

void
DemoWriteMode::textColour()
{

}

void
DemoWriteMode::textItalic()
{

}

void
DemoWriteMode::textSize()
{

}

void
DemoWriteMode::textUnderline()
{

}

void
DemoWriteMode::currentCharFormatChanged(const QTextCharFormat &format)
{
    fontChanged(format.font());
    colorChanged(format.foreground().color());
}

void
DemoWriteMode::mergeFormatOnWordOrSelection(const QTextCharFormat &format)
{
    QTextCursor cursor = m_textEditor->textCursor();
    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);
    cursor.mergeCharFormat(format);
    m_textEditor->mergeCurrentCharFormat(format);
}

void
DemoWriteMode::fontChanged(const QFont &f)
{
    comboFont->setCurrentIndex(comboFont->findText(QFontInfo(f).family()));
    comboSize->setCurrentIndex(comboSize->findText(QString::number(f.pointSize())));
    actionTextBold->setChecked(f.bold());
    actionTextItalic->setChecked(f.italic());
    actionTextUnderline->setChecked(f.underline());
}

void
DemoWriteMode::colorChanged(const QColor &c)
{
    QPixmap pix(16, 16);
    pix.fill(c);
    actionTextColor->setIcon(pix);
}


} //namespace netanim
