#ifndef CCUSTOMTEXTEDIT_H
#define CCUSTOMTEXTEDIT_H

#include <QTextEdit>

class CCustomTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit CCustomTextEdit(QWidget *parent = 0);
    explicit CCustomTextEdit( const QString &text, QWidget *parent = 0 );
    ~CCustomTextEdit();

signals:

public slots:
};

#endif // CCUSTOMTEXTEDIT_H
