#ifndef UI_SEARCH_2D_LOG_H
#define UI_SEARCH_2D_LOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

class Ui_LogSearch
{
public:
    QLabel *lblBackground;
    QLabel *lblTitleBackground;
    QLabel *lblTitleText;
    QLabel *lblTitleIcon;
    QLabel *lblStatusIcon;
    QLabel *lblStatusText;
    QPushButton *btnESC;
    QLabel *lblName;
    QLineEdit *txtTo;
    QLabel *lblStatus;
    QPushButton *btnOK;
    QLabel *lblID;
    QLabel *lblTo;
    QComboBox *comboDate;
    QLabel *lblDate;
    QLineEdit *txtFrom;
    QLabel *lblFrom;
    QLineEdit *txtName;
    QLineEdit *txtID;
    QLabel *lblBackgroundFrame;
    QLabel *lblEsc;
    QLabel *lblButtonBackgroud;
    QLabel *lblButtonTitle;

    void setupUi(QDialog *LogSearch)
    {
    LogSearch->setObjectName(QString::fromUtf8("LogSearch"));
    LogSearch->resize(QSize(480, 272).expandedTo(LogSearch->minimumSizeHint()));
    lblBackground = new QLabel(LogSearch);
    lblBackground->setObjectName(QString::fromUtf8("lblBackground"));
    lblBackground->setGeometry(QRect(0, 0, 480, 272));
    lblBackground->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bg-main.png")));
    lblTitleBackground = new QLabel(LogSearch);
    lblTitleBackground->setObjectName(QString::fromUtf8("lblTitleBackground"));
    lblTitleBackground->setGeometry(QRect(0, 0, 400, 34));
    lblTitleBackground->setPixmap(QPixmap(QString::fromUtf8(":/images/res/title-1.png")));
    lblTitleText = new QLabel(LogSearch);
    lblTitleText->setObjectName(QString::fromUtf8("lblTitleText"));
    lblTitleText->setGeometry(QRect(40, 3, 273, 28));
    lblTitleIcon = new QLabel(LogSearch);
    lblTitleIcon->setObjectName(QString::fromUtf8("lblTitleIcon"));
    lblTitleIcon->setGeometry(QRect(9, 5, 26, 26));
    lblTitleIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/SEARCH_GLOG.png")));
    lblTitleIcon->setScaledContents(true);
    lblStatusIcon = new QLabel(LogSearch);
    lblStatusIcon->setObjectName(QString::fromUtf8("lblStatusIcon"));
    lblStatusIcon->setGeometry(QRect(20, 205, 16, 16));
    lblStatusIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-help.png")));
    lblStatusText = new QLabel(LogSearch);
    lblStatusText->setObjectName(QString::fromUtf8("lblStatusText"));
    lblStatusText->setGeometry(QRect(40, 200, 270, 25));
    btnESC = new QPushButton(LogSearch);
    btnESC->setObjectName(QString::fromUtf8("btnESC"));
    btnESC->setGeometry(QRect(380, 200, 75, 41));
    lblName = new QLabel(LogSearch);
    lblName->setObjectName(QString::fromUtf8("lblName"));
    lblName->setGeometry(QRect(230, 150, 50, 21));
    txtTo = new QLineEdit(LogSearch);
    txtTo->setObjectName(QString::fromUtf8("txtTo"));
    txtTo->setEnabled(false);
    txtTo->setGeometry(QRect(70, 129, 91, 20));
    lblStatus = new QLabel(LogSearch);
    lblStatus->setObjectName(QString::fromUtf8("lblStatus"));
    lblStatus->setGeometry(QRect(40, 50, 279, 21));
    lblStatus->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
    btnOK = new QPushButton(LogSearch);
    btnOK->setObjectName(QString::fromUtf8("btnOK"));
    btnOK->setGeometry(QRect(240, 200, 75, 41));
    lblID = new QLabel(LogSearch);
    lblID->setObjectName(QString::fromUtf8("lblID"));
    lblID->setGeometry(QRect(240, 100, 40, 21));
    lblTo = new QLabel(LogSearch);
    lblTo->setObjectName(QString::fromUtf8("lblTo"));
    lblTo->setGeometry(QRect(20, 129, 40, 21));
    comboDate = new QComboBox(LogSearch);
    comboDate->setObjectName(QString::fromUtf8("comboDate"));
    comboDate->setGeometry(QRect(70, 72, 231, 21));
    lblDate = new QLabel(LogSearch);
    lblDate->setObjectName(QString::fromUtf8("lblDate"));
    lblDate->setGeometry(QRect(20, 72, 40, 16));
    txtFrom = new QLineEdit(LogSearch);
    txtFrom->setObjectName(QString::fromUtf8("txtFrom"));
    txtFrom->setEnabled(false);
    txtFrom->setGeometry(QRect(70, 101, 91, 20));
    lblFrom = new QLabel(LogSearch);
    lblFrom->setObjectName(QString::fromUtf8("lblFrom"));
    lblFrom->setGeometry(QRect(20, 99, 40, 21));
    txtName = new QLineEdit(LogSearch);
    txtName->setObjectName(QString::fromUtf8("txtName"));
    txtName->setGeometry(QRect(290, 150, 131, 20));
    txtName->setMaxLength(8);
    txtName->setAlignment(Qt::AlignCenter);
    txtID = new QLineEdit(LogSearch);
    txtID->setObjectName(QString::fromUtf8("txtID"));
    txtID->setGeometry(QRect(290, 100, 131, 20));
    txtID->setContextMenuPolicy(Qt::DefaultContextMenu);
    txtID->setMaxLength(9);
    txtID->setAlignment(Qt::AlignCenter);
    lblBackgroundFrame = new QLabel(LogSearch);
    lblBackgroundFrame->setObjectName(QString::fromUtf8("lblBackgroundFrame"));
    lblBackgroundFrame->setGeometry(QRect(12, 34, 456, 238));
    lblBackgroundFrame->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bg-menu.png")));
    lblEsc = new QLabel(LogSearch);
    lblEsc->setObjectName(QString::fromUtf8("lblEsc"));
    lblEsc->setGeometry(QRect(400, 0, 80, 34));
    lblEsc->setPixmap(QPixmap(QString::fromUtf8(":/images/res/esc.png")));
    lblButtonBackgroud = new QLabel(LogSearch);
    lblButtonBackgroud->setObjectName(QString::fromUtf8("lblButtonBackgroud"));
    lblButtonBackgroud->setGeometry(QRect(330, 150, 80, 40));
    lblButtonBackgroud->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bg-button.png")));
    lblButtonTitle = new QLabel(LogSearch);
    lblButtonTitle->setObjectName(QString::fromUtf8("lblButtonTitle"));
    lblButtonTitle->setGeometry(QRect(345, 156, 50, 28));
    lblButtonTitle->setAlignment(Qt::AlignCenter);
    QWidget::setTabOrder(comboDate, txtFrom);
    QWidget::setTabOrder(txtFrom, txtTo);
    QWidget::setTabOrder(txtTo, txtID);
    QWidget::setTabOrder(txtID, txtName);
    QWidget::setTabOrder(txtName, btnOK);
    QWidget::setTabOrder(btnOK, btnESC);
    retranslateUi(LogSearch);

    QMetaObject::connectSlotsByName(LogSearch);
    } // setupUi

