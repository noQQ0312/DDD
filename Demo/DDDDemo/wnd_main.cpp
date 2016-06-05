#include "wnd_main.h"
#include "ui_wnd_main.h"

#include "edt_custom.h"

#include <QToolBar>
#include <QFontComboBox>
#include <QFontDialog>
#include <QToolButton>
#include <QComboBox>
#include <QDebug>
#include <QFontDatabase>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initControls();
    layoutControls();

    connect( ui->txtEdt, SIGNAL(currentCharFormatChanged( QTextCharFormat)), this, SLOT(onTextCharFormatChanged(QTextCharFormat)) );

    QFont fnt = currentFont();
    m_pCmbFont->setCurrentText( fnt.family() );
    m_pCmbFontPointSize->setCurrentText( QString::number( fnt.pointSize() ) );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MainWindow::~MainWindow()
{
    if ( m_pCmbFontPointSize ) {
        delete m_pCmbFontPointSize;
        m_pCmbFontPointSize = 0;
    }
    if ( m_pCmbFont ) {
        delete m_pCmbFont;
        m_pCmbFont = 0;
    }

    delete ui;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::initControls()
{
    QToolBar *pFormatBar = createFormatToolBar();
    addToolBar( pFormatBar );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::layoutControls()
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
QToolBar* MainWindow::createFormatToolBar()
{
    QToolBar *pFormatBar = new QToolBar();
    pFormatBar->setWindowTitle( "Format Bar" );

    m_pCmbFont = new QFontComboBox;
    m_pCmbFont->setEditable( false );
    m_pCmbFont->setFocusPolicy( Qt::NoFocus );
    m_pCmbFontPointSize = new QComboBox;
    updateFontPointSize( m_pCmbFont->currentText() );
    m_pCmbFontPointSize->setFocusPolicy( Qt::NoFocus );
    QToolButton *pBtnMoreOptions = new QToolButton;
    pBtnMoreOptions->setText( "More..." );
    pBtnMoreOptions->setStyleSheet( "border: 1px solid #000000" );
    pBtnMoreOptions->setFixedHeight( 20 );
    pBtnMoreOptions->setFocusPolicy( Qt::NoFocus );

    pFormatBar->addWidget( m_pCmbFont );
    pFormatBar->addWidget( m_pCmbFontPointSize );
    pFormatBar->addWidget( pBtnMoreOptions );

    connect( m_pCmbFont, SIGNAL(currentIndexChanged(int)), this, SLOT(onFontFamilyChanged()) );
    connect( m_pCmbFontPointSize, SIGNAL(currentIndexChanged(int)), this, SLOT(onFontPointSizeChanged()) );
    connect( pBtnMoreOptions, SIGNAL(clicked()), this, SLOT(onFormatMoreBtnClicked()) );

    return pFormatBar;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::updateFontPointSize( const QString & strFamily, const QString & strStyleName )
{
    QFontDatabase fdb;
    QList<int> lsPointSize = fdb.pointSizes( strFamily, strStyleName );

    QString strOriginSelected = m_pCmbFontPointSize->currentText();
    m_pCmbFontPointSize->blockSignals( true );
    m_pCmbFontPointSize->clear();
    int iSizeCnt = lsPointSize.count();
    for ( int iSizeIndex = 0; iSizeIndex < iSizeCnt; iSizeIndex++ ) {
        m_pCmbFontPointSize->addItem( QString::number( lsPointSize.at( iSizeIndex ) ) );
    }
    m_pCmbFontPointSize->setCurrentIndex( -1 );
    m_pCmbFontPointSize->blockSignals( false );

    if ( iSizeCnt > 0 ) {
        int iCurSelectedIndex = m_pCmbFontPointSize->findText( strOriginSelected );
        m_pCmbFontPointSize->setCurrentIndex( iCurSelectedIndex != -1 ? iCurSelectedIndex : 0 );
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::onFormatMoreBtnClicked()
{
    QFontDialog cDlgFont(  currentFont(), this );
    if ( QDialog::Accepted == cDlgFont.exec() ) {
        setCurrentFont( cDlgFont.selectedFont() );
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::onFontFamilyChanged()
{
    updateFontPointSize( m_pCmbFont->currentText() );

    QFont fnt = currentFont();
    fnt.setFamily( m_pCmbFont->currentText() );
    fnt.setPointSize( m_pCmbFontPointSize->currentText().toInt() );
    setCurrentFont( fnt );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::onFontPointSizeChanged()
{
    QFont fnt = currentFont();
    fnt.setPointSize( m_pCmbFontPointSize->currentText().toInt() );
    setCurrentFont( fnt );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::onTextCharFormatChanged( const QTextCharFormat & sFormat )
{
    QFont fnt = sFormat.font();
    m_pCmbFont->setCurrentText( fnt.family() );
    m_pCmbFontPointSize->setCurrentText(  QString::number( fnt.pointSize() ) );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
QFont MainWindow::currentFont()
{
    return ui->txtEdt->currentFont();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::setCurrentFont( const QFont & cFnt )
{
    ui->txtEdt->setCurrentFont( cFnt );
}
