#ifndef __MESSAGEBOX_H__
#define __MESSAGEBOX_H__

#include "define.h"
#include "ui_msgbox-dlg.h"

typedef enum
{
	UI_MSGRET_ESC,
	UI_MSGRET_OK,
	UI_MSGRET_TIMEOUT
}T_UI_MSGRET;

class CMessageBox : public QDialog
{
	Q_OBJECT

public:
	CMessageBox(QWidget *parent = NULL);
	~CMessageBox() {};
	void SetIcon(QString szIconFile);
	void SetText(QString szText);
	void SetType(int nType);
	int  MsgBoxProc(unsigned int nTimeout = 0xFFFFFFFF);

public Q_SLOTS:
	;
	void OnBtnOK();
	void OnBtnESC();

private:
	bool m_bTerminateFlag;
	GUI_DLG_DEFINE(Ui::MsgboxDlg);
	int m_nRet;
};

#endif /*__MESSAGEBOX_H__*/
