#include "mylineedit.h"

MyLineEdit::MyLineEdit(QWidget *parent):QLineEdit(parent)
{

}
void MyLineEdit::focusInEvent(QFocusEvent *e)
{
       //this->insert("i");
       emit FocusIN();
}

void MyLineEdit::focusOutEvent(QFocusEvent *e)
{
       //this->insert("o");
       emit FocusOUT();
}

