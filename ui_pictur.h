#ifndef UI_PICTUR_H
#define UI_PICTUR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

class Ui_Form
{
public:
    QLabel *picture;
    QPushButton *ok;
    QPushButton *pushButton_2;

    void setupUi(QWidget *Form)
    {
    Form->setObjectName(QString::fromUtf8("Form"));
    Form->resize(QSize(480, 272).expandedTo(Form->minimumSizeHint()));
    picture = new QLabel(Form);
    picture->setObjectName(QString::fromUtf8("picture"));
    picture->setGeometry(QRect(70, 20, 311, 141));
    ok = new QPushButton(Form);
    ok->setObjectName(QString::fromUtf8("ok"));
    ok->setGeometry(QRect(90, 210, 101, 31));
    pushButton_2 = new QPushButton(Form);
    pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
    pushButton_2->setGeometry(QRect(250, 210, 91, 31));
    retranslateUi(Form);

    QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
    Form->setWindowTitle(QApplication::translate("Form", "Form", 0, QApplication::UnicodeUTF8));
    picture->setText(QApplication::translate("Form", "TextLabel", 0, QApplication::UnicodeUTF8));
    ok->setText(QApplication::translate("Form", "OK", 0, QApplication::UnicodeUTF8));
    pushButton_2->setText(QApplication::translate("Form", "Cancle", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(Form);
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

#endif // UI_PICTUR_H
