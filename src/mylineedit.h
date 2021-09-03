#ifndef MYLINEEDIT_H
#define MYLINEEDIT_H
#include <QLineEdit>

class MyLineEdit: public QLineEdit
{
    Q_OBJECT
public:
           MyLineEdit(QWidget *parent=nullptr);
protected:
      virtual void focusInEvent(QFocusEvent *e);
      virtual void focusOutEvent(QFocusEvent *e);
signals:
      void FocusIN();
      void FocusOUT();

};

#endif // MYLINEEDIT_H
