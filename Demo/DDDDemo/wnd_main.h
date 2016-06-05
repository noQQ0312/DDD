#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

QT_BEGIN_NAMESPACE
class QToolBar;
class CCustomTextEdit;
class QComboBox;
class QFontComboBox;
class QTextCharFormat;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void initControls();
    void layoutControls();
    QToolBar* createFormatToolBar();

    void updateFontPointSize( const QString & strFamily, const QString & strStyleName = QString() );

private slots:
    // 字体相关
    void onFormatMoreBtnClicked();
    void onFontFamilyChanged();
    void onFontPointSizeChanged();

    void onTextCharFormatChanged( const QTextCharFormat & sFormat );

    QFont currentFont();
    void setCurrentFont( const QFont & cFnt );

private:
    Ui::MainWindow *ui;

    QComboBox *m_pCmbFontPointSize;
    QFontComboBox *m_pCmbFont;
};

#endif // MAINWINDOW_H