    void retranslateUi(QDialog *LogSearch)
    {
    LogSearch->setWindowTitle(QApplication::translate("LogSearch", "Dialog", 0, QApplication::UnicodeUTF8));
    lblBackground->setText(QApplication::translate("LogSearch", "", 0, QApplication::UnicodeUTF8));
    lblTitleBackground->setText(QApplication::translate("LogSearch", "", 0, QApplication::UnicodeUTF8));
    lblTitleText->setText(QApplication::translate("LogSearch", "Log Search", 0, QApplication::UnicodeUTF8));
    lblTitleIcon->setText(QApplication::translate("LogSearch", "", 0, QApplication::UnicodeUTF8));
    lblStatusIcon->setText(QApplication::translate("LogSearch", "", 0, QApplication::UnicodeUTF8));
    lblStatusText->setText(QApplication::translate("LogSearch", "Use Arrow & OK, ESC for return, OK for T9Input", 0, QApplication::UnicodeUTF8));
    btnESC->setText(QApplication::translate("LogSearch", "ESC", 0, QApplication::UnicodeUTF8));
    lblName->setText(QApplication::translate("LogSearch", "Name", 0, QApplication::UnicodeUTF8));
    lblStatus->setText(QApplication::translate("LogSearch", "Press finger or input card", 0, QApplication::UnicodeUTF8));
    btnOK->setText(QApplication::translate("LogSearch", "Search", 0, QApplication::UnicodeUTF8));
    lblID->setText(QApplication::translate("LogSearch", "ID", 0, QApplication::UnicodeUTF8));
    lblTo->setText(QApplication::translate("LogSearch", "to", 0, QApplication::UnicodeUTF8));
    comboDate->clear();
    comboDate->addItem(QApplication::translate("LogSearch", "All", 0, QApplication::UnicodeUTF8));
    comboDate->addItem(QApplication::translate("LogSearch", "Last Week", 0, QApplication::UnicodeUTF8));
    comboDate->addItem(QApplication::translate("LogSearch", "Past Month", 0, QApplication::UnicodeUTF8));
    comboDate->addItem(QApplication::translate("LogSearch", "Specify Date", 0, QApplication::UnicodeUTF8));
    lblDate->setText(QApplication::translate("LogSearch", "Date", 0, QApplication::UnicodeUTF8));
    lblFrom->setText(QApplication::translate("LogSearch", "from", 0, QApplication::UnicodeUTF8));
    lblBackgroundFrame->setText(QApplication::translate("LogSearch", "", 0, QApplication::UnicodeUTF8));
    lblEsc->setText(QApplication::translate("LogSearch", "", 0, QApplication::UnicodeUTF8));
    lblButtonBackgroud->setText(QApplication::translate("LogSearch", "", 0, QApplication::UnicodeUTF8));
    lblButtonTitle->setText(QApplication::translate("LogSearch", "Search", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(LogSearch);
    } // retranslateUi

};

namespace Ui {
    class LogSearch: public Ui_LogSearch {};
} // namespace Ui

#endif // UI_SEARCH_2D_LOG_H
