/*Comhghall McKeating 12328401
 * Final Year Project.*/

#include "demowritemode.h"
#include <QTextEdit>
#include <sys/stat.h>
#include <QColorDialog>
#include <QTextStream>
#include <QUrl>
#include <QImageReader>

const QString rsrcPath = "/home/comhghall/Final-Year-Project/netAnim_icons/";

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
//    XmlManager xmlManager;
    QString text = m_textEditor->toPlainText();
    QString html = m_textEditor->toHtml();
    qDebug(html.toLatin1());
    QString demoName = "D_" + m_filenameEdit->text();
    QString htmlTextName = demoName + "_text.html";

    QString fullDirPath = "/home/comhghall/Final-Year-Project/demos/" + demoName;
    QString fullWritepath = fullDirPath + "/" + htmlTextName;
    const char * stdDirPath = fullDirPath.toStdString().c_str();

    mkdir(stdDirPath, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    qDebug(text.toLatin1());
    QFile file(fullWritepath);
    file.open(QIODevice::WriteOnly);
    QTextStream outstream(&file);
    outstream<<html;
    file.close();
//    xmlManager.writeXmlFile(fullWritepath, text);
}

void
DemoWriteMode::addImageButtonSlot()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Select an image"),
                                      ".", tr("Bitmap Files (*.bmp)\n"
                                        "JPEG (*.jpg *jpeg)\n"
                                        "GIF (*.gif)\n"
                                        "PNG (*.png)\n"));
    QUrl Uri ( QString ( "file://%1" ).arg ( file ) );
    QImage image = QImageReader ( file ).read();

    QTextDocument * textDocument = m_textEditor->document();
    textDocument->addResource( QTextDocument::ImageResource, Uri, QVariant ( image ) );
    QTextCursor cursor = m_textEditor->textCursor();
    QTextImageFormat imageFormat;
    imageFormat.setWidth( image.width() );
    imageFormat.setHeight( image.height() );
    imageFormat.setName( Uri.toString() );
    cursor.insertImage(imageFormat);
}

void
DemoWriteMode::setupTextActions()
{
    QToolBar *tb = new QToolBar();
    m_gLayout->addWidget(tb, 0, 0);

    m_addImageButton = new QToolButton;
    m_addImageButton->setText("ADD IMAGE");
    connect (m_addImageButton, SIGNAL(clicked()), this, SLOT (addImageButtonSlot()));
    tb->addWidget(m_addImageButton);

    actionTextBold = new QAction(QIcon::fromTheme("format-text-bold", QIcon(rsrcPath + "/textbold.png")),
                                     tr("&Bold"), this);

    actionTextBold->setShortcut(Qt::CTRL + Qt::Key_B);
    actionTextBold->setPriority(QAction::LowPriority);
    QFont bold;
    bold.setBold(true);
    actionTextBold->setFont(bold);
    connect(actionTextBold, SIGNAL(triggered()), this, SLOT(textBold()));
    tb->addAction(actionTextBold);
    actionTextBold->setCheckable(true);

    actionTextItalic = new QAction(QIcon::fromTheme("format-text-italic",
                                                        QIcon(rsrcPath + "/textitalic.png")),
                                       tr("&Italic"), this);
    actionTextItalic->setPriority(QAction::LowPriority);
    actionTextItalic->setShortcut(Qt::CTRL + Qt::Key_I);
    QFont italic;
    italic.setItalic(true);
    actionTextItalic->setFont(italic);
    connect(actionTextItalic, SIGNAL(triggered()), this, SLOT(textItalic()));
    tb->addAction(actionTextItalic);
//    menu->addAction(actionTextItalic);
    actionTextItalic->setCheckable(true);

    actionTextUnderline = new QAction(QIcon::fromTheme("format-text-underline",
                                                           QIcon(rsrcPath + "/textunder.png")),
                                          tr("&Underline"), this);
    actionTextUnderline->setShortcut(Qt::CTRL + Qt::Key_U);
    actionTextUnderline->setPriority(QAction::LowPriority);
    QFont underline;
    underline.setUnderline(true);
    actionTextUnderline->setFont(underline);
    connect(actionTextUnderline, SIGNAL(triggered()), this, SLOT(textUnderline()));
    tb->addAction(actionTextUnderline);
//    menu->addAction(actionTextUnderline);
    actionTextUnderline->setCheckable(true);

    QPixmap pix(16, 16);
    pix.fill(Qt::black);
    actionTextColor = new QAction(pix, tr("&Color..."), this);
    connect(actionTextColor, SIGNAL(triggered()), this, SLOT(textColor()));
    tb->addAction(actionTextColor);
//    menu->addAction(actionTextColor);

    comboFont = new QFontComboBox(tb);
    tb->addWidget(comboFont);
    connect(comboFont, SIGNAL(activated(QString)), this, SLOT(textFamily(QString)));

    comboSize = new QComboBox(tb);
    comboSize->setObjectName("comboSize");
    tb->addWidget(comboSize);
    comboSize->setEditable(true);

    QFontDatabase db;
    foreach(int size, db.standardSizes())
    comboSize->addItem(QString::number(size));

    connect(comboSize, SIGNAL(activated(QString)), this, SLOT(textSize(QString)));
    comboSize->setCurrentIndex(comboSize->findText(QString::number(QApplication::font()
                                                                       .pointSize())));
}

void
DemoWriteMode::textBold()
{
    QTextCharFormat fmt;
    fmt.setFontWeight(actionTextBold->isChecked() ? QFont::Bold : QFont::Normal);
    mergeFormatOnWordOrSelection(fmt);
}

void
DemoWriteMode::textColor()
{
   QColor col = QColorDialog::getColor(m_textEditor->textColor(), this);
   if (!col.isValid())
       return;
   QTextCharFormat fmt;
   fmt.setForeground(col);
   mergeFormatOnWordOrSelection(fmt);
   colorChanged(col);
}

void
DemoWriteMode::textItalic()
{
    QTextCharFormat fmt;
    fmt.setFontItalic(actionTextItalic->isChecked());
    mergeFormatOnWordOrSelection(fmt);
}

void
DemoWriteMode::textSize(const QString &p)
{
    qreal pointSize = p.toFloat();
    if (p.toFloat() > 0) {
        QTextCharFormat fmt;
        fmt.setFontPointSize(pointSize);
        mergeFormatOnWordOrSelection(fmt);
    }
}

void
DemoWriteMode::textUnderline()
{
    QTextCharFormat fmt;
    fmt.setFontUnderline(actionTextUnderline->isChecked());
    mergeFormatOnWordOrSelection(fmt);
}

void
DemoWriteMode::textFamily(const QString &f)
{
    QTextCharFormat fmt;
    fmt.setFontFamily(f);
    mergeFormatOnWordOrSelection(fmt);
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
