#include "../precomp.h"
#include "Menu.h"
#include "MainWindow.h"
#include "UserManage.h"
#include "SystemManage.h"
#include <QtGui/QPainter>
#include <QtGui/QPixmap>
#include <QtGui/QPainterPath>
#include "../style/customstyle.h"

extern CMainWindow *g_MainWindow;

extern int nBackgroupIconFile;   

int uiSelftestLcd(DWORD dwTimeout = -1UL);
int uiProcBoxDate(QWidget* parent, int x, int y, int cx, int cy, BOOL* pbRet, int nInitial, int nFormat = 0, BOOL bKeyCheck = FALSE, BOOL bAutoSize = TRUE);
int uiProcBoxDaylight(QWidget* parent, int x, int y, int cx, int cy, BOOL* pbRet, int nInitial, int nFormat = 0, BOOL bKeyCheck = FALSE, BOOL bAutoSize = TRUE);  //xf 091120
void uiEnrollSetTitle(QLabel *pTitlebar);
BOOL uiEnrollUserInfo(USER_INFO *pUserInfo);
void uiProcEnroll(USER_INFO *pUserInfo, int nStr);
BOOL uiProcEnrollDelete(UINT64 nID, int nStr);
//////////////////////////////////////////////////////////////////////////
static int __MENU_ICON_COL_CNT = 3;        
static int __MENU_ICON_ITEM_SIZE = 105;     
static int nLanguage = 0;

#define MENUITEM_REPORT_SIZE_X  200
#define MENUITEM_REPORT_SIZE_Y  50


#define MENUITEM_COLS	(__MENU_ICON_COL_CNT)
#define MENUITEM_ROWS	 5  
#define REPORTITEM_COLS	 2  
#define REPORTITEM_ROWS	 4  
#define MENUITEM_ICONSTYLE_SIZE (__MENU_ICON_ITEM_SIZE) /*Imagesize: 48X48*/
#define RESOURCE_PATH	GUI_RESOURCE_PATH
#define SELECTED_ITEM_FILENAME "selected-item.png"
#define SCROLL_BG_FILENAME		"scroll-bg.png"
#define SCROLL_ITEM_FILENAME	"scroll-item.png"

#define MENU_PEN_COLOR			FOREGROUND_COLOR
#define MENU_ITEM_SELET_COLOR	QColor(255,255,0)

#define MENU_ICON_TOPMARGIN		10       
#define MENU_REPORT_LEFTMARGIN	5    
#define MENU_REPORT_RIGHTMARGIN	5    
#define MENU_REPORT_UPMARGIN    10   
#define MENU_ICON_DRAW_NUMBER	TRUE

#define ENROLLMENU_ROWCOUNT		3
#define ENROLLMENU_ROWHEIGHT	50
#define ENROLLMENU_COLWIDTH		((w - MENU_REPORT_LEFTMARGIN*2) >> 1)
#define ENROLLMENU_ICONSIZE		24

extern unsigned int nTouchX, nTouchY, nTouchPress;      
//////////////////////////////////////////////////////////////////////////
static const char * const __RIGHT_ARROW[] =
{
	"4 7 2 1",
	"   c None",
	"*  c #064CA4",
	"*   ",
	"**  ",
	"*** ",
	"****",
	"*** ",
	"**  ",
	"*   "
};

void uiProcBoxWrapper(BOOL bEventHooked, BOOL bStart)
{
	static QWidget* pFocusWidget = NULL;

	if (!bEventHooked)
	{
		if (bStart)
			pFocusWidget = qApp->focusWidget();
		else
		{
			if (pFocusWidget)
				pFocusWidget->setFocus(Qt::MouseFocusReason);
			pFocusWidget = NULL;
		}
	}
}

//////////////////////////////////////////////////////////////////////////
void uiProcMakeString(char *szBuf, int *nValueList, int nCount, int *Lengths, int index, int i_length, char split)
{
	int i, j;
	int len;
	char FORMAT[16];

	szBuf[0] = 0;

	for (i=0; i<nCount; i++)
	{
		len = strlen(szBuf);
		sprintf(FORMAT, "%c0%dd", '%', Lengths[i]);
		sprintf(&szBuf[len], FORMAT, nValueList[i]);
		if (i == index)
		{
			for (j = 0; j < Lengths[i] - i_length; j++)
			{
				szBuf[len + j] = ' ';
			}
		}
		if (split && i < nCount - 1)
			sprintf(&szBuf[strlen(szBuf)], "%c", split);
	}
}

//////////////////////////////////////////////////////////////////////////
int uiProcBoxSelect(QWidget *pWnd, int x, int y, int w, int h, BOOL *pbRet, int nValue, int from, int to, QStringList *pStrList = NULL, BOOL bResize = TRUE)
{
	uiProcBoxWrapper(FALSE, TRUE);

	int x1, y1, w1, h1;  
	int nRet = nValue;
	int nKey;
	int nRealWidth = 0;
	QComboBox combo(pWnd);
	QPalette pal = combo.palette();

	pal.setColor(QPalette::All, QPalette::Text, FOREGROUND_COLOR);
	pal.setBrush(QPalette::Base, QBrush(QColor(59, 129, 212)));
	combo.setPalette(pal);

	for (int i=from; i<=to; i++)
	{
		QString szItem = (pStrList?pStrList->value(i):UISTR(i));
		combo.addItem(szItem);
		nRealWidth = MAX(nRealWidth, pWnd->fontMetrics().width(szItem));
	}
	if (nValue < 0)
		combo.setCurrentIndex(0);
	else
		combo.setCurrentIndex(nValue);

	x1 = x; y1 = y; w1 = w; h1 = h;   

	if (bResize)
	{
		nRealWidth += 50;
		x = x + w - nRealWidth;
		w = nRealWidth;
	}
	combo.setGeometry(x, y, w, h);
	combo.setFocus(Qt::MouseFocusReason);
	combo.show();

	w1 = w1 - w; h1 = h;  

	*pbRet = FALSE;
	while (uiTimeIsTimeout() == FALSE)
	{
		POST_EVENTS();
		DM9000_Check();

		nKey = uiKeyGetKey();
		if (nKey == UIKEY_OK)
		{
			nRet = combo.currentIndex();
			*pbRet = TRUE;
			break;
		}
		else if (nKey == UIKEY_ESC)
		{
			*pbRet = FALSE;
			break;
		}
		if(nKey == UIKEY_UP)
		{
            nRet = combo.currentIndex();
			*pbRet = TRUE;
			break;
		}
		if(nKey == UIKEY_DOWN)
		{
            nRet = combo.currentIndex();
			*pbRet = TRUE;
			break;
		} 
        if(nKey == UIKEY_POWER)  
		{
			if(combo.currentIndex()== combo.count()-1)
				combo.setCurrentIndex(0);
			else
				combo.setCurrentIndex(combo.currentIndex()+1);   
		} 

		if ((nTouchX >= x) && (nTouchX <= (x+w)) && (nTouchY >= y) && (nTouchY <= (y+h)))  
		{
            if(combo.currentIndex()== combo.count()-1)
				combo.setCurrentIndex(0);
			else
				combo.setCurrentIndex(combo.currentIndex()+1);   
		}
		if ((nTouchX >= x1) && (nTouchX <= (x1+w1)) && (nTouchY >= y1) && (nTouchY <= (y1+h1)))  
		{
           	nRet = combo.currentIndex();
			*pbRet = TRUE;
			break;
		}
	}

	uiProcBoxWrapper(FALSE, FALSE);
	return nRet;

}

int uiProcBoxNumber(QWidget* parent, int x, int y, int cx, int cy,
					BOOL* pbRet, int nInitial, int nMin, int nMax, BOOL b0isNo,
					int nUnitStr, int nKeyFrom = 0, int nKeyTo = 9, BOOL bAutoMinMaxSel = TRUE,
					Qt::Alignment align = Qt::AlignVCenter | Qt::AlignRight)
{
	uiProcBoxWrapper(FALSE, TRUE);

	int nRet = nInitial;
  
	*pbRet = FALSE;
	nRet = DIALOGBOX_RETNUM(CInputUserID);
	if (nRet >= 0)
	{
		 *pbRet = TRUE;
         if (nRet < nMin && bAutoMinMaxSel)
			 nRet = nMin;
		 if (nRet > nMax && bAutoMinMaxSel)
			 nRet = nMax;
	}
	else nRet = nInitial;

	uiProcBoxWrapper(FALSE, FALSE);
	return nRet;
}

char* uiProcBoxString(QWidget* parent, int x, int y, int cx, int cy,
					BOOL* pbRet, char *szInitial, int nMaxLen, int nKeyFrom = 0, int nKeyTo = 9)
{
	uiProcBoxWrapper(FALSE, TRUE);

	int i, nRet = 0;
	char szRet[32];
	memset(szRet, 0, sizeof(szRet));
	strcpy(szRet, szInitial);
  
	*pbRet = FALSE;
	nRet = DIALOGBOX_RETNUM(CInputUserID);
	if (nRet >= 0 && nRet <= 999999 )
	{
		*pbRet = TRUE;
		sprintf(szRet, "%d", nRet);
	}

	uiProcBoxWrapper(FALSE, FALSE);
	return szRet;
}

int uiProcBoxIPAddress(QWidget* parent, int x, int y, int cx, int cy, BOOL* pbRet, int nInitial)
{
	uiProcBoxWrapper(FALSE, TRUE);

#define __CURSOR_POS (4 * nIndex)

	int nRet = nInitial;
  
	*pbRet = FALSE;
	nRet = (int)DIALOGBOX_RETNUMIP(CInputUserID);
//	if (nRet > 0)
    if (nRet != 0)
		 *pbRet = TRUE;
	else nRet = nInitial;

	uiProcBoxWrapper(FALSE, FALSE);
	return nRet;
}

enum
{
	UI_DATETIME_1,	//yyyy-mm-dd
	UI_DATETIME_2,	//mm-dd hh:mm
	UI_DATETIME_3,	//yyyy-mm-dd hh:mm:ss
};

int uiProcBoxDate(QWidget* parent, int x, int y, int cx, int cy, BOOL* pbRet, int nInitial, int nFormat, BOOL bKeyCheck, BOOL bAutoSize) 
{
	uiProcBoxWrapper(bKeyCheck, TRUE);

#undef __CURSOR_POS
#define __CURSOR_POS (nIndex ? (nIndex * 3) : 0)  
#define __CURSOR_POS1 ((nIndex-from) * 3)

	int nRet = nInitial;
	int nKey = UIKEY_NONE;
  
	*pbRet = FALSE;
	nRet = DIALOGBOX_RETNUMDATE(CInputUserID);
	if (nRet >= 0)
	{
		*pbRet = TRUE;

		if (uiLcdMessageBox(UI_MSG_QUESTION, UISTR_STATUS_SAVE_QUESTION, UITIME_OUT) && ( nFormat == UI_DATETIME_1 ) )
		{
			uiRtcSetDate(nRet);  
			uiLogSlogAdd(g_uiProcStatus.nIDCurrentMgr, SLOG_SETTIME, 0, 1);
		}
	}
	else nRet = nInitial;

	if (bKeyCheck)
		*pbRet = nKey;

	uiProcBoxWrapper(bKeyCheck, FALSE);
	return nRet;
}

int uiProcBoxDaylight(QWidget* parent, int x, int y, int cx, int cy, BOOL* pbRet, int nInitial, int nFormat, BOOL bKeyCheck, BOOL bAutoSize) 
{
	uiProcBoxWrapper(bKeyCheck, TRUE);

#undef __CURSOR_POS
#define __CURSOR_POS (nIndex ? (nIndex * 3) : 0)  
#define __CURSOR_POS1 ((nIndex-from) * 3)

	int nRet = nInitial;
	int nKey = UIKEY_NONE;
  
	*pbRet = FALSE;
	nRet = DIALOGBOX_RETNUMDAYLIGHT(CInputUserID);
	if (nRet >= 0)
		*pbRet = TRUE;
	else nRet = nInitial;

	if (bKeyCheck)
		*pbRet = nKey;

	uiProcBoxWrapper(bKeyCheck, FALSE);
	return nRet;
}

int uiProcBoxTime(QWidget* parent, int x, int y, int cx, int cy, BOOL* pbRet, int nInitial, BOOL bKeyCheck = FALSE, BOOL bAutoSize = TRUE, BOOL bSecondShow = TRUE)
{
	uiProcBoxWrapper(bKeyCheck, TRUE);

#undef __CURSOR_POS
#define __CURSOR_POS (nIndex * 3)

	int nRet = nInitial;
	int addr[6];
	int i;
	int nMin[] = {0,  0,  0 };
	int nMax[] = {23, 59, 59};
	int nKey = UIKEY_NONE;
	int nYear, nMonth, nDay;

	uiRtcSeconds2YMDHMS((DWORD)nInitial, &addr[3], &addr[4], &addr[5], &addr[0], &addr[1], &addr[2]);
  
	*pbRet = FALSE;
	nRet = DIALOGBOX_RETNUMTIME(CInputUserID);
	if (nRet >= 0)
		 *pbRet = TRUE;
	else nRet = nInitial;

    uiRtcSeconds2YMDHMS(nRet, &nYear, &nMonth, &nDay, &addr[0], &addr[1], &addr[2]);
	for (i=0; i<3; i++)
	{
		if (addr[i] > nMax[i])
		{
			uiSoundOut(SOUND_ERROR, UI_BUZZER_ERROR);
			addr[i] = nMax[i];
		}
		if (addr[i] < nMin[i])
		{
			uiSoundOut(SOUND_ERROR, UI_BUZZER_ERROR);
			addr[i] = nMin[i];
		}
	}

	if (*pbRet)
		nRet = (int)uiRtcGetSeconds(addr[3], addr[4], addr[5], addr[0], addr[1], addr[2]);
	if (bKeyCheck)
		*pbRet = nKey;

	uiProcBoxWrapper(bKeyCheck, FALSE);
	return nRet;
}

int uiProcBoxTimeGroup(QWidget* parent, int x, int y, int cx, int cy, BOOL* pbRet, int nInitial, int nInitialVM, int *pnVM)
{
	uiProcBoxWrapper(FALSE, TRUE);

#undef __CURSOR_POS
#define __CURSOR_POS (3 * nIndex)

	int i;
	int addr[4];
	int addr_length[4] = {2, 2, 2, 0};
//	DB_TZGROUP_A tzGroup;
	int nIndex, i_len = addr_length[0];
	int nRet = nInitial;
	int nPrevTime = uiTimeGetTickCount() - 501;
	int nKey;
	BOOL bStartNew = TRUE;
	QLineEdit txtAddress(parent);
	char szAddress[16];
	QString szResult;
//	int nCursorPos = 0;
	int nRealWidth;
	int nVMCount = UISTR_VERIFYMODE_END - UISTR_VERIFYMODE_START + 1;
	QPalette pal = txtAddress.palette();

	pal.setBrush(QPalette::Base, QBrush(QColor(59, 129, 212)));
	pal.setColor(QPalette::All, QPalette::Text, FOREGROUND_COLOR);
	txtAddress.setPalette(pal);

	nIndex = 0;
	addr[0] = (nInitial & 0x000000FF) >> 0; //A
	addr[1] = (nInitial & 0x0000FF00) >> 8; //B
	addr[2] = (nInitial & 0x00FF0000) >> 16;//C
	addr[3] = VERIFYMODE2INDEX(nInitialVM);

	nRealWidth = 0;
	for (i=UISTR_VERIFYMODE_START; i<=UISTR_VERIFYMODE_END; i++)
		nRealWidth = MAX(nRealWidth, parent->fontMetrics().width(UISTR(i)));

	nRealWidth = parent->fontMetrics().width("00:00:00-") + nRealWidth + 10;
	x = x + cx - nRealWidth;
	cx = nRealWidth;

	txtAddress.setGeometry(x, y, cx, cy);
	txtAddress.setAlignment(Qt::AlignVCenter /*| Qt::AlignRight*/);
	txtAddress.setFocus(Qt::MouseFocusReason);
	txtAddress.show();

	*pbRet = FALSE;
	while (uiTimeIsTimeout() == FALSE)
	{
		POST_EVENTS();
		DM9000_Check();
		if (uiTimeGetTickCount() - nPrevTime > 500)
		{
			if (nIndex < 3 && addr[nIndex] > 50)
			{
				uiSoundOut(SOUND_ERROR, UI_BUZZER_ERROR);
				addr[nIndex] = 50;
				bStartNew = TRUE;
			}

			if (nIndex < 3 && addr[nIndex] < 0)
			{
				uiSoundOut(SOUND_ERROR, UI_BUZZER_ERROR);
				addr[nIndex] = 0;
				bStartNew = TRUE;
			}

			nPrevTime = uiTimeGetTickCount();

			if (bStartNew)
			{
				if (nIndex < 3)
					i_len = addr_length[nIndex];
				else
					i_len = 2;
			}
			uiProcMakeString(szAddress, addr, 3, addr_length, nIndex, i_len, ':');
			szResult = QString(szAddress) + "-" + UISTR(UISTR_VERIFYMODE_START + addr[3]);
			txtAddress.setText(szResult);

			if (bStartNew)
				txtAddress.setSelection(__CURSOR_POS, nIndex < 3 ? 2 : UISTR(UISTR_VERIFYMODE_START + addr[3]).length());
			else
				txtAddress.setCursorPosition(__CURSOR_POS + 1);

			if (!bStartNew && nIndex < 3 && i_len == addr_length[nIndex])
			{
				nKey = UIKEY_0;
				goto _lKeyPressed;
			}
		}

		if ((nKey = uiKeyGetKey()) == UIKEY_NONE)
			continue;

_lKeyPressed:
		if (nKey == UIKEY_ESC)
		{
			nRet = nInitial;
			*pnVM = nInitialVM;
			break;
		}

		if (nKey == UIKEY_OK)
		{
			*pbRet = TRUE;
			break;
		}

		//if (nKey == UIKEY_RIGHT)
		//{
		//	nIndex = (nIndex + 1) % 4;
		//	bStartNew = TRUE;
		//}

		//if (nKey == UIKEY_LEFT)
		//{
		//	nIndex = (nIndex + 3) % 4;
		//	bStartNew = TRUE;
		//}

		if (nKey == UIKEY_UP)
		{
			bStartNew = TRUE;
			if (nIndex < 3)
				addr[nIndex]--;
			else
				addr[nIndex] = (addr[nIndex] + nVMCount - 1) % nVMCount;
		}
		if (nKey == UIKEY_DOWN)
		{
			bStartNew = TRUE;
			if (nIndex < 3)
				addr[nIndex]++;
			else
				addr[nIndex] = (addr[nIndex] + nVMCount + 1) % nVMCount;
		}

		if (nKey == UIKEY_MENU && nIndex < 3)
		{
			if (bStartNew)
			{
				addr[nIndex] = 0;
				i_len = 0;
				bStartNew = FALSE;
			}
			else
			{
				addr[nIndex] = addr[nIndex] / 10;
				if (i_len)
					i_len--;
			}
		}

		if (uiKeyIsDigit((T_UI_KEY)nKey) && nIndex < 3)
		{
			if (bStartNew)
			{
				addr[nIndex] = (WORD)nKey;
				bStartNew = FALSE;
				i_len = 1;
			}
			else
			{
				addr[nIndex] = addr[nIndex] * 10 + (WORD)nKey;
				i_len++;
			}
		}

		nPrevTime = uiTimeGetTickCount() - 501;
	}

	if (*pbRet)
	{
		nRet = (addr[0] << 0) | (addr[1] << 8) | (addr[2] << 16);
		*pnVM = INDEX2VERIFYMODE(addr[3]);
	}

	uiProcBoxWrapper(FALSE, FALSE);
	return nRet;
}

int uiProcBoxTimerange(QWidget* parent, int x, int y, int cx, int cy, BOOL* pbRet, int nInitial)
{
	uiProcBoxWrapper(FALSE, TRUE);

#define __CURSOR_POS (3 * nIndex)

	nInitial = htonl(nInitial);
#define __SET_TIME {sprintf(szTime, "%02d:%02d-%02d:%02d", addr[0], addr[1], addr[2], addr[3]); txtTime.setText(szTime);}

	int addr[4];
	int addr_length[4] = {2, 2, 2, 2,};
	int nIndex, i_len = addr_length[0];
	int nRet = nInitial;
	int nPrevTime = uiTimeGetTickCount() - 501;
	int nKey;
	BOOL bStartNew = TRUE;
	QLineEdit txtTime(parent);
	char szTime[16];
//	int nCursorPos = 0;
	int nMax;
	QPalette pal = txtTime.palette();

	pal.setBrush(QPalette::Base, QBrush(QColor(255, 255, 255)));
	pal.setColor(QPalette::All, QPalette::Text, FOREGROUND_COLOR);
	txtTime.setPalette(pal);

	nIndex = 0;
	UI_IP_UNMAKE(nInitial, addr[0], addr[1], addr[2], addr[3]);

	txtTime.setGeometry(x, y, cx, cy);
	txtTime.setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
	txtTime.setFocus(Qt::MouseFocusReason);
	txtTime.show();

	*pbRet = FALSE;
	while (uiTimeIsTimeout() == FALSE)
	{
		POST_EVENTS();
		DM9000_Check();
		if (uiTimeGetTickCount() - nPrevTime > 500)
		{
			nMax = ((nIndex % 2) ? 59 : 23);
			if (addr[nIndex] > nMax)
			{
				uiSoundOut(SOUND_ERROR, UI_BUZZER_ERROR);
				addr[nIndex] = nMax;
				bStartNew = TRUE;
			}

			if (addr[nIndex] < 0)
			{
				uiSoundOut(SOUND_ERROR, UI_BUZZER_ERROR);
				addr[nIndex] = 0;
				bStartNew = TRUE;
			}

			nPrevTime = uiTimeGetTickCount();

			if (bStartNew)
				i_len = addr_length[nIndex];
			uiProcMakeString(szTime, addr, 2, addr_length, nIndex<2 ? nIndex : -1, i_len, ':');
			strcat(szTime, "-");
			uiProcMakeString(&szTime[strlen(szTime)], &addr[2], 2, &addr_length[2], nIndex>1 ? nIndex : -1, i_len, ':');
			txtTime.setText(szTime);

			if (bStartNew)
				txtTime.setSelection(__CURSOR_POS, 2);
			else
				txtTime.setCursorPosition(__CURSOR_POS + 2);

			if (!bStartNew && i_len == addr_length[nIndex])
			{
				nKey = UIKEY_UP;
				goto _lKeyPressed;
			}
		}

		if ((nKey = uiKeyGetKey()) == UIKEY_NONE)
			continue;

_lKeyPressed:
		if (nKey == UIKEY_ESC)
		{
			nRet = nInitial;
			break;
		}

		if (nKey == UIKEY_OK)
		{
			*pbRet = TRUE;
			break;
		}

	/*	if (nKey == UIKEY_RIGHT)
		{
			nIndex = (nIndex + 1) % 4;
			bStartNew = TRUE;
		}

		if (nKey == UIKEY_LEFT)
		{
			nIndex = (nIndex + 3) % 4;
			bStartNew = TRUE;
		}*/

		if (nKey == UIKEY_UP)
		{
			addr[nIndex]--;
			bStartNew = TRUE;
		}

		if (nKey == UIKEY_DOWN)
		{
			addr[nIndex]++;
			bStartNew = TRUE;
		}

		if (nKey == UIKEY_MENU)
		{
			if (bStartNew)
			{
				addr[nIndex] = 0;
				i_len = 0;
				bStartNew = FALSE;
			}
			else
			{
				addr[nIndex] = addr[nIndex] / 10;
				if (i_len)
					i_len--;
			}
		}

		if (uiKeyIsDigit((T_UI_KEY)nKey))
		{
			if (bStartNew)
			{
				addr[nIndex] = (WORD)nKey;
				bStartNew = FALSE;
				i_len = 1;
			}
			else
			{
				addr[nIndex] = addr[nIndex] * 10 + (WORD)nKey;
				i_len++;
			}
		}

		nPrevTime = uiTimeGetTickCount() - 501;
	}

	if (*pbRet)
		nRet = (int)UI_IP_MAKE(addr[0], addr[1], addr[2], addr[3]);

	nRet = htonl(nRet);

	uiProcBoxWrapper(FALSE, FALSE);
	return nRet;
}

//////////////////////////////////////////////////////////////////////////
typedef enum
{
	// 0,1,2,... = parent & title, UISTR_SPACE - top menu
	UIMENU_POPUP = -1,
	UIMENU_HASVALUE = -2,
	UIMENU_CUSTOM = -3,
	UIMENU_CUSTOM_HASCHILD = -4,
	UIMENU_NOACTION = -5,
	UIMENU_TITLE = -6
} T_UI_MENUITEM_TYPE;

typedef enum
{
	UIMENU_ICON,
	UIMENU_REPORT,
	UIMENU_REPORT_NOICON,
	UIMENU_CUSTOMDRAW,
} T_UI_MENUITEM_LISTSTYLE;

typedef struct 
{
	int nMenuStr;
	int nType;
	const char* szIconFile;
	int nHelpStr;
} T_UI_MENUITEM;

typedef int (*funcMenuCustomDraw)(CMenu *pWnd, QPainter *painter, T_UI_MENUITEM *pItems, int from, int to);

int uiProcCustomDrawEnroll(CMenu *pWnd, QPainter *painter, T_UI_MENUITEM *pItems, int from, int to);

T_UI_MENUITEM g_uiMenuItemsSrc[] = 
{
	{UISTR_MENU_MAINMENU, UIMENU_TITLE, (const char*)UIMENU_ICON, -1},
	{UISTR_MENU_USERMANAGE, UIMENU_POPUP, "USERMANAGE.png", -1},
	{UISTR_MENU_DATAVIEW, UIMENU_POPUP, "DATAVIEW.png", -1},
	{UISTR_MENU_USBMANAGE, UIMENU_POPUP, "USBMANAGE.png", -1},
	{UISTR_MENU_SYSTEMSETTING, UIMENU_POPUP, "SYSTEMSETTING.png", -1},
	{UISTR_MENU_SYSINFOVIEW, UIMENU_POPUP, "SYSINFOVIEW.png", -1},
//	{UISTR_MENU_ALARMREMOVE, UIMENU_CUSTOM, "ALARMREMOVE.png", -1},

	{UISTR_MENU_USERMANAGE, UIMENU_TITLE, (const char*)UIMENU_ICON, -1},  
	{UISTR_MENU_ENROLLNEW, UIMENU_CUSTOM, "ENROLLNEW.png", -1}, 
	{UISTR_MENU_ENROLLEDIT,UIMENU_CUSTOM,"ENROLLEDIT.png",-1},
	{UISTR_MENU_ENROLLDEL, UIMENU_CUSTOM,"ENROLLDEL.png",-1},
	
	{UISTR_MENU_ENROLL_PICTURE, UIMENU_CUSTOM,"ENROLL_PHOTO.png",-1},

// 	{UISTR_MENU_ENROLLNEW, UIMENU_TITLE, (const char*)UIMENU_CUSTOMDRAW, (int)uiProcCustomDrawEnroll},
// 	{UISTR_MENU_ENROLL_FP, UIMENU_CUSTOM, "ENROLL_FP.png", -1},
// 	{UISTR_MENU_ENROLL_RFCARD, UIMENU_CUSTOM, "ENROLL_RF.png", -1},
// 	{UISTR_MENU_ENROLL_PWD, UIMENU_CUSTOM, "ENROLL_PWD.png", -1},
// 	{UISTR_MENU_ENROLL_VOICE, UIMENU_CUSTOM, "ENROLL_VOICE.png", -1},
// 	{UISTR_MENU_ENROLL_PHOTO, UIMENU_CUSTOM, "ENROLL_PHOTO.png", -1},

// 	{UISTR_MENU_ENROLLDELETE, UIMENU_TITLE, (const char*)UIMENU_CUSTOMDRAW, (int)uiProcCustomDrawEnroll},
// 	{UISTR_MENU_DELETE_FP, UIMENU_CUSTOM, "ENROLL_FP.png", -1},
// 	{UISTR_MENU_DELETE_RFCARD, UIMENU_CUSTOM, "ENROLL_RF.png", -1},
// 	{UISTR_MENU_REMOVE_PWD, UIMENU_CUSTOM, "ENROLL_PWD.png", -1},
// 	{UISTR_MENU_DELETE_VOICE, UIMENU_CUSTOM, "ENROLL_VOICE.png", -1},
// 	{UISTR_MENU_DELETE_PHOTO, UIMENU_CUSTOM, "ENROLL_PHOTO.png", -1},
// 	{UISTR_MENU_DELETE_ALL, UIMENU_CUSTOM, "ENROLLDELETEALL.png", -1},

	{UISTR_MENU_SYSTEMSETTING, UIMENU_TITLE, (const char*)UIMENU_ICON, -1},  
	{UISTR_MENU_MAINSETTING, UIMENU_POPUP, "MAINSETTING.png", -1},
	{UISTR_MENU_COMMSETTING, UIMENU_POPUP, "COMMSETTING.png", -1},
	{UISTR_MENU_LOGSETTING, UIMENU_POPUP, "LOGSETTING.png", -1},
	{UISTR_MENU_ADVANCEDSETTING, UIMENU_POPUP, "ADVANCEDSETTING.png", -1},
//	{UISTR_MENU_POWERMANAGE, UIMENU_POPUP, "POWERMANAGE.png", -1},            //xf 091120
//	{UISTR_MENU_ACSETTING, UIMENU_POPUP, "ACSETTING.png", -1},
	{UISTR_MENU_SELFTEST, UIMENU_POPUP, "SELFTEST.png", -1},   
	{UISTR_REMOTE_ATTENDANCE, UIMENU_POPUP, "REMOTEATT.png", -1},   


	{UISTR_MENU_MAINSETTING, UIMENU_TITLE, (const char*)UIMENU_REPORT, -1},
	{UISTR_MENU_MAINSETTING_TIME, UIMENU_POPUP, "TIME.png", -1},
	{UISTR_MENU_POWERMANAGE_BELL, UIMENU_CUSTOM_HASCHILD, "BELL.png", -1},
	{UISTR_MENU_MAINSETTING_LANGUAGE, UIMENU_HASVALUE, "LANGUAGE.png", -1},
	{UISTR_MENU_ADVANCEDSETTING_MANAGER_COUNT, UIMENU_HASVALUE, "MANAGER_COUNT.png", -1},
	{UISTR_MENU_MAINSETTING_SOUND, UIMENU_HASVALUE, "SOUND.png", -1},
//	{UISTR_MENU_MAINSETTING_VOLUME, UIMENU_HASVALUE, "VOLUME.png", -1},
	{UISTR_MENU_MAINSETTING_KEYALARM, UIMENU_HASVALUE, "KEYALARM.png", -1},
	{UISTR_MENU_ADVANCEDSETTING_BRIGHT_ADJUST, UIMENU_CUSTOM, "BRIGHT_ADJUST.png", -1},
	{UISTR_MENU_MAINSETTING_BACKGROUP, UIMENU_HASVALUE, "BK_SETTING.png", -1},                  //xf 091106
//	{UISTR_MENU_ADVANCEDSETTING_THEME, UIMENU_HASVALUE, "THEME.png", -1},

	{UISTR_MENU_MAINSETTING_TIME, UIMENU_TITLE, (const char*)UIMENU_REPORT, -1},
//	{UISTR_MENU_MAINSETTING_TIME_FORMAT, UIMENU_HASVALUE, "TIME_FORMAT.png", -1},
	{UISTR_MENU_MAINSETTING_DATE_FORMAT, UIMENU_HASVALUE, "DATE_FORMAT.png", -1},
	{UISTR_MENU_MAINSETTING_TIME_DATE, UIMENU_HASVALUE, "TIME_DATE.png", -1},
	{UISTR_MENU_MAINSETTING_TIME_TIME, UIMENU_HASVALUE, "TIME_TIME.png", -1},

	{UISTR_MENU_ADVANCEDSETTING, UIMENU_TITLE, (const char*)UIMENU_REPORT, -1},
	{UISTR_MENU_ADVANCEDSETTING_VERIFYIF_FPSHOW, UIMENU_HASVALUE, "VERIFYIF_FP.png", -1},
	{UISTR_MENU_ADVANCEDSETTING_LOGDELETEALL, UIMENU_CUSTOM, "LOGDELETEALL.png", -1},
	{UISTR_MENU_ADVANCEDSETTING_ENROLLDELETEALL, UIMENU_CUSTOM, "ENROLLDELETEALL.png", -1},
	{UISTR_MENU_ADVANCEDSETTING_DEFAULT, UIMENU_CUSTOM, "DEFAULT.png", -1},
	{UISTR_MENU_ADVANCEDSETTING_FWUPGRADE, UIMENU_CUSTOM, "FWUPGRADE.png", -1},
	{UISTR_MENU_ADVANCEDSETTING_DAYLIGHT, UIMENU_POPUP, "DAYLIGHT.png", -1},
	//{UISTR_MENU_ADVANCEDSETTING_SMANAGER_PWD, UIMENU_HASVALUE, "SMANAGER_PWD.png", -1},
	{UISTR_MENU_COMMSETTING_COMMPWD, UIMENU_HASVALUE, "COMMPWD.png", -1},
	{UISTR_MENU_COMMSETTING_DHCPUSE, UIMENU_HASVALUE, "DHCPUSE.png", -1},
	//{UISTR_MENU_ADVANCEDSETTING_DEFAULT_VERIFYMODE,UIMENU_HASVALUE,"GROUPVERIFYMODE.png",-1},

	{UISTR_MENU_ADVANCEDSETTING_VERIFYIF, UIMENU_TITLE, (const char*)UIMENU_REPORT, -1},
	{UISTR_MENU_ADVANCEDSETTING_VERIFYIF_CAMERA, UIMENU_POPUP, "VERIFYIF_CAMERA.png", -1},
	{UISTR_MENU_ADVANCEDSETTING_VERIFYIF_PHOTOSHOW, UIMENU_HASVALUE, "VERIFYIF_PHOTO.png", -1},
	{UISTR_MENU_ADVANCEDSETTING_VERIFYIF_CAMERASHOW, UIMENU_HASVALUE, "VERIFYIF_CAMERA.png", -1},

	{UISTR_MENU_ADVANCEDSETTING_VERIFYIF_CAMERA, UIMENU_TITLE, (const char*)UIMENU_REPORT_NOICON, -1},
	{UISTR_MENU_ADVANCEDSETTING_VERIFYIF_CAMERA_SAVE, UIMENU_HASVALUE, NULL, -1},
	{UISTR_MENU_ADVANCEDSETTING_VERIFYIF_CAMERA_FP, UIMENU_HASVALUE, NULL, -1},
	{UISTR_MENU_ADVANCEDSETTING_VERIFYIF_CAMERA_CARD, UIMENU_HASVALUE, NULL, -1},
	{UISTR_MENU_ADVANCEDSETTING_VERIFYIF_CAMERA_PWD, UIMENU_HASVALUE, NULL, -1},

	{UISTR_MENU_ADVANCEDSETTING_DAYLIGHT, UIMENU_TITLE, (const char*)UIMENU_REPORT_NOICON, -1},
	{UISTR_MENU_ADVANCEDSETTING_DAYLIGHT_OFFSET, UIMENU_HASVALUE, NULL, -1},
	{UISTR_MENU_ADVANCEDSETTING_DAYLIGHT_CHANGE, UIMENU_HASVALUE, NULL, -1},
	{UISTR_MENU_ADVANCEDSETTING_DAYLIGHT_RESTORE, UIMENU_HASVALUE, NULL, -1},

	{UISTR_MENU_ADVANCEDSETTING_FUNCKEY, UIMENU_TITLE, (const char*)UIMENU_REPORT_NOICON, -1},
	{UISTR_MENU_ADVANCEDSETTING_FUNCKEY_F1, UIMENU_HASVALUE, NULL, -1},
	{UISTR_MENU_ADVANCEDSETTING_FUNCKEY_F2, UIMENU_HASVALUE, NULL, -1},
	{UISTR_MENU_ADVANCEDSETTING_FUNCKEY_F3, UIMENU_HASVALUE, NULL, -1},
	{UISTR_MENU_ADVANCEDSETTING_FUNCKEY_F4, UIMENU_HASVALUE, NULL, -1},

	{UISTR_MENU_POWERMANAGE, UIMENU_TITLE, (const char*)UIMENU_REPORT, -1},
	{UISTR_MENU_POWERMANAGE_POWERON, UIMENU_HASVALUE, "POWERON.png", -1},
	{UISTR_MENU_POWERMANAGE_POWEROFF, UIMENU_HASVALUE, "POWEROFF.png", -1},
	{UISTR_MENU_POWERMANAGE_SLEEP, UIMENU_HASVALUE, "SLEEP.png", -1},
	{UISTR_MENU_POWERMANAGE_IDLE_LCDSWITCH, UIMENU_HASVALUE, "IDLE.png", -1},       //xf 091106


	{UISTR_MENU_POWERMANAGE_IDLE, UIMENU_TITLE, (const char*)UIMENU_REPORT_NOICON, -1},
	{UISTR_MENU_POWERMANAGE_IDLE_POWEROFF, UIMENU_HASVALUE, NULL, -1},
	{UISTR_MENU_POWERMANAGE_IDLE_SLEEP, UIMENU_HASVALUE, NULL, -1},
	{UISTR_MENU_POWERMANAGE_IDLE_LCDSWITCH, UIMENU_HASVALUE, NULL, -1},

	{UISTR_MENU_COMMSETTING, UIMENU_TITLE, (const char*)UIMENU_REPORT, -1},
	{UISTR_MENU_COMMSETTING_DEVICEID, UIMENU_HASVALUE, "DEVICEID.png", -1},
	{UISTR_MENU_COMMSETTING_BAUDRATE, UIMENU_HASVALUE, "BAUDRATE.png", -1},
	{UISTR_MENU_COMMSETTING_IPADDRESS, UIMENU_HASVALUE, "IPADDRESS.png", -1},
	{UISTR_MENU_COMMSETTING_MASKADDRESS, UIMENU_HASVALUE, "MASKADDRESS.png", -1},
	{UISTR_MENU_COMMSETTING_GWADDRESS, UIMENU_HASVALUE, "GWADDRESS.png", -1},
	{UISTR_MENU_COMMSETTING_PCBACKGROUND, UIMENU_HASVALUE, "PCBACKGROUND.png", -1},
	{UISTR_MENU_COMMSETTING_PCBACKPORT, UIMENU_HASVALUE, "PCBACKGROUND.png", -1},
	{UISTR_MENU_DNSSERVERIP, UIMENU_HASVALUE, "PCBACKGROUND.png", -1},
// 	{UISTR_MENU_COMMSETTING_RS232USE, UIMENU_HASVALUE, "RS232USE.png", -1},
// 	{UISTR_MENU_COMMSETTING_RS485USE, UIMENU_HASVALUE, "RS485USE.png", -1},
//	{UISTR_MENU_COMMSETTING_ETHERNETUSE, UIMENU_HASVALUE, "ETHERNETUSE.png", -1},

       {UISTR_REMOTE_ATTENDANCE, UIMENU_TITLE, (const char*)UIMENU_REPORT, -1},
	{UISTR_REMOTE_ATTENDANCE_FUN, UIMENU_HASVALUE, "DEVICEID.png", -1},
	{UISTRr_REMOTE_DATA_SAVE_TIME, UIMENU_HASVALUE, "DEVICEID.png", -1},

	{UISTR_MENU_LOGSETTING, UIMENU_TITLE, (const char*)UIMENU_REPORT, -1},
	{UISTR_MENU_LOGSETTING_MLOGWARNING, UIMENU_HASVALUE, "MLOGWARNING.png", -1},
	{UISTR_MENU_LOGSETTING_GLOGWARNING, UIMENU_HASVALUE, "GLOGWARNING.png", -1},
	{UISTR_MENU_LOGSETTING_REVERIFYTIME, UIMENU_HASVALUE, "REVERIFYTIME.png", -1},

	{UISTR_MENU_ACSETTING, UIMENU_TITLE, (const char*)UIMENU_REPORT, -1},
	{UISTR_MENU_ACSETTING_TIMEZONE, UIMENU_CUSTOM_HASCHILD, "TIMEZONE.png", -1},
	{UISTR_MENU_ACSETTING_GROUP, UIMENU_POPUP, "GROUP.png", -1},
	{UISTR_MENU_ACSETTING_USERTIMEZONE, UIMENU_POPUP, "USERTIMEZONE.png", -1},
	{UISTR_MENU_ACSETTING_LOCKGROUP, UIMENU_POPUP, "LOCKGROUP.png", -1},
	{UISTR_MENU_ACSETTING_LOCKTIME, UIMENU_HASVALUE, "LOCKTIME.png", -1},
	{UISTR_MENU_ACSETTING_OPENTIME, UIMENU_HASVALUE, "OPENTIME.png", -1},
	{UISTR_MENU_ACSETTING_DOORSENSOR, UIMENU_HASVALUE, "DOORSENSOR.png", -1},
	{UISTR_MENU_ACSETTING_DURESS, UIMENU_POPUP, "DURESS.png", -1},
	{UISTR_MENU_ACSETTING_ILLEGALVERIFYWARNING, UIMENU_HASVALUE, "ILLEGALVERIFYWARNING.png", -1},
//	{UISTR_MENU_ACSETTING_GROUPVERIFYMODE, UIMENU_POPUP, "GROUPVERIFYMODE.png", -1},
// 	{UISTR_MENU_ACSETTING_ANTIPASS, UIMENU_HASVALUE, "ANTIPASS.png", -1},
//	{UISTR_MENU_ACSETTING_ACCONTROLLERUSE, UIMENU_HASVALUE, "ACCONTROLLERUSE.png", -1},

	{UISTR_MENU_ACSETTING_GROUP, UIMENU_TITLE, (const char*)UIMENU_REPORT, -1},
	{UISTR_MENU_ACSETTING_GROUP_SET, UIMENU_POPUP, "GROUP_SET.png", -1},
	{UISTR_MENU_ACSETTING_GROUP_DEFAULT_VM, UIMENU_HASVALUE, "GROUP_DEFAULTVM.png", -1},

	{UISTR_MENU_ACSETTING_GROUP_SET, UIMENU_TITLE, (const char*)UIMENU_REPORT_NOICON, -1},
	{UISTR_MENU_ACSETTING_GROUP_1, UIMENU_HASVALUE, NULL, -1},
	{UISTR_MENU_ACSETTING_GROUP_2, UIMENU_HASVALUE, NULL, -1},
	{UISTR_MENU_ACSETTING_GROUP_3, UIMENU_HASVALUE, NULL, -1},
	{UISTR_MENU_ACSETTING_GROUP_4, UIMENU_HASVALUE, NULL, -1},
	{UISTR_MENU_ACSETTING_GROUP_5, UIMENU_HASVALUE, NULL, -1},

	{UISTR_MENU_ACSETTING_USERTIMEZONE, UIMENU_TITLE, (const char*)UIMENU_REPORT_NOICON, -1},
	{UISTR_MENU_ACSETTING_USERTIMEZONE_GROUP, UIMENU_HASVALUE, NULL, -1},
	{UISTR_MENU_ACSETTING_USERTIMEZONE_GTZUSE, UIMENU_HASVALUE, NULL, -1},
	{UISTR_MENU_ACSETTING_USERTIMEZONE_TZ1, UIMENU_HASVALUE, NULL, -1},
	{UISTR_MENU_ACSETTING_USERTIMEZONE_TZ2, UIMENU_HASVALUE, NULL, -1},
	{UISTR_MENU_ACSETTING_USERTIMEZONE_TZ3, UIMENU_HASVALUE, NULL, -1},
	{UISTR_MENU_ACSETTING_USERTIMEZONE_GVMUSE, UIMENU_HASVALUE, NULL, -1},
	{UISTR_MENU_ACSETTING_USERTIMEZONE_VERIFYMODE, UIMENU_HASVALUE, NULL, -1},

	{UISTR_MENU_ACSETTING_LOCKGROUP, UIMENU_TITLE, (const char*)UIMENU_REPORT, -1},
	{UISTR_MENU_ACSETTING_LOCKGROUP_SET, UIMENU_POPUP, "LOCKGROUP_SET.png", -1},
	{UISTR_MENU_ACSETTING_LOCKGROUP_MAIN, UIMENU_HASVALUE, "LOCKGROUP_MAIN.png", -1},

	{UISTR_MENU_ACSETTING_LOCKGROUP_SET, UIMENU_TITLE, (const char*)UIMENU_REPORT_NOICON, -1},
	{UISTR_MENU_ACSETTING_LOCKGROUP_1, UIMENU_HASVALUE, NULL, -1},
	{UISTR_MENU_ACSETTING_LOCKGROUP_2, UIMENU_HASVALUE, NULL, -1},
	{UISTR_MENU_ACSETTING_LOCKGROUP_3, UIMENU_HASVALUE, NULL, -1},
	{UISTR_MENU_ACSETTING_LOCKGROUP_4, UIMENU_HASVALUE, NULL, -1},
	{UISTR_MENU_ACSETTING_LOCKGROUP_5, UIMENU_HASVALUE, NULL, -1},
	{UISTR_MENU_ACSETTING_LOCKGROUP_6, UIMENU_HASVALUE, NULL, -1},
	{UISTR_MENU_ACSETTING_LOCKGROUP_7, UIMENU_HASVALUE, NULL, -1},
	{UISTR_MENU_ACSETTING_LOCKGROUP_8, UIMENU_HASVALUE, NULL, -1},
	{UISTR_MENU_ACSETTING_LOCKGROUP_9, UIMENU_HASVALUE, NULL, -1},
	{UISTR_MENU_ACSETTING_LOCKGROUP_10, UIMENU_HASVALUE, NULL, -1},

	{UISTR_MENU_ACSETTING_DURESS, UIMENU_TITLE, (const char*)UIMENU_REPORT, -1},
	{UISTR_MENU_ACSETTING_DURESS_MANAGE, UIMENU_POPUP, "DURESS_MANAGE.png", -1},
	{UISTR_MENU_ACSETTING_DURESS_PWD, UIMENU_HASVALUE, "DURESS_PWD.png", -1},
	{UISTR_MENU_ACSETTING_DURESS_SOSKEY, UIMENU_HASVALUE, "DURESS_SOSKEY.png", -1},
//	{UISTR_MENU_ACSETTING_DURESS_ALARMDELAY, UIMENU_HASVALUE, NULL, -1},

	{UISTR_MENU_ACSETTING_DURESS_MANAGE, UIMENU_TITLE, (const char*)UIMENU_REPORT_NOICON, -1},
	{UISTR_MENU_ACSETTING_DURESS_MANAGE_ENROLL, UIMENU_CUSTOM_HASCHILD, NULL, -1},
	{UISTR_MENU_ACSETTING_DURESS_MANAGE_SET, UIMENU_CUSTOM_HASCHILD, NULL, -1},
	{UISTR_MENU_ACSETTING_DURESS_MANAGE_REMOVE, UIMENU_CUSTOM_HASCHILD, NULL, -1},
	{UISTR_MENU_ACSETTING_DURESS_MANAGE_REMOVEALL, UIMENU_CUSTOM, NULL, -1},

	{UISTR_MENU_ACSETTING_GROUPVERIFYMODE, UIMENU_TITLE, (const char*)UIMENU_REPORT_NOICON, -1},
	{UISTR_MENU_ACSETTING_GROUPVERIFYMODE_GROUP1, UIMENU_HASVALUE, NULL, -1},
	{UISTR_MENU_ACSETTING_GROUPVERIFYMODE_GROUP2, UIMENU_HASVALUE, NULL, -1},
	{UISTR_MENU_ACSETTING_GROUPVERIFYMODE_GROUP3, UIMENU_HASVALUE, NULL, -1},
	{UISTR_MENU_ACSETTING_GROUPVERIFYMODE_GROUP4, UIMENU_HASVALUE, NULL, -1},
	{UISTR_MENU_ACSETTING_GROUPVERIFYMODE_GROUP5, UIMENU_HASVALUE, NULL, -1},

	{UISTR_MENU_SELFTEST, UIMENU_TITLE, (const char*)UIMENU_REPORT, -1},
	{UISTR_MENU_SELFTEST_ALL, UIMENU_CUSTOM_HASCHILD, "SELFTEST_ALL.png", -1},
	{UISTR_MENU_SELFTEST_MEMORY, UIMENU_CUSTOM, "SELFTEST_MEMORY.png", -1},
	{UISTR_MENU_SELFTEST_LCD, UIMENU_CUSTOM, "SELFTEST_LCD.png", -1},
	{UISTR_MENU_SELFTEST_SOUND, UIMENU_CUSTOM, "SELFTEST_SOUND.png", -1},
	{UISTR_MENU_SELFTEST_SENSOR, UIMENU_CUSTOM, "SELFTEST_SENSOR.png", -1},
	{UISTR_MENU_SELFTEST_KEYBOARD, UIMENU_CUSTOM, "SELFTEST_KEYBOARD.png", -1},
	{UISTR_MENU_SELFTEST_RTC, UIMENU_CUSTOM, "SELFTEST_RTC.png", -1},
//	{UISTR_MENU_SELFTEST_MP3, UIMENU_CUSTOM, "SELFTEST_MP3.png", -1},

    {UISTR_MENU_USBMANAGE, UIMENU_TITLE, (const char*)UIMENU_ICON, -1},    //xf 091120
	{UISTR_MENU_GLOGDOWNLOAD, UIMENU_CUSTOM, "GLOGDOWNLOAD.png", -1},
	{UISTR_MENU_ALLGLOGDOWNLOAD, UIMENU_CUSTOM, "GLOGDOWNLOAD.png", -1},   //xf 090818
	{UISTR_MENU_MLOGDOWNLOAD, UIMENU_CUSTOM, "MLOGDOWNLOAD.png", -1},
	{UISTR_MENU_ALLMLOGDOWNLOAD, UIMENU_CUSTOM, "MLOGDOWNLOAD.png", -1},   //xf 090818
	{UISTR_MENU_USERINFODOWNLOAD, UIMENU_CUSTOM, "USERINFODOWNLOAD.png", -1},
	{UISTR_MENU_USERINFOUPLOAD, UIMENU_CUSTOM, "USERINFOUPLOAD.png", -1},
//	{UISTR_MENU_MSGUPLOAD, UIMENU_CUSTOM, "MSGUPLOAD.png", -1},    //xf 090818
//	{UISTR_MENU_MP3UPLOAD, UIMENU_CUSTOM_HASCHILD, "MP3UPLOAD.png", -1},

	{UISTR_MENU_SYSINFOVIEW, UIMENU_TITLE, (const char*)UIMENU_REPORT, -1},
	{UISTR_MENU_USERENROLLCOUNT, UIMENU_HASVALUE, "USED_USERS.png", -1},
	{UISTR_MENU_FPENROLLCOUNT, UIMENU_HASVALUE, "USED_FP.png", -1},
	{UISTR_MENU_PWDENROLLCOUNT, UIMENU_HASVALUE, "USED_PWD.png", -1},
	{UISTR_MENU_CARDENROLLCOUNT, UIMENU_HASVALUE, "USED_CARD.png", -1},
	{UISTR_MENU_GLOGCOUNT, UIMENU_HASVALUE, "USED_GLOG.png", -1},
	{UISTR_MENU_MLOGCOUNT, UIMENU_HASVALUE, "USED_MLOG.png", -1},
	{UISTR_MENU_USEDMEMORY, UIMENU_HASVALUE, "USED_MEMORY.png", -1},
	//{UISTR_MENU_FREESPACES, UIMENU_POPUP, "FREESPACES.png", -1},
	{UISTR_MENU_DEVICEINFO, UIMENU_POPUP, "DEVICEINFO.png", -1},

	{UISTR_MENU_FREESPACES, UIMENU_TITLE, (const char*)UIMENU_REPORT, -1},
	{UISTR_MENU_FREE_USERENROLLCOUNT, UIMENU_HASVALUE, "FREE_USERS.png", -1},
	{UISTR_MENU_FREE_FPENROLLCOUNT, UIMENU_HASVALUE, "FREE_FP.png", -1},
	{UISTR_MENU_FREE_PWDENROLLCOUNT, UIMENU_HASVALUE, "FREE_PWD.png", -1},
	{UISTR_MENU_FREE_CARDENROLLCOUNT, UIMENU_HASVALUE, "FREE_CARD.png", -1},
	{UISTR_MENU_FREE_GLOGCOUNT, UIMENU_HASVALUE, "FREE_GLOG.png", -1},
	{UISTR_MENU_FREE_MLOGCOUNT, UIMENU_HASVALUE, "FREE_MLOG.png", -1},
	{UISTR_MENU_FREE_FREEMEMORY, UIMENU_HASVALUE, "FREE_MEMORY.png", -1},

	{UISTR_MENU_DEVICEINFO, UIMENU_TITLE, (const char*)UIMENU_REPORT, -1},
//	{UISTR_MENU_DEVINFO_FP, UIMENU_HASVALUE, "DEVINFO_FP.png", -1},
//	{UISTR_MENU_DEVINFO_GLOG, UIMENU_HASVALUE, "DEVINFO_GLOG.png", -1},
//	{UISTR_MENU_DEVINFO_SLOG, UIMENU_HASVALUE, "DEVINFO_SLOG.png", -1},
//	{UISTR_MENU_DEVINFO_MEMORY, UIMENU_HASVALUE, "DEVINFO_MEMORY.png", -1},
	{UISTR_MENU_DEVINFO_FIRSTDATE, UIMENU_HASVALUE, "DEVINFO_FIRSTDATE.png", -1},
	{UISTR_MENU_DEVINFO_SN, UIMENU_HASVALUE, "DEVINFO_SN.png", -1},
	{UISTR_MENU_DEVINFO_TRADEMARK, UIMENU_HASVALUE, "DEVINFO_TRADEMARK.png", -1},
//	{UISTR_MENU_DEVINFO_PRODUCTNAME, UIMENU_HASVALUE, "DEVINFO_PRODUCTNAME.png", -1},
//	{UISTR_MENU_DEVINFO_PRODUCTTYPE, UIMENU_HASVALUE, "DEVINFO_PRODUCTTYPE.png", -1},
//	{UISTR_MENU_DEVINFO_ENGINEVERSION, UIMENU_HASVALUE, "DEVINFO_ENGINEVERSION.png", -1},
	{UISTR_MENU_DEVINFO_FIRMWAREVERSION, UIMENU_HASVALUE, "DEVINFO_FIRMWAREVERSION.png", -1},
	{UISTR_MENU_DEVINFO_HARDWAREVERSION, UIMENU_HASVALUE, "DEVINFO_HARDWAREVERSION.png", -1},

//	{UISTR_MENU_DATAVIEW, UIMENU_TITLE, (const char*)UIMENU_REPORT, -1},  //xf 091120
    	{UISTR_MENU_DATAVIEW, UIMENU_TITLE, (const char*)UIMENU_ICON, -1},    //xf 091120
	{UISTR_MENU_GLOGVIEW, UIMENU_CUSTOM_HASCHILD, "SEARCH_GLOG.png", -1},
	{UISTR_MENU_MLOGVIEW, UIMENU_CUSTOM_HASCHILD, "SEARCH_MLOG.png", -1},
	{UISTR_MENU_ENROLLVIEW, UIMENU_CUSTOM_HASCHILD, "SEARCH_USER.png", -1},

	{-1, UIMENU_TITLE, NULL, -1}
};

T_UI_MENUITEM g_uiMenuItems[ITEM_CNT(g_uiMenuItemsSrc)];

int g_uiMenuItemTitle = UISTR_MENU_MAINMENU;
int g_uiMenuItemIndex = 1;
int g_uiMenuTopIndex = 1;
QRect g_uiMenuCurrentArea;
BOOL g_uiMenuRedrawFlag = TRUE;
UINT64 g_uiMenuIDForUerTZ = 0;
int g_uiPopupTitle = -1;

void uiProcBuildMenu()
{
	int i, j=0;

	for (i=0; i<(int)ITEM_CNT(g_uiMenuItemsSrc); i++)
	{
		if (!g_uiProcStatus.bAlarming)
		{
			if (g_uiMenuItemsSrc[i].nMenuStr == UISTR_MENU_ALARMREMOVE)
				continue;
		}

		if (!dbLicense.bUseEthernet)
		{
			if ((g_uiMenuItemsSrc[i].nMenuStr == UISTR_MENU_COMMSETTING_IPADDRESS) ||
				(g_uiMenuItemsSrc[i].nMenuStr == UISTR_MENU_COMMSETTING_MASKADDRESS) ||
				(g_uiMenuItemsSrc[i].nMenuStr == UISTR_MENU_COMMSETTING_GWADDRESS) ||
				(g_uiMenuItemsSrc[i].nMenuStr == UISTR_MENU_COMMSETTING_COMMPWD) ||
				(g_uiMenuItemsSrc[i].nMenuStr == UISTR_MENU_COMMSETTING_DHCPUSE) ||
				(g_uiMenuItemsSrc[i].nMenuStr == UISTR_MENU_COMMSETTING_PCBACKGROUND) ||
				(g_uiMenuItemsSrc[i].nMenuStr == UISTR_MENU_COMMSETTING_PCBACKPORT))
				continue;
		}

		if (!dbLicense.bUseUSB)
		{
			if ((g_uiMenuItemsSrc[i].nMenuStr == UISTR_MENU_USBMANAGE && g_uiMenuItemsSrc[i].nType != UIMENU_TITLE) ||
				(g_uiMenuItemsSrc[i].nMenuStr == UISTR_MENU_ADVANCEDSETTING_FWUPGRADE))
				continue;
		}

		if (!dbLicense.bUseRS232)
		{
			if ((g_uiMenuItemsSrc[i].nMenuStr == UISTR_MENU_COMMSETTING_RS232USE) ||
				(g_uiMenuItemsSrc[i].nMenuStr == UISTR_MENU_COMMSETTING_RS485USE) ||
				(g_uiMenuItemsSrc[i].nMenuStr == UISTR_MENU_COMMSETTING_BAUDRATE))
				continue;
		}

		if (!dbLicense.bUseMP3)
		{
			if ((g_uiMenuItemsSrc[i].nMenuStr == UISTR_MENU_ENROLL_VOICE) ||
				(g_uiMenuItemsSrc[i].nMenuStr == UISTR_MENU_DELETE_VOICE) ||
				(g_uiMenuItemsSrc[i].nMenuStr == UISTR_MENU_MP3UPLOAD) ||
				(g_uiMenuItemsSrc[i].nMenuStr == UISTR_MENU_SELFTEST_MP3)) /*||
				(g_uiMenuItemsSrc[i].nMenuStr == UISTR_MENU_MAINSETTING_KEYALARM) ||
				(g_uiMenuItemsSrc[i].nMenuStr == UISTR_MENU_MAINSETTING_VOLUME) ||
				(g_uiMenuItemsSrc[i].nMenuStr == UISTR_MENU_MAINSETTING_SOUND))*/
				continue;
		}

		if (!dbLicense.bUseCamera)
		{
			if ((g_uiMenuItemsSrc[i].nMenuStr == UISTR_MENU_ENROLL_PHOTO) ||
				(g_uiMenuItemsSrc[i].nMenuStr == UISTR_MENU_DELETE_PHOTO) ||
				(g_uiMenuItemsSrc[i].nMenuStr == UISTR_MENU_ADVANCEDSETTING_VERIFYIF_PHOTOSHOW) ||
				(g_uiMenuItemsSrc[i].nMenuStr == UISTR_MENU_ADVANCEDSETTING_VERIFYIF_CAMERASHOW) ||
				(g_uiMenuItemsSrc[i].nMenuStr == UISTR_MENU_ADVANCEDSETTING_VERIFYIF_CAMERA && g_uiMenuItemsSrc[i].nType != UIMENU_TITLE))
				continue;
		}

		if (!dbLicense.bUseACFunction)
		{
			if ((g_uiMenuItemsSrc[i].nMenuStr == UISTR_MENU_ACSETTING) &&
				(g_uiMenuItemsSrc[i].nType != UIMENU_TITLE))
				continue;
		}

		if (!dbLicense.bUseAlarmFunction)
		{
			if ((g_uiMenuItemsSrc[i].nMenuStr == UISTR_MENU_ACSETTING_ILLEGALVERIFYWARNING) ||
				(g_uiMenuItemsSrc[i].nMenuStr == UISTR_MENU_ACSETTING_DURESS && g_uiMenuItemsSrc[i].nType != UIMENU_TITLE))
				continue;
		}

		g_uiMenuItems[j] = g_uiMenuItemsSrc[i];
		j++;
	}
}

BOOL uiProcMenuGetCurrentRange(int *from, int *to)
{
	int start, end;
	BOOL bRet = FALSE;

	start = 0;
	while (1)
	{
		if (g_uiMenuItems[start].nMenuStr == -1)
			goto _lExit;
		if ((g_uiMenuItems[start].nMenuStr == g_uiMenuItemTitle) && (g_uiMenuItems[start].nType == UIMENU_TITLE))
			break;
		start++;
	}

	start++;
	end = start;
	while (1)
	{
		if (g_uiMenuItems[end].nMenuStr == -1)
			break;
		if (g_uiMenuItems[end].nType == UIMENU_TITLE)
			break;
		end++;
	}

	*from = start;
	*to = end - 1;

	bRet = TRUE;
_lExit:
	return bRet;
}

int uiProcMenuTitleIndex(int nItemStr)
{
	int i = 0;

	while (g_uiMenuItems[i].nMenuStr != -1)
	{
		if ((g_uiMenuItems[i].nMenuStr == nItemStr) && (g_uiMenuItems[i].nType == UIMENU_TITLE))
			return i;
		i++;
	}
	return -1;
}

int uiProcMenuItemIndex(int nItemStr)
{
	int i = 0;

	while (g_uiMenuItems[i].nMenuStr != -1)
	{
		if ((g_uiMenuItems[i].nMenuStr == nItemStr) && (g_uiMenuItems[i].nType != UIMENU_TITLE))
			return i;
		i++;
	}
	return -1;
}

const char* uiProcMenuGetItemImageFilename(int nItemStr)
{
	int nIndex = uiProcMenuItemIndex(nItemStr);
	if (nIndex < 0)
		return NULL;
	return g_uiMenuItems[nIndex].szIconFile;
}

int uiProcMenuGetItemCount(int nTitle)
{
	int nIndex = uiProcMenuTitleIndex(nTitle);
	if (nIndex >= (int)ITEM_CNT(g_uiMenuItems))
		return 0;
	if (g_uiMenuItems[nIndex++].nType != UIMENU_TITLE)
		return 0;

	int nCount= 0;
	while (g_uiMenuItems[nIndex].nType != UIMENU_TITLE)
	{
		nCount++;
		nIndex++;
	}

	return nCount;
}

QString uiProcMenuGetItemValue(int nItemStr)
{
//	BOOL bIsNumber = TRUE;
	DWORD dwValue = 0;
	QString str;
	int a, b, c, d;
	char strTemp[16];

	switch (nItemStr)
	{
	case UISTR_MENU_MAINSETTING_LANGUAGE:
		str = UISTR(UISTR_LANG_START + dbSetupSystemNew.nLanguage);
		break;
	case UISTR_MENU_MAINSETTING_SOUND:
		str = UISTR(UISTR_YESNO_START + dbSetupSystemNew.bVoiceOut);
		break;
	case UISTR_MENU_MAINSETTING_VOLUME:
		if (dbSetupSystemNew.bVoiceOut)
			str = QString("%1%2").arg(dbSetupSystemNew.nVolume).arg(UISTR(UISTR_UNIT_PERCENT));
		else
			str = " ";
		break;
	case UISTR_MENU_MAINSETTING_BACKGROUP:
        str = UISTR(UISTR_BK_START + dbSetupSystemNew.nBackgroupIconFile);
		break;
	case UISTR_MENU_MAINSETTING_KEYALARM:
		str = UISTR(UISTR_YESNO_START + dbSetupSystemNew.bKeyTones);
		break;
	case UISTR_MENU_MAINSETTING_TIME_FORMAT:
		str = UISTR(UISTR_TIMEFMT_START + dbSetupSystemNew.nTimeFormat);
		break;
	case UISTR_MENU_MAINSETTING_DATE_FORMAT:
		str = UISTR(UISTR_DATEFMT_START + dbSetupSystemNew.nDateFormat);
		break;
	case UISTR_MENU_MAINSETTING_TIME_DATE:
		str = uiRtcGetDate(uiRtcGetSeconds());
		break;
	case UISTR_MENU_MAINSETTING_TIME_TIME:
		str = uiRtcGetTime(uiRtcGetSeconds());
		break;
	case UISTR_MENU_ADVANCEDSETTING_MANAGER_COUNT:
		str = QString("%1%2").arg(dbSetupSystemNew.nManagersNumber).arg(UISTR(UISTR_UNIT_PEOPLE));
		break;
	case UISTR_MENU_ADVANCEDSETTING_DEFAULT_VERIFYMODE:
		str = UISTR(UISTR_VERIFYMODE_START + VERIFYMODE2INDEX(dbSetupSystemNew.nVerifyMode));
		break;
	case UISTR_MENU_ADVANCEDSETTING_THEME:
		str = UISTR(UISTR_THEME_START + dbSetupSystemNew.byTheme);
		break;
	case UISTR_MENU_ADVANCEDSETTING_SMANAGER_PWD:
		str = PWD2STRING(dbSetupSystemNew.dwSManagerPwd);
		if(dbSetupSystemNew.dwSManagerPwd == STRING2PWD((char*)"0"))
			str = UISTR(UISTR_VERIFYMODE_NONE);
		else
			str = QString(str.length(), QChar('*'));
		break;
	case UISTR_MENU_ADVANCEDSETTING_VERIFYIF_PHOTOSHOW:
		str = UISTR(UISTR_YESNO_START + dbSetupSystemNew.bPhotoShow);
		break;
	case UISTR_MENU_ADVANCEDSETTING_VERIFYIF_CAMERASHOW:
		str = UISTR(UISTR_YESNO_START + dbSetupSystemNew.bCameraShow);
		break;
	case UISTR_MENU_ADVANCEDSETTING_VERIFYIF_FPSHOW:
		str = UISTR(UISTR_YESNO_START + dbSetupSystemNew.bFPShow);
		break;
	case UISTR_MENU_ADVANCEDSETTING_VERIFYIF_CAMERA_SAVE:
		str = UISTR(UISTR_YESNO_START + dbSetupSystemNew.bCameraSave);
		break;
	case UISTR_MENU_ADVANCEDSETTING_VERIFYIF_CAMERA_FP:
		str = QString("%1%2").arg(dbSetupSystemNew.byCameraRateForFP).arg(UISTR(UISTR_UNIT_PERCENT));
		if (!dbSetupSystemNew.byCameraRateForFP)
			str = UISTR(UISTR_YESNO_NO);
		break;
	case UISTR_MENU_ADVANCEDSETTING_VERIFYIF_CAMERA_CARD:
		str = QString("%1%2").arg(dbSetupSystemNew.byCameraRateForCard).arg(UISTR(UISTR_UNIT_PERCENT));
		if (!dbSetupSystemNew.byCameraRateForCard)
			str = UISTR(UISTR_YESNO_NO);
		break;
	case UISTR_MENU_ADVANCEDSETTING_VERIFYIF_CAMERA_PWD:
		str = QString("%1%2").arg(dbSetupSystemNew.byCameraRateForPWD).arg(UISTR(UISTR_UNIT_PERCENT));
		if (!dbSetupSystemNew.byCameraRateForPWD)
			str = UISTR(UISTR_YESNO_NO);
		break;
	case UISTR_MENU_ADVANCEDSETTING_DAYLIGHT_OFFSET:
		if(dbSetupSystemNew.nDaylightOffset != 0)
			str = QString("+%1%2").arg(dbSetupSystemNew.nDaylightOffset).arg(UISTR(UISTR_UNIT_HOUR));
		else 
			str = QString("%1%2").arg(dbSetupSystemNew.nDaylightOffset).arg(UISTR(UISTR_UNIT_HOUR));
		break;
	case UISTR_MENU_ADVANCEDSETTING_DAYLIGHT_CHANGE:
		str = uiRtcSeconds2Summertime(dbSetupSystemNew.dwDaylightChangeTime);
		break;
	case UISTR_MENU_ADVANCEDSETTING_DAYLIGHT_RESTORE:
		str = uiRtcSeconds2Summertime(dbSetupSystemNew.dwDaylightRestoreTime);
		break;
	case UISTR_MENU_ADVANCEDSETTING_FUNCKEY_F1:
		str = UISTR(UISTR_FUNC_START + dbSetupSystemNew.byF1Status);
		break;
	case UISTR_MENU_ADVANCEDSETTING_FUNCKEY_F2:
		str = UISTR(UISTR_FUNC_START + dbSetupSystemNew.byF2Status);
		break;
	case UISTR_MENU_ADVANCEDSETTING_FUNCKEY_F3:
		str = UISTR(UISTR_FUNC_START + dbSetupSystemNew.byF3Status);
		break;
	case UISTR_MENU_ADVANCEDSETTING_FUNCKEY_F4:
		str = UISTR(UISTR_FUNC_START + dbSetupSystemNew.byF4Status);
		break;
	case UISTR_MENU_POWERMANAGE_POWEROFF:
		if (dbSetupSystemNew.dwAutoPoweroffTime)
			str = uiRtcGetTime(dbSetupSystemNew.dwAutoPoweroffTime);
		else
			str = UISTR(UISTR_YESNO_NO);
		break;
	case UISTR_MENU_POWERMANAGE_POWERON:
		if (dbSetupSystemNew.dwAutoPoweronTime)
			str = uiRtcGetTime(dbSetupSystemNew.dwAutoPoweronTime);
		else
			str = UISTR(UISTR_YESNO_NO);
		break;
	case UISTR_MENU_POWERMANAGE_SLEEP:
		if (dbSetupSystemNew.dwAutoSleepTime)
			str = uiRtcGetTime(dbSetupSystemNew.dwAutoSleepTime);
		else
			str = UISTR(UISTR_YESNO_NO);
		break;
	case UISTR_MENU_POWERMANAGE_POWERKEYUSE:
		str = UISTR(UISTR_YESNO_START + dbSetupSystemNew.bPowerkeyLock);
		break;
	case UISTR_MENU_POWERMANAGE_IDLE_POWEROFF:
		if (dbSetupSystemNew.nIdletimeForPoweroff)
			str = QString("%1%2").arg(dbSetupSystemNew.nIdletimeForPoweroff).arg(UISTR(UISTR_UNIT_MINUTE));
		else
			str = UISTR(UISTR_YESNO_NO);
		break;
	case UISTR_MENU_POWERMANAGE_IDLE_SLEEP:
		if (dbSetupSystemNew.nIdletimeForSleep)
			str = QString("%1%2").arg(dbSetupSystemNew.nIdletimeForSleep).arg(UISTR(UISTR_UNIT_MINUTE));
		else
			str = UISTR(UISTR_YESNO_NO);
		break;
	case UISTR_MENU_POWERMANAGE_IDLE_LCDSWITCH:
		if (dbSetupSystemNew.nIdletimeForLcdswitch)
			str = QString("%1%2").arg(dbSetupSystemNew.nIdletimeForLcdswitch).arg(UISTR(UISTR_UNIT_MINUTE));
		else
			str = UISTR(UISTR_YESNO_NO);
		break;
	case UISTR_MENU_COMMSETTING_DEVICEID:
		dwValue = (DWORD)dbSetupSystemNew.nMachineID;
		break;
	case UISTR_MENU_COMMSETTING_RS232USE:
		str = UISTR(UISTR_YESNO_START + dbSetupSystemNew.bRS232Use);
		break;
	case UISTR_MENU_COMMSETTING_RS485USE:
		str = UISTR(UISTR_YESNO_START + dbSetupSystemNew.bRS485Use);
		break;
	case UISTR_MENU_COMMSETTING_BAUDRATE:
		str = UISTR(UISTR_BPS_START + dbSetupSystemNew.nBaudrate);
		break;
	case UISTR_MENU_COMMSETTING_ETHERNETUSE:
		str = UISTR(UISTR_YESNO_START + dbSetupSystemNew.bEthernetUse);
		break;
	case UISTR_MENU_COMMSETTING_IPADDRESS:
		UI_IP_UNMAKE(dbSetupSystemNew.bDHCPUse ? dbComm_ipAddress : dbSetupSystemNew.ipAddress, a, b, c, d);
		str = QString("%1.%2.%3.%4").arg(a).arg(b).arg(c).arg(d);
		break;
	case UISTR_MENU_COMMSETTING_MASKADDRESS:
		UI_IP_UNMAKE(dbSetupSystemNew.bDHCPUse ? dbComm_ipSubnetMask : dbSetupSystemNew.ipSubnetMask,a, b, c, d);
		str = QString("%1.%2.%3.%4").arg(a).arg(b).arg(c).arg(d);
		break;
	case UISTR_MENU_COMMSETTING_GWADDRESS:
		UI_IP_UNMAKE(dbSetupSystemNew.bDHCPUse ? dbComm_ipDefaultGateway : dbSetupSystemNew.ipDefaultGateway, a, b, c, d);
		str = QString("%1.%2.%3.%4").arg(a).arg(b).arg(c).arg(d);
		break;
	case UISTR_MENU_COMMSETTING_COMMPWD:
		dwValue = dbSetupSystemNew.dwCommPassword;
		if (!dwValue)
			str = UISTR(UISTR_YESNO_NO);
		break;
	case UISTR_MENU_COMMSETTING_DHCPUSE:
		str = UISTR(UISTR_YESNO_START + dbSetupSystemNew.bDHCPUse);
		break;
	case UISTR_MENU_COMMSETTING_PCBACKGROUND:
		UI_IP_UNMAKE(dbSetupSystemNew.ipPCBackground, a, b, c, d);
		str = QString("%1.%2.%3.%4").arg(a).arg(b).arg(c).arg(d);
		break;
	case UISTR_MENU_COMMSETTING_PCBACKPORT:
		dwValue = (DWORD)dbSetupSystemNew.wPortNumBack;
		break;
	case UISTR_REMOTE_ATTENDANCE_FUN:
		str = UISTR(UISTR_YESNO_START + dbSetupSystemNew.bRemoteAttUse);
		break;
	case UISTRr_REMOTE_DATA_SAVE_TIME:
		dwValue = (DWORD)dbSetupSystemNew.dwDataSaveTime;
		break;	
	case UISTR_MENU_LOGSETTING_MLOGWARNING:
		if (dbSetupSystemNew.nMLogWarning)
			str = QString("%1%2").arg(dbSetupSystemNew.nMLogWarning).arg(UISTR(UISTR_UNIT_LOG));
		else
			str = UISTR(UISTR_YESNO_NO);
		break;
	case UISTR_MENU_LOGSETTING_GLOGWARNING:
		if (dbSetupSystemNew.nGLogWarning)
			str = QString("%1%2").arg(dbSetupSystemNew.nGLogWarning).arg(UISTR(UISTR_UNIT_LOG));
		else
			str = UISTR(UISTR_YESNO_NO);
		break;
	case UISTR_MENU_LOGSETTING_REVERIFYTIME:
		if (dbSetupSystemNew.nReverifyTime)
			str = QString("%1%2").arg(dbSetupSystemNew.nReverifyTime).arg(UISTR(UISTR_UNIT_MINUTE));
		else
			str = UISTR(UISTR_YESNO_NO);
		break;
	case UISTR_MENU_ACSETTING_LOCKTIME:
		if (dbSetupSystemNew.nLockTime)
			str = QString("%1%2").arg(dbSetupSystemNew.nLockTime).arg(UISTR(UISTR_UNIT_SECOND));
		else
			str = UISTR(UISTR_YESNO_NO);
		break;
	case UISTR_MENU_ACSETTING_OPENTIME:
		if (dbSetupSystemNew.nDoorOpenTime)
			str = QString("%1%2").arg(dbSetupSystemNew.nDoorOpenTime).arg(UISTR(UISTR_UNIT_SECOND));
		else
			str = UISTR(UISTR_YESNO_NO);
		break;
	case UISTR_MENU_ACSETTING_DOORSENSOR:
		str = UISTR(UISTR_DOORSENSOR_START + dbSetupSystemNew.nDoorSensorStatus);
		break;
	case UISTR_MENU_ACSETTING_ILLEGALVERIFYWARNING:
		if (dbSetupSystemNew.nIllegalVerifyWarning)
			str = QString("%1%2").arg(dbSetupSystemNew.nIllegalVerifyWarning).arg(UISTR(UISTR_UNIT_TIMES));
		else
			str = UISTR(UISTR_YESNO_NO);
		break;
	case UISTR_MENU_ACSETTING_ANTIPASS:
		str = UISTR(UISTR_ANTIPASS_START + dbSetupSystemNew.byAntipassStatus);
		break;
	case UISTR_MENU_ACSETTING_ACCONTROLLERUSE:
		dwValue = dbSetupSystemNew.dwBindingID;
		if (!dwValue)
			str = UISTR(UISTR_YESNO_NO);
		break;
	case UISTR_MENU_ACSETTING_GROUP_DEFAULT_VM:
		str = UISTR(UISTR_VERIFYMODE_START + VERIFYMODE2INDEX(dbSetupSystemNew.byDefaultGVM));
		break;
	case UISTR_MENU_ACSETTING_GROUP_1:
	case UISTR_MENU_ACSETTING_GROUP_2:
	case UISTR_MENU_ACSETTING_GROUP_3:
	case UISTR_MENU_ACSETTING_GROUP_4:
	case UISTR_MENU_ACSETTING_GROUP_5:
		a = (int)dbSetupTimezoneNew.tzGroup[nItemStr - UISTR_MENU_ACSETTING_GROUP_1].bGroupA;
		b = (int)dbSetupTimezoneNew.tzGroup[nItemStr - UISTR_MENU_ACSETTING_GROUP_1].bGroupB;
		c = (int)dbSetupTimezoneNew.tzGroup[nItemStr - UISTR_MENU_ACSETTING_GROUP_1].bGroupC;
		d = (int)dbSetupTimezoneNew.tzGrupVM[nItemStr - UISTR_MENU_ACSETTING_GROUP_1];
		sprintf(strTemp, "%02d:%02d:%02d", a, b, c);
		str = QString(strTemp) + "-" + UISTR(UISTR_VERIFYMODE_START + VERIFYMODE2INDEX(d));
		break;
	case UISTR_MENU_ACSETTING_USERTIMEZONE_GROUP:
		dwValue = (DWORD)gUserInfoTemp.TIMEGROUP;
		break;
	case UISTR_MENU_ACSETTING_USERTIMEZONE_GTZUSE:
		str = UISTR(UISTR_YESNO_START + DbUserInfoFlagGTZStatusGet(&gUserInfoTemp));
		break;
	case UISTR_MENU_ACSETTING_USERTIMEZONE_TZ1:
	case UISTR_MENU_ACSETTING_USERTIMEZONE_TZ2:
	case UISTR_MENU_ACSETTING_USERTIMEZONE_TZ3:
		dwValue = (DWORD)gUserInfoTemp.UserTZ[nItemStr - UISTR_MENU_ACSETTING_USERTIMEZONE_TZ1];
		break;
	case UISTR_MENU_ACSETTING_USERTIMEZONE_GVMUSE:
		str = UISTR(UISTR_YESNO_START + DbUserInfoFlagGVMStatusGet(&gUserInfoTemp));
		break;
	case UISTR_MENU_ACSETTING_USERTIMEZONE_VERIFYMODE:
		str = UISTR(UISTR_VERIFYMODE_START + VERIFYMODE2INDEX(gUserInfoTemp.VERIFYMODE));
		break;
	case UISTR_MENU_ACSETTING_LOCKGROUP_MAIN:
		dwValue = dbSetupSystemNew.nLockGroupMain;
		if (!dwValue)
			str = UISTR(UISTR_YESNO_NO);
		break;
	case UISTR_MENU_ACSETTING_LOCKGROUP_1:
	case UISTR_MENU_ACSETTING_LOCKGROUP_2:
	case UISTR_MENU_ACSETTING_LOCKGROUP_3:
	case UISTR_MENU_ACSETTING_LOCKGROUP_4:
	case UISTR_MENU_ACSETTING_LOCKGROUP_5:
	case UISTR_MENU_ACSETTING_LOCKGROUP_6:
	case UISTR_MENU_ACSETTING_LOCKGROUP_7:
	case UISTR_MENU_ACSETTING_LOCKGROUP_8:
	case UISTR_MENU_ACSETTING_LOCKGROUP_9:
	case UISTR_MENU_ACSETTING_LOCKGROUP_10:
		dwValue = (DWORD)LOCKGROUP2NUMBER(dbSetupTimezoneNew.tzLockGroup[nItemStr - UISTR_MENU_ACSETTING_LOCKGROUP_1]);
		if (!dwValue)
			str = " ";
		else
			str = LOCKGROUP2STRING(dbSetupTimezoneNew.tzLockGroup[nItemStr - UISTR_MENU_ACSETTING_LOCKGROUP_1]);
		break;
	case UISTR_MENU_ACSETTING_DURESS_PWD:
		str = UISTR(UISTR_YESNO_START + dbSetupSystemNew.bPwdAlarmUse);
		break;
	case UISTR_MENU_ACSETTING_DURESS_SOSKEY:
		str = UISTR(UISTR_YESNO_START + dbSetupSystemNew.bSOSKeyUse);
		break;
	case UISTR_MENU_ACSETTING_DURESS_ALARMDELAY:
		str = QString("%1%2").arg(dbSetupSystemNew.nAlarmDelay).arg(UISTR(UISTR_UNIT_SECOND));
		if (!dbSetupSystemNew.nAlarmDelay)
			str = UISTR(UISTR_YESNO_NO);
		break;
	case UISTR_MENU_ACSETTING_GROUPVERIFYMODE_GROUP1:
	case UISTR_MENU_ACSETTING_GROUPVERIFYMODE_GROUP2:
	case UISTR_MENU_ACSETTING_GROUPVERIFYMODE_GROUP3:
	case UISTR_MENU_ACSETTING_GROUPVERIFYMODE_GROUP4:
	case UISTR_MENU_ACSETTING_GROUPVERIFYMODE_GROUP5:
		str = UISTR(UISTR_VERIFYMODE_START + VERIFYMODE2INDEX(dbSetupTimezoneNew.tzGrupVM[nItemStr - UISTR_MENU_ACSETTING_GROUPVERIFYMODE_GROUP1]));
		break;
	case UISTR_MENU_USERENROLLCOUNT:
		str = QString("%1 / %3%4").arg(DbUserInfoGetCount()).arg(dbLicense.nMaxEnrollCount).arg(UISTR(UISTR_UNIT_MAN));
		break;
	case UISTR_MENU_FPENROLLCOUNT:
		str = QString("%1 / %3%4").arg(DbUserInfoGetCount(BACKUP_FINGER)).arg(gFpMaximum).arg(UISTR(UISTR_UNIT_FP));
		break;
	case UISTR_MENU_PWDENROLLCOUNT:
	    str = QString("%1 / %3%4").arg(DbUserInfoGetCount(BACKUP_PASSWORD)).arg(dbLicense.nMaxEnrollCount).arg(UISTR(UISTR_UNIT_GE));       //xf 090818
		break;
	case UISTR_MENU_CARDENROLLCOUNT:
		str = QString("%1 / %3%4").arg(DbUserInfoGetCount(BACKUP_CARD)).arg(dbLicense.nMaxEnrollCount).arg(UISTR(UISTR_UNIT_GE));      //xf 090818
		break;
	case UISTR_MENU_GLOGCOUNT:
		str = QString("%1 / %3%4").arg( DbGLogCount()).arg(dbLicense.nGlogMaxCount - 1).arg(UISTR(UISTR_UNIT_LOG));
		break;
	case UISTR_MENU_MLOGCOUNT:
		str = QString("%1 / %3%4").arg( DbSLogCount()).arg(dbLicense.nSlogMaxCount - 1).arg(UISTR(UISTR_UNIT_LOG));
		break;
	case UISTR_MENU_USEDMEMORY:
		str = QString("%1 / %2M").arg((total_flash_size() - free_space_flash())/1024/1024).arg(total_flash_size() / 1024 / 1024);
		break;
	case UISTR_MENU_FREE_USERENROLLCOUNT:
		dwValue = dbLicense.nMaxEnrollCount - DbUserInfoGetCount();
		break;
	case UISTR_MENU_FREE_FPENROLLCOUNT:
		str = QString("%1%2").arg(gFpMaximum - DbUserInfoGetCount(BACKUP_FINGER)).arg(UISTR(UISTR_UNIT_FP));
		break;
	case UISTR_MENU_FREE_PWDENROLLCOUNT:
		dwValue = dbLicense.nMaxEnrollCount - DbUserInfoGetCount(BACKUP_PASSWORD);
		break;
	case UISTR_MENU_FREE_CARDENROLLCOUNT:
		dwValue = dbLicense.nMaxEnrollCount -DbUserInfoGetCount(BACKUP_CARD);
		break;
	case UISTR_MENU_FREE_GLOGCOUNT:
		str = QString("%1%2").arg(dbLicense.nGlogMaxCount - 1 - DbGLogCount()).arg(UISTR(UISTR_UNIT_LOG));
		break;
	case UISTR_MENU_FREE_MLOGCOUNT:
		str = QString("%1%2").arg(dbLicense.nSlogMaxCount - 1 - DbSLogCount()).arg(UISTR(UISTR_UNIT_LOG));
		break;
	case UISTR_MENU_FREE_FREEMEMORY:
		str = QString("%1M").arg(free_space_flash() / 1024 / 1024);
		break;
	case UISTR_MENU_DEVINFO_FP:
		str = QString("%1%2").arg(gFpMaximum).arg(UISTR(UISTR_UNIT_FP));
		break;
	case UISTR_MENU_DEVINFO_GLOG:
		str = QString("%1%2").arg(dbLicense.nGlogMaxCount - 1).arg(UISTR(UISTR_UNIT_LOG));
		break;
	case UISTR_MENU_DEVINFO_SLOG:
		str = QString("%1%2").arg(dbLicense.nSlogMaxCount - 1).arg(UISTR(UISTR_UNIT_LOG));
		break;
	case UISTR_MENU_DEVINFO_MEMORY:
		str = QString("%1M").arg(total_flash_size() / 1024 / 1024);
		break;
	case UISTR_MENU_DEVINFO_FIRSTDATE:
		str = QString(dbLicense.szFirstDate);
		break;
	case UISTR_MENU_DEVINFO_SN:
		str = QString(dbLicense.szSerialNumber);
		break;
	case UISTR_MENU_DEVINFO_TRADEMARK:
		str = QString(dbLicense.szTradeMark);
		break;
	case UISTR_MENU_DEVINFO_PRODUCTNAME:
		str = QString(dbLicense.szProductName);
		break;
	case UISTR_MENU_DEVINFO_PRODUCTTYPE:
		str = QString(dbLicense.szProductType);
		break;
	case UISTR_MENU_DEVINFO_ENGINEVERSION:
		str = QString(dbLicense.szEngineVersion);
		break;
	case UISTR_MENU_DEVINFO_FIRMWAREVERSION:
	//	str = QString(dbLicense.szFirmwareVersion);   //xf 091106
        str = QString(LNSC_FIRMWAREVERSION1);   //xf 091106
		break;
	case UISTR_MENU_DEVINFO_HARDWAREVERSION:
		str = LNSC_HARDWAREVERSION;
		break;
	case UISTR_MENU_DNSSERVERIP:
		if (dbSetupSystemNew.bDHCPUse)
	    {
			UI_IP_UNMAKE(dbComm_dnsserverip, a, b, c, d);
	    }
	   	else
	   	{
	        UI_IP_UNMAKE(dbSetupSystemNew.DNSserverIp , a, b, c, d);
	   	}
		str = QString("%1.%2.%3.%4").arg(a).arg(b).arg(c).arg(d);
		break;		
	default:
		break;
	}

	if (!str.length())
		str = QString("%1").arg(dwValue);

	return str;
}

BOOL uiProcMenuHasValue(QWidget *pWnd, int nItemStr)
{
	BOOL bResult;
	int nValue, nValue1;
	int x, y, w, h;
//	USER_INFO *pUserInfo;
	char *szValue;

	g_uiMenuRedrawFlag = FALSE;

	x = g_uiMenuCurrentArea.x();
	y = g_uiMenuCurrentArea.y();
	w = g_uiMenuCurrentArea.width();
	h = g_uiMenuCurrentArea.height();

	switch (nItemStr)
	{
	case UISTR_MENU_MAINSETTING_LANGUAGE:
		nValue = uiProcBoxSelect(pWnd, x, y, w, h, &bResult, dbSetupSystemNew.nLanguage, UISTR_LANG_START, UISTR_LANG_END - 1);
		if (bResult)
		{
			nLanguage = dbSetupTotal.setSystem.nLanguage;  
			dbSetupTotal.setSystem.nLanguage = nValue;    
			dbSetupSystemNew.nLanguage =nValue;           
			SET_LANGUAGE((T_UI_LANG)nValue);  
		}
		break;
	case UISTR_MENU_MAINSETTING_SOUND:
		nValue = uiProcBoxSelect(pWnd, x, y, w, h, &bResult, dbSetupSystemNew.bVoiceOut, UISTR_YESNO_START, UISTR_YESNO_END);
		if (bResult)
			dbSetupSystemNew.bVoiceOut = nValue;
		break;
	case UISTR_MENU_MAINSETTING_VOLUME:
		if (dbSetupSystemNew.bVoiceOut)
		{
			nValue = uiProcBoxNumber(pWnd, x, y, w, h, &bResult, dbSetupSystemNew.nVolume, 0, 100, FALSE, UISTR_UNIT_PERCENT);
			if (bResult)
				dbSetupSystemNew.nVolume = nValue;
		}
		break;
	case UISTR_MENU_MAINSETTING_BACKGROUP:
		nValue = uiProcBoxSelect(pWnd, x, y, w, h, &bResult, dbSetupSystemNew.nBackgroupIconFile, UISTR_BK_START, UISTR_BK_END );
		if (bResult)
			dbSetupSystemNew.nBackgroupIconFile = nValue;
		break;
	case UISTR_MENU_MAINSETTING_KEYALARM:
		nValue = uiProcBoxSelect(pWnd, x, y, w, h, &bResult, dbSetupSystemNew.bKeyTones, UISTR_YESNO_START, UISTR_YESNO_END);
		if (bResult)
			dbSetupSystemNew.bKeyTones = nValue;
		break;
	case UISTR_MENU_MAINSETTING_TIME_FORMAT:
		nValue = uiProcBoxSelect(pWnd, x, y, w, h, &bResult, dbSetupSystemNew.nTimeFormat, UISTR_TIMEFMT_START, UISTR_TIMEFMT_END);
		if (bResult)
			dbSetupSystemNew.nTimeFormat = nValue;
		break;
	case UISTR_MENU_MAINSETTING_DATE_FORMAT:
		nValue = uiProcBoxSelect(pWnd, x, y, w, h, &bResult, dbSetupSystemNew.nDateFormat, UISTR_DATEFMT_START, UISTR_DATEFMT_END);
		if (bResult)
			dbSetupSystemNew.nDateFormat = nValue;
		break;
	case UISTR_MENU_MAINSETTING_TIME_DATE:
		nValue = uiProcBoxDate(pWnd, x, y, w, h, &bResult, uiRtcGetSeconds());
		break;
	case UISTR_MENU_MAINSETTING_TIME_TIME:
		nValue = uiProcBoxTime(pWnd, x, y, w, h, &bResult, uiRtcGetSeconds());
		if (bResult)
		{
			uiRtcSetTime(nValue);
			uiLogSlogAdd(g_uiProcStatus.nIDCurrentMgr, SLOG_SETTIME, 0, 2);
		}
		break;
	case UISTR_MENU_ADVANCEDSETTING_MANAGER_COUNT:
		nValue = uiProcBoxNumber(pWnd, x, y, w, h, &bResult, dbSetupSystemNew.nManagersNumber, MAX(1, Db_GetManagerCountMax()), 10, FALSE, UISTR_UNIT_PEOPLE);
		if (bResult)
			dbSetupSystemNew.nManagersNumber = nValue;
		break;
	case UISTR_MENU_ADVANCEDSETTING_DEFAULT_VERIFYMODE:
		nValue = uiProcBoxSelect(pWnd, x, y, w, h, &bResult, dbSetupSystemNew.nVerifyMode - 1, UISTR_VERIFYMODE_START + 1, UISTR_VERIFYMODE_END);
		if (bResult)
			dbSetupSystemNew.nVerifyMode = INDEX2VERIFYMODE(nValue + 1);
		break;
	case UISTR_MENU_ADVANCEDSETTING_THEME:
		nValue = uiProcBoxSelect(pWnd, x, y, w, h, &bResult, (int)dbSetupSystemNew.byTheme, UISTR_THEME_START, UISTR_THEME_END);
		if (bResult)
		{
			dbSetupSystemNew.byTheme= nValue;
			SET_GUITHEME((int)nValue);
		}
		break;
	case UISTR_MENU_ADVANCEDSETTING_SMANAGER_PWD:
		szValue = uiProcBoxString(pWnd, x, y, w, h, &bResult, PWD2STRING(dbSetupSystemNew.dwSManagerPwd), 6);
		if (bResult)
		{
			if (!strlen(szValue))
				dbSetupSystemNew.dwSManagerPwd = DEFAULT_PASSWORD;
			else
				dbSetupSystemNew.dwSManagerPwd = STRING2PWD(szValue);
		}
		break;
	case UISTR_MENU_ADVANCEDSETTING_VERIFYIF_PHOTOSHOW:
		nValue = uiProcBoxSelect(pWnd, x, y, w, h, &bResult, dbSetupSystemNew.bPhotoShow, UISTR_YESNO_START, UISTR_YESNO_END);
		if (bResult)
		{
			dbSetupSystemNew.bPhotoShow = nValue;
			if (dbSetupSystemNew.bPhotoShow)
				dbSetupSystemNew.bCameraShow = FALSE;
		}
		break;
	case UISTR_MENU_ADVANCEDSETTING_VERIFYIF_CAMERASHOW:
		nValue = uiProcBoxSelect(pWnd, x, y, w, h, &bResult, dbSetupSystemNew.bCameraShow, UISTR_YESNO_START, UISTR_YESNO_END);
		if (bResult)
		{
			dbSetupSystemNew.bCameraShow = nValue;
			if (dbSetupSystemNew.bCameraShow)
				dbSetupSystemNew.bPhotoShow = FALSE;
		}
		break;
	case UISTR_MENU_ADVANCEDSETTING_VERIFYIF_FPSHOW:
		nValue = uiProcBoxSelect(pWnd, x, y, w, h, &bResult, dbSetupSystemNew.bFPShow, UISTR_YESNO_START, UISTR_YESNO_END);
		if (bResult)
			dbSetupSystemNew.bFPShow = nValue;
		break;
	case UISTR_MENU_ADVANCEDSETTING_VERIFYIF_CAMERA_SAVE:
		nValue = uiProcBoxSelect(pWnd, x, y, w, h, &bResult, dbSetupSystemNew.bCameraSave, UISTR_YESNO_START, UISTR_YESNO_END);
		if (bResult)
			dbSetupSystemNew.bCameraSave = nValue;
		break;
	case UISTR_MENU_ADVANCEDSETTING_VERIFYIF_CAMERA_FP:
		if (dbSetupSystemNew.bCameraSave)
		{
			nValue = uiProcBoxNumber(pWnd, x, y, w, h, &bResult, dbSetupSystemNew.byCameraRateForFP, 0, 100, FALSE, UISTR_UNIT_PERCENT);
			if (bResult)
				dbSetupSystemNew.byCameraRateForFP = nValue;
		}
		break;
	case UISTR_MENU_ADVANCEDSETTING_VERIFYIF_CAMERA_CARD:
		if (dbSetupSystemNew.bCameraSave)
		{
			nValue = uiProcBoxNumber(pWnd, x, y, w, h, &bResult, dbSetupSystemNew.byCameraRateForCard, 0, 100, FALSE, UISTR_UNIT_PERCENT);
			if (bResult)
				dbSetupSystemNew.byCameraRateForCard = nValue;
		}
		break;
	case UISTR_MENU_ADVANCEDSETTING_VERIFYIF_CAMERA_PWD:
		if (dbSetupSystemNew.bCameraSave)
		{
			nValue = uiProcBoxNumber(pWnd, x, y, w, h, &bResult, dbSetupSystemNew.byCameraRateForPWD, 0, 100, FALSE, UISTR_UNIT_PERCENT);
			if (bResult)
				dbSetupSystemNew.byCameraRateForPWD = nValue;
		}
		break;
	case UISTR_MENU_ADVANCEDSETTING_DAYLIGHT_OFFSET:
		nValue = uiProcBoxNumber(pWnd, x, y, w, h, &bResult, dbSetupSystemNew.nDaylightOffset, 0, 5,FALSE, UISTR_UNIT_HOUR);
		if (bResult)
			dbSetupSystemNew.nDaylightOffset = nValue;
		break;
	case UISTR_MENU_ADVANCEDSETTING_DAYLIGHT_CHANGE:
//		nValue = uiProcBoxDate(pWnd, x, y, w, h, &bResult, (int)dbSetupSystemNew.dwDaylightChangeTime, UI_DATETIME_2);  //xf 091120
		nValue = uiProcBoxDaylight(pWnd, x, y, w, h, &bResult, (int)dbSetupSystemNew.dwDaylightChangeTime, UI_DATETIME_2);  //xf 091120
		if (bResult)
			dbSetupSystemNew.dwDaylightChangeTime = (DWORD)nValue;
		break;
	case UISTR_MENU_ADVANCEDSETTING_DAYLIGHT_RESTORE:
//		nValue = uiProcBoxDate(pWnd, x, y, w, h, &bResult, (int)dbSetupSystemNew.dwDaylightRestoreTime, UI_DATETIME_2);  //xf 091120
		nValue = uiProcBoxDaylight(pWnd, x, y, w, h, &bResult, (int)dbSetupSystemNew.dwDaylightRestoreTime, UI_DATETIME_2);  //xf 091120
		if (bResult)
			dbSetupSystemNew.dwDaylightRestoreTime = (DWORD)nValue;
		break;
	case UISTR_MENU_ADVANCEDSETTING_FUNCKEY_F1:
		nValue = uiProcBoxSelect(pWnd, x, y, w, h, &bResult, dbSetupSystemNew.byF1Status, UISTR_FUNC_START, UISTR_FUNC_END);
		if (bResult)
			dbSetupSystemNew.byF1Status = nValue;
		break;
	case UISTR_MENU_ADVANCEDSETTING_FUNCKEY_F2:
		nValue = uiProcBoxSelect(pWnd, x, y, w, h, &bResult, dbSetupSystemNew.byF2Status, UISTR_FUNC_START, UISTR_FUNC_END);
		if (bResult)
			dbSetupSystemNew.byF2Status = nValue;
		break;
	case UISTR_MENU_ADVANCEDSETTING_FUNCKEY_F3:
		nValue = uiProcBoxSelect(pWnd, x, y, w, h, &bResult, dbSetupSystemNew.byF3Status, UISTR_FUNC_START, UISTR_FUNC_END);
		if (bResult)
			dbSetupSystemNew.byF3Status = nValue;
		break;
	case UISTR_MENU_ADVANCEDSETTING_FUNCKEY_F4:
		nValue = uiProcBoxSelect(pWnd, x, y, w, h, &bResult, dbSetupSystemNew.byF4Status, UISTR_FUNC_START, UISTR_FUNC_END);
		if (bResult)
			dbSetupSystemNew.byF4Status = nValue;
		break;
	case UISTR_MENU_POWERMANAGE_POWEROFF:
		nValue = uiProcBoxTime(pWnd, x, y, w, h, &bResult, dbSetupSystemNew.dwAutoPoweroffTime);
		if (bResult)
		{
			if(nValue && (DWORD)nValue == dbSetupSystemNew.dwAutoPoweronTime)
			{
				uiSoundOut(SOUND_ERROR, UI_BUZZER_ERROR);
				uiLcdMessageBox(UI_MSG_OK,UISTR_STATUS_MSG_INPUT_ERROR,UI_MSGTIMEOUT);
				break;
			}
			dbSetupSystemNew.dwAutoPoweroffTime = nValue;
		}
		break;
	case UISTR_MENU_POWERMANAGE_POWERON:
		nValue = uiProcBoxTime(pWnd, x, y, w, h, &bResult, dbSetupSystemNew.dwAutoPoweronTime);
		if (bResult)
			dbSetupSystemNew.dwAutoPoweronTime = nValue;
		break;
	case UISTR_MENU_POWERMANAGE_SLEEP:
		nValue = uiProcBoxTime(pWnd, x, y, w, h, &bResult, dbSetupSystemNew.dwAutoSleepTime);
		if (bResult)
			if(nValue && (DWORD)nValue == dbSetupSystemNew.dwAutoPoweronTime)
			{
				uiSoundOut(SOUND_ERROR, UI_BUZZER_ERROR);
				uiLcdMessageBox(UI_MSG_OK,UISTR_STATUS_MSG_INPUT_ERROR,UI_MSGTIMEOUT);
				break;
			}
			dbSetupSystemNew.dwAutoSleepTime = nValue;
		break;
	case UISTR_MENU_POWERMANAGE_POWERKEYUSE:
		nValue = uiProcBoxSelect(pWnd, x, y, w, h, &bResult, dbSetupSystemNew.bPowerkeyLock, UISTR_YESNO_START, UISTR_YESNO_END);
		if (bResult)
			dbSetupSystemNew.bPowerkeyLock = nValue;
		break;
	case UISTR_MENU_POWERMANAGE_IDLE_POWEROFF:
		nValue = uiProcBoxNumber(pWnd, x, y, w, h, &bResult, dbSetupSystemNew.nIdletimeForPoweroff, 0, 9999, TRUE, UISTR_UNIT_MINUTE);
		if (bResult)
			dbSetupSystemNew.nIdletimeForPoweroff = nValue;
		break;
	case UISTR_MENU_POWERMANAGE_IDLE_SLEEP:
		nValue = uiProcBoxNumber(pWnd, x, y, w, h, &bResult, dbSetupSystemNew.nIdletimeForSleep, 0, 9999, TRUE, UISTR_UNIT_MINUTE);
		if (bResult)
			dbSetupSystemNew.nIdletimeForSleep = nValue;
		break;
	case UISTR_MENU_POWERMANAGE_IDLE_LCDSWITCH:
		nValue = uiProcBoxNumber(pWnd, x, y, w, h, &bResult, dbSetupSystemNew.nIdletimeForLcdswitch, 0, 9999, TRUE, UISTR_UNIT_MINUTE);
		if (bResult)
			dbSetupSystemNew.nIdletimeForLcdswitch = nValue;
		break;
	case UISTR_MENU_COMMSETTING_DEVICEID:
		nValue = uiProcBoxNumber(pWnd, x, y, w, h, &bResult, dbSetupSystemNew.nMachineID, 1, 9999, FALSE, 0);
		if (bResult)
			dbSetupSystemNew.nMachineID = nValue;
		break;
	case UISTR_MENU_COMMSETTING_RS232USE:
		nValue = uiProcBoxSelect(pWnd, x, y, w, h, &bResult, dbSetupSystemNew.bRS232Use, UISTR_YESNO_START, UISTR_YESNO_END);
		if (bResult)
			dbSetupSystemNew.bRS232Use = nValue;
		break;
	case UISTR_MENU_COMMSETTING_RS485USE:
		nValue = uiProcBoxSelect(pWnd, x, y, w, h, &bResult, dbSetupSystemNew.bRS485Use, UISTR_YESNO_START, UISTR_YESNO_END);
		if (bResult)
			dbSetupSystemNew.bRS485Use = nValue;
		break;
	case UISTR_MENU_COMMSETTING_BAUDRATE:
		nValue = uiProcBoxSelect(pWnd, x, y, w, h, &bResult, dbSetupSystemNew.nBaudrate, UISTR_BPS_START, UISTR_BPS_END);
		if (bResult)
			dbSetupSystemNew.nBaudrate = nValue;
		break;
	case UISTR_MENU_COMMSETTING_ETHERNETUSE:
		nValue = uiProcBoxSelect(pWnd, x, y, w, h, &bResult, dbSetupSystemNew.bEthernetUse, UISTR_YESNO_START, UISTR_YESNO_END);
		if (bResult)
			dbSetupSystemNew.bEthernetUse = nValue;
		break;
	case UISTR_MENU_COMMSETTING_IPADDRESS:
		if (!dbSetupSystemNew.bDHCPUse)
		{
			nValue = uiProcBoxIPAddress(pWnd, x, y, w, h, &bResult, dbSetupSystemNew.ipAddress);
			if (bResult)
				dbSetupSystemNew.ipAddress = (DWORD)nValue;
		}
		break;
	case UISTR_MENU_COMMSETTING_MASKADDRESS:
		if (!dbSetupSystemNew.bDHCPUse)
		{
			nValue = uiProcBoxIPAddress(pWnd, x, y, w, h, &bResult, dbSetupSystemNew.ipSubnetMask);
			if (bResult)
				dbSetupSystemNew.ipSubnetMask = (DWORD)nValue;
		}
		break;
	case UISTR_MENU_COMMSETTING_GWADDRESS:
		if (!dbSetupSystemNew.bDHCPUse)
		{
			nValue = uiProcBoxIPAddress(pWnd, x, y, w, h, &bResult, dbSetupSystemNew.ipDefaultGateway);
			if (bResult)
				dbSetupSystemNew.ipDefaultGateway = (DWORD)nValue;
		}
		break;
	case UISTR_MENU_COMMSETTING_COMMPWD:
		nValue = uiProcBoxNumber(pWnd, x, y, w, h, &bResult, dbSetupSystemNew.dwCommPassword, 0, 99999999, TRUE, 0);
		if (bResult)
			dbSetupSystemNew.dwCommPassword = nValue;
		break;
	case UISTR_MENU_COMMSETTING_DHCPUSE:
		nValue = uiProcBoxSelect(pWnd, x, y, w, h, &bResult, dbSetupSystemNew.bDHCPUse, UISTR_YESNO_START, UISTR_YESNO_END);
		if (bResult)
			dbSetupSystemNew.bDHCPUse = nValue;
		break;
	case UISTR_MENU_COMMSETTING_PCBACKGROUND:
         if (dbSetupTotal.setSystem.szHostByName[0] == 0)   
		 {                                                  
		nValue = uiProcBoxIPAddress(pWnd, x, y, w, h, &bResult, dbSetupSystemNew.ipPCBackground);
		if (bResult)
			dbSetupSystemNew.ipPCBackground = (DWORD)nValue;
		 }                                                 
		break;
	case UISTR_MENU_COMMSETTING_PCBACKPORT:
		nValue = uiProcBoxNumber(pWnd, x, y, w, h, &bResult, dbSetupSystemNew.wPortNumBack, 0, 9999, TRUE, 0);
		if (bResult)
			dbSetupSystemNew.wPortNumBack = nValue;
		break;
	case UISTR_REMOTE_ATTENDANCE_FUN:
		nValue = uiProcBoxSelect(pWnd, x, y, w, h, &bResult, dbSetupSystemNew.bRemoteAttUse, UISTR_YESNO_START, UISTR_YESNO_END);
		if (bResult)
			dbSetupSystemNew.bRemoteAttUse = nValue;
		break;
	case UISTRr_REMOTE_DATA_SAVE_TIME:
		nValue = uiProcBoxNumber(pWnd, x, y, w, h, &bResult, dbSetupSystemNew.dwDataSaveTime, 0, 255, TRUE, 0);
		if (bResult)
			dbSetupSystemNew.dwDataSaveTime = nValue;
		break;	
	case UISTR_MENU_LOGSETTING_MLOGWARNING:
		nValue = uiProcBoxNumber(pWnd, x, y, w, h, &bResult, dbSetupSystemNew.nMLogWarning, 0, 100, TRUE, UISTR_UNIT_LOG);
		if (bResult)
			dbSetupSystemNew.nMLogWarning = nValue;
		break;
	case UISTR_MENU_LOGSETTING_GLOGWARNING:
		nValue = uiProcBoxNumber(pWnd, x, y, w, h, &bResult, dbSetupSystemNew.nGLogWarning, 0, 1000, TRUE, UISTR_UNIT_LOG);
		if (bResult)
			dbSetupSystemNew.nGLogWarning = nValue;
		break;
	case UISTR_MENU_LOGSETTING_REVERIFYTIME:
		nValue = uiProcBoxNumber(pWnd, x, y, w, h, &bResult, dbSetupSystemNew.nReverifyTime, 0, 255, TRUE, UISTR_UNIT_MINUTE);
		if (bResult)
			dbSetupSystemNew.nReverifyTime = nValue;
		break;
	case UISTR_MENU_ACSETTING_LOCKTIME:
		nValue = uiProcBoxNumber(pWnd, x, y, w, h, &bResult, dbSetupSystemNew.nLockTime, 0, 10, TRUE, UISTR_UNIT_SECOND);
		if (bResult)
			dbSetupSystemNew.nLockTime = nValue;
		break;
	case UISTR_MENU_ACSETTING_OPENTIME:
		nValue = uiProcBoxNumber(pWnd, x, y, w, h, &bResult, dbSetupSystemNew.nDoorOpenTime, 0, 255, TRUE, UISTR_UNIT_SECOND);
		if (bResult)
			dbSetupSystemNew.nDoorOpenTime = nValue;
		break;
	case UISTR_MENU_ACSETTING_DOORSENSOR:
		nValue = uiProcBoxSelect(pWnd, x, y, w, h, &bResult, dbSetupSystemNew.nDoorSensorStatus, UISTR_DOORSENSOR_START, UISTR_DOORSENSOR_END);
		if (bResult)
			dbSetupSystemNew.nDoorSensorStatus = nValue;
		break;
	case UISTR_MENU_ACSETTING_ILLEGALVERIFYWARNING:
		nValue = uiProcBoxNumber(pWnd, x, y, w, h, &bResult, dbSetupSystemNew.nIllegalVerifyWarning, 0, 255, TRUE, UISTR_UNIT_TIMES);
		if (bResult)
			dbSetupSystemNew.nIllegalVerifyWarning = nValue;
		break;
	case UISTR_MENU_ACSETTING_ANTIPASS:
		nValue = uiProcBoxSelect(pWnd, x, y, w, h, &bResult, dbSetupSystemNew.byAntipassStatus, UISTR_ANTIPASS_START, UISTR_ANTIPASS_END);
		if (bResult)
			dbSetupSystemNew.byAntipassStatus = nValue;
		break;
	case UISTR_MENU_ACSETTING_ACCONTROLLERUSE:
		nValue = uiProcBoxNumber(pWnd, x, y, w, h, &bResult, dbSetupSystemNew.dwBindingID, 0, 99999999, TRUE, 0);
		if (bResult)
			dbSetupSystemNew.dwBindingID = nValue;
		break;
	case UISTR_MENU_ACSETTING_GROUP_DEFAULT_VM:
		nValue = uiProcBoxSelect(pWnd, x, y, w, h, &bResult, (int)dbSetupSystemNew.byDefaultGVM, UISTR_VERIFYMODE_START, UISTR_VERIFYMODE_END);
		if (bResult)
			dbSetupSystemNew.byDefaultGVM = (BYTE)INDEX2VERIFYMODE(nValue);
		break;
	case UISTR_MENU_ACSETTING_GROUP_1:
	case UISTR_MENU_ACSETTING_GROUP_2:
	case UISTR_MENU_ACSETTING_GROUP_3:
	case UISTR_MENU_ACSETTING_GROUP_4:
	case UISTR_MENU_ACSETTING_GROUP_5:
		nValue = uiProcBoxTimeGroup(
			pWnd, x, y, w, h, &bResult,
			*(int*)&dbSetupTimezoneNew.tzGroup[nItemStr - UISTR_MENU_ACSETTING_GROUP_1],
			dbSetupTimezoneNew.tzGrupVM[nItemStr - UISTR_MENU_ACSETTING_GROUP_1], &nValue1);
		if (bResult)
		{
			*(int*)&dbSetupTimezoneNew.tzGroup[nItemStr - UISTR_MENU_ACSETTING_GROUP_1] = nValue;
			dbSetupTimezoneNew.tzGrupVM[nItemStr - UISTR_MENU_ACSETTING_GROUP_1] = (BYTE)nValue1;
		}
		break;
	case UISTR_MENU_ACSETTING_USERTIMEZONE_GROUP:
		nValue = uiProcBoxNumber(pWnd, x, y, w, h, &bResult, (int)gUserInfoTemp.TIMEGROUP, 1, 5, FALSE, 0);
		if (bResult)
			gUserInfoTemp.TIMEGROUP = (BYTE)nValue;
		break;
	case UISTR_MENU_ACSETTING_USERTIMEZONE_GTZUSE:
		nValue = uiProcBoxSelect(pWnd, x, y, w, h, &bResult, DbUserInfoFlagGTZStatusGet(&gUserInfoTemp), UISTR_YESNO_START, UISTR_YESNO_END);
		if (bResult)
		{
			DbUserInfoFlagGTZStatusSet(&gUserInfoTemp, nValue);
			if (DbUserInfoFlagGTZStatusGet(&gUserInfoTemp) && gUserInfoTemp.TIMEGROUP > 0)
			{
				gUserInfoTemp.UserTZ[0] = dbSetupTimezoneNew.tzGroup[gUserInfoTemp.TIMEGROUP - 1].bGroupA;
				gUserInfoTemp.UserTZ[1] = dbSetupTimezoneNew.tzGroup[gUserInfoTemp.TIMEGROUP - 1].bGroupB;
				gUserInfoTemp.UserTZ[2] = dbSetupTimezoneNew.tzGroup[gUserInfoTemp.TIMEGROUP - 1].bGroupC;
			}
		}
		break;
	case UISTR_MENU_ACSETTING_USERTIMEZONE_TZ1:
	case UISTR_MENU_ACSETTING_USERTIMEZONE_TZ2:
	case UISTR_MENU_ACSETTING_USERTIMEZONE_TZ3:
		nValue = uiProcBoxNumber(pWnd, x, y, w, h, &bResult, (int)gUserInfoTemp.UserTZ[nItemStr - UISTR_MENU_ACSETTING_USERTIMEZONE_TZ1], 0, 50, FALSE, 0);
		if (bResult)
		{
			DbUserInfoFlagGTZStatusSet(&gUserInfoTemp, FALSE);
			gUserInfoTemp.UserTZ[nItemStr - UISTR_MENU_ACSETTING_USERTIMEZONE_TZ1] = (BYTE)nValue;
		}
		break;
	case UISTR_MENU_ACSETTING_USERTIMEZONE_GVMUSE:
		nValue = uiProcBoxSelect(pWnd, x, y, w, h, &bResult, DbUserInfoFlagGVMStatusGet(&gUserInfoTemp), UISTR_YESNO_START, UISTR_YESNO_END);
		if (bResult)
			DbUserInfoFlagGVMStatusSet(&gUserInfoTemp, nValue);
		break;
	case UISTR_MENU_ACSETTING_USERTIMEZONE_VERIFYMODE:
		nValue = uiProcBoxSelect(pWnd, x, y, w, h, &bResult, (int)gUserInfoTemp.VERIFYMODE, UISTR_VERIFYMODE_START, UISTR_VERIFYMODE_END);
		if (bResult)
			gUserInfoTemp.VERIFYMODE = INDEX2VERIFYMODE(nValue);
		break;
	case UISTR_MENU_ACSETTING_LOCKGROUP_MAIN:
		nValue = uiProcBoxNumber(pWnd, x, y, w, h, &bResult, dbSetupSystemNew.nLockGroupMain, 0, 5, TRUE, 0);
		if (bResult)
			dbSetupSystemNew.nLockGroupMain = nValue;
		break;
	case UISTR_MENU_ACSETTING_LOCKGROUP_1:
	case UISTR_MENU_ACSETTING_LOCKGROUP_2:
	case UISTR_MENU_ACSETTING_LOCKGROUP_3:
	case UISTR_MENU_ACSETTING_LOCKGROUP_4:
	case UISTR_MENU_ACSETTING_LOCKGROUP_5:
	case UISTR_MENU_ACSETTING_LOCKGROUP_6:
	case UISTR_MENU_ACSETTING_LOCKGROUP_7:
	case UISTR_MENU_ACSETTING_LOCKGROUP_8:
	case UISTR_MENU_ACSETTING_LOCKGROUP_9:
	case UISTR_MENU_ACSETTING_LOCKGROUP_10:
		nValue = uiProcBoxNumber(
			pWnd, x, y, w, h, &bResult,
			LOCKGROUP2NUMBER(dbSetupTimezoneNew.tzLockGroup[nItemStr - UISTR_MENU_ACSETTING_LOCKGROUP_1]),
			0, 55555, FALSE, 0, 1, 5, FALSE);
		if (bResult)
		{
			nValue1 = dbSetupTimezoneNew.tzLockGroup[nItemStr - UISTR_MENU_ACSETTING_LOCKGROUP_1];
			dbSetupTimezoneNew.tzLockGroup[nItemStr - UISTR_MENU_ACSETTING_LOCKGROUP_1] = 0;
			if (LOCKGROUP_VALIDCHECK(dbSetupTimezoneNew.tzLockGroup, (BYTE)NUMBER2LOCKGROUP(nValue)))
				dbSetupTimezoneNew.tzLockGroup[nItemStr - UISTR_MENU_ACSETTING_LOCKGROUP_1] = NUMBER2LOCKGROUP(nValue);
			else
			{
				dbSetupTimezoneNew.tzLockGroup[nItemStr - UISTR_MENU_ACSETTING_LOCKGROUP_1] = nValue1;
				uiLcdMessageBox(UI_MSG_ERROR, UISTR_VERIFY_INVALID_GROUP, UI_MSGTIMEOUT);
			}
		}
		break;
	case UISTR_MENU_ACSETTING_DURESS_PWD:
		nValue = uiProcBoxSelect(pWnd, x, y, w, h, &bResult, dbSetupSystemNew.bPwdAlarmUse, UISTR_YESNO_START, UISTR_YESNO_END);
		if (bResult)
			dbSetupSystemNew.bPwdAlarmUse = nValue;
		break;
	case UISTR_MENU_ACSETTING_DURESS_SOSKEY:
		nValue = uiProcBoxSelect(pWnd, x, y, w, h, &bResult, dbSetupSystemNew.bSOSKeyUse, UISTR_YESNO_START, UISTR_YESNO_END);
		if (bResult)
			dbSetupSystemNew.bSOSKeyUse = nValue;
		break;
	case UISTR_MENU_ACSETTING_DURESS_ALARMDELAY:
		nValue = uiProcBoxNumber(pWnd, x, y, w, h, &bResult, dbSetupSystemNew.nAlarmDelay, 0, 255, TRUE, UISTR_UNIT_SECOND);
		if (bResult)
			dbSetupSystemNew.nAlarmDelay = nValue;
		break;
	case UISTR_MENU_ACSETTING_GROUPVERIFYMODE_GROUP1:
	case UISTR_MENU_ACSETTING_GROUPVERIFYMODE_GROUP2:
	case UISTR_MENU_ACSETTING_GROUPVERIFYMODE_GROUP3:
	case UISTR_MENU_ACSETTING_GROUPVERIFYMODE_GROUP4:
	case UISTR_MENU_ACSETTING_GROUPVERIFYMODE_GROUP5:
		nValue = uiProcBoxSelect(
			pWnd, x, y, w, h, &bResult,
			dbSetupTimezoneNew.tzGrupVM[nItemStr-UISTR_MENU_ACSETTING_GROUPVERIFYMODE_GROUP1],
			UISTR_VERIFYMODE_START, UISTR_VERIFYMODE_END);
		if (bResult)
		{
			dbSetupTimezoneNew.tzGrupVM[nItemStr-UISTR_MENU_ACSETTING_GROUPVERIFYMODE_GROUP1] = (BYTE)nValue;
		}
		break;
	case UISTR_MENU_USERENROLLCOUNT:
		break;
	case UISTR_MENU_FPENROLLCOUNT:
		break;
	case UISTR_MENU_GLOGCOUNT:
		break;
	case UISTR_MENU_MLOGCOUNT:
		break;
	case UISTR_MENU_USEDMEMORY:
		break;
	case UISTR_MENU_DNSSERVERIP:
        // if (dbSetupTotal.setSystem.szHostByName[0] == 0)  
         if (dbSetupSystemNew.bDHCPUse==0)
		 {                                                  
			nValue = uiProcBoxIPAddress(pWnd, x, y, w, h, &bResult, dbSetupSystemNew.DNSserverIp);
			if (bResult)
				dbSetupSystemNew.DNSserverIp = (DWORD)nValue;
		 }                                                 
		break;		
	default:
		break;
	}

	g_uiMenuRedrawFlag = TRUE;
	return TRUE;
}

BOOL uiProcMenuCustom(QWidget* /*pWnd*/, int nItemStr)
{
	BOOL bResult;

	switch (nItemStr)
	{
	case UISTR_MENU_ALARMREMOVE:
		if (uiLcdMessageBox(UI_MSG_QUESTION, UISTR_ACTION_CONFIRM, UITIME_OUT))
		{
			uiAlarmStop();
			uiEventSend_ALARM_OFF(-1, ALARMRELEASE_MANAGER, g_uiProcStatus.nIDCurrentMgr);
			uiLcdMessageBox(UI_MSG_OK, UISTR_ACTION_SUCCESS, UI_MSGTIMEOUT);
		}
		break;
	case UISTR_MENU_ENROLL_FP:
	case UISTR_MENU_ENROLL_RFCARD:
	case UISTR_MENU_ENROLL_PWD:
	case UISTR_MENU_ENROLL_VOICE:
	case UISTR_MENU_ENROLL_PHOTO:
		uiProcEnroll(&gUserInfoTemp, nItemStr);
		break;
	case UISTR_MENU_DELETE_FP:
	case UISTR_MENU_DELETE_RFCARD:
	case UISTR_MENU_REMOVE_PWD:
	case UISTR_MENU_DELETE_VOICE:
	case UISTR_MENU_DELETE_PHOTO:
	case UISTR_MENU_DELETE_ALL:
		uiProcEnrollDelete(gUserInfoTemp.ID, nItemStr);
		break;
	case UISTR_MENU_ADVANCEDSETTING_LOGDELETEALL:
		if (uiLcdMessageBox(UI_MSG_QUESTION, UISTR_ACTION_CONFIRM, UITIME_OUT))
		{
			bResult = Db_DeleteAllLogData();
			uiLogSlogAdd(g_uiProcStatus.nIDCurrentMgr, SLOG_DELETE_ALL_LOG, 0, bResult);
			uiLcdMessageBox(UI_MSG_OK, UISTR_ACTION_SUCCESS, UI_MSGTIMEOUT);
		}
		break;
	case UISTR_MENU_ADVANCEDSETTING_ENROLLDELETEALL:
		if (!Db_GetUserCount())
		{
			uiLcdMessageBox(UI_MSG_ERROR, UISTR_ENROLLDELETE_NODATA, UI_MSGTIMEOUT);
			break;
		}
		if (uiLcdMessageBox(UI_MSG_QUESTION, UISTR_ACTION_CONFIRM, UITIME_OUT))
		{
			bResult = Db_DeleteAllEnrollData();
			uiLogSlogAdd(g_uiProcStatus.nIDCurrentMgr, SLOG_DELETE_ALL, 0, bResult);
			uiLcdMessageBox(UI_MSG_OK, UISTR_ACTION_SUCCESS, UI_MSGTIMEOUT);
		}
		break;
	case UISTR_MENU_ADVANCEDSETTING_DEFAULT:
		if (uiLcdMessageBox(UI_MSG_QUESTION, UISTR_ACTION_CONFIRM, UITIME_OUT))
		{
			DbSetupTotal2Default();
// 			Db_FreeAllData();
// 			Db_LoadAllData(FALSE);
			dbSetupSystemNew = dbSetupTotal.setSystem;
			dbSetupTimezoneNew = dbSetupTotal.setTimezone;
			uiLogSlogAdd(g_uiProcStatus.nIDCurrentMgr, SLOG_RESTORE, 0, TRUE);
			uiLcdMessageBox(UI_MSG_OK, UISTR_ACTION_SUCCESS, UI_MSGTIMEOUT);
		}
		break;
	case UISTR_MENU_ADVANCEDSETTING_FWUPGRADE:
		tcpclient_connect_threadStop();
		uiSL811_FirmwareUpgrade();
		//SB_EXEC("reboot"); 
		SystemReset();
		break;
	case UISTR_MENU_ADVANCEDSETTING_BRIGHT_ADJUST:
		{
			DWORD dwMechanical, dwExposure;
			if (uiCMOSAdjustBrightness(&dwMechanical, &dwExposure))
			{
				dbSetupTotal.setNoMenu.dwMechanical = dwMechanical;
				dbSetupTotal.setNoMenu.dwExpose = dwExposure;
				DbSetupTotalWrite();
				uiLcdMessageBox(UI_MSG_OK, UISTR_STATUS_BRIGHT_ADJUST_SUCCESS, UI_MSGTIMEOUT);
			}
			else
				uiLcdMessageBox(UI_MSG_ERROR, UISTR_CHECK_SENSOR, UI_MSGTIMEOUT);
		}
		break;
	case UISTR_MENU_POWERMANAGE_BELL:
		DIALOGBOX(CBellSetup);
		break;
	case UISTR_MENU_POWERMANAGE_TRSWITCH:
		DIALOGBOX(CTrSetup);
		break;
	case UISTR_MENU_ACSETTING_TIMEZONE:
		DIALOGBOX(CTimezoneSetup);
		break;
	case UISTR_MENU_ACSETTING_DURESS_MANAGE_ENROLL:
		{
			int nRet = DIALOGBOX_RET_HAS_NAME(CEnrollFP, "EnrollDuress");
			for (int i=BACKUP_FINGER0; i<=BACKUP_FINGER9; i++)
			{
				if (nRet & (1 << i))
					DbUserInfoSetDuress(gUserInfoTemp.ID, i, 1);
			}
		}
		break;
	case UISTR_MENU_ACSETTING_DURESS_MANAGE_SET:
		DIALOGBOXEX_HAS_NAME(CDuressFP, TRUE, "DuressFPSet");
		break;
	case UISTR_MENU_ACSETTING_DURESS_MANAGE_REMOVE:
		if (!DbUserInfoGetDuressCount(gUserInfoTemp.ID))
		{
			uiLcdMessageBox(UI_MSG_ERROR, UISTR_DURESS_NOEXIST, UI_MSGTIMEOUT);
			break;
		}
		DIALOGBOXEX_HAS_NAME(CDuressFP, FALSE, "DuressFPRemove");
		break;
	case UISTR_MENU_ACSETTING_DURESS_MANAGE_REMOVEALL:
		if (!DbUserInfoGetDuressCount(gUserInfoTemp.ID))
		{
			uiLcdMessageBox(UI_MSG_ERROR, UISTR_DURESS_NOEXIST, UI_MSGTIMEOUT);
			break;
		}
		if (uiLcdMessageBox(UI_MSG_QUESTION, UISTR_ACTION_CONFIRM, UITIME_OUT))
		{
			DbUserInfoSetDuress(gUserInfoTemp.ID, BACKUP_ALL, 0);
			uiLcdMessageBox(UI_MSG_OK, UISTR_ACTION_SUCCESS, UI_MSGTIMEOUT);
		}
		break;
	case UISTR_MENU_SELFTEST_ALL:
		DIALOGBOX(CSelftestAll);
		break;
	case UISTR_MENU_SELFTEST_MEMORY:
		DIALOGBOX(CSelftestMemory);
		break;
	case UISTR_MENU_SELFTEST_LCD:
//		DIALOGBOX(CSelftestLcd);
		uiSelftestLcd(UITIME_OUT);
		break;
	case UISTR_MENU_SELFTEST_SOUND:
		DIALOGBOXEX(CSelftestSound, UITIME_OUT);
		break;
	case UISTR_MENU_SELFTEST_SENSOR:
		DIALOGBOXEX(CSelftestSensor, UITIME_OUT);
		break;
	case UISTR_MENU_SELFTEST_KEYBOARD:
		DIALOGBOXEX(CSelftestKeyboard, UITIME_OUT);
		break;
	case UISTR_MENU_SELFTEST_RTC:
		DIALOGBOXEX(CSelftestRtc, UITIME_OUT);
		break;
// 	case UISTR_MENU_SELFTEST_MP3:
// 		break;
	case UISTR_MENU_ALLGLOGDOWNLOAD:
		uiSL811_DownloadAllGlog(&bResult);
		break;
	case UISTR_MENU_ALLMLOGDOWNLOAD:
		uiSL811_DownloadAllSlog(&bResult);
		break;
	case UISTR_MENU_GLOGDOWNLOAD:
		uiSL811_DownloadGlog(&bResult);
		break;
	case UISTR_MENU_MLOGDOWNLOAD:
		uiSL811_DownloadSlog(&bResult);
		break;
	case UISTR_MENU_USERINFODOWNLOAD:
		uiSL811_DownloadAllEnroll();
		break;
	case UISTR_MENU_USERINFOUPLOAD:
		uiSL811_UploadAllEnroll();
		break;
	case UISTR_MENU_MSGUPLOAD:
		uiSL811_MsgUpload();
		break;
	case UISTR_MENU_MP3UPLOAD:
		uiSL811_MP3Upload();
		break;
	case UISTR_MENU_FREESPACES:
		break;
	case UISTR_MENU_DEVICEINFO:
		break;
	case UISTR_MENU_GLOGVIEW:
		DIALOGBOXEX(CSearchLog, CSearchLog::LOG_GLOG);
//		DIALOGBOX(CGLogList);
		break;
	case UISTR_MENU_MLOGVIEW:
		DIALOGBOXEX(CSearchLog, CSearchLog::LOG_SLOG);
//		DIALOGBOX(CSLogList);
		break;
	case UISTR_MENU_ENROLLVIEW:
		{
			DIALOGBOX(CSearchUser);
// 			int nRet = DIALOGBOX_RET(CSearchUser);
// 			if (nRet)
// 			{
// 				DIALOGBOX(CUserList);
// 			}
		}
		break;
	case UISTR_MENU_ENROLLNEW:
		xprintf("loveywm1\r\n");
		DIALOGBOXEX(CEnrollStep1,CEnrollStep1::ID_NEW);  
		break;  
	case UISTR_MENU_ENROLLEDIT:
		DIALOGBOX(CUserManage);
		break;
	case UISTR_MENU_ENROLLDEL:
        		DIALOGBOX(CUserDel);
		break;
	case UISTR_MENU_MESSINFO:
		DIALOGBOX(CMsgManage);
		
	case	UISTR_MENU_ENROLL_PICTURE:
		DIALOGBOX(CEnrollPhoto);
		break;
	}

	return TRUE;
}

void MenuSettingStart(BOOL bFirst = FALSE)
{

	if (bFirst)
	{
		USER_INFO *pUserInfo = (USER_INFO*)DbUserInfoGetPointer(gUserInfoTemp.ID);
		if (pUserInfo)
			memcpy(&gUserInfoTemp, pUserInfo, sizeof(USER_INFO));
		dbSetupSystemNew = dbSetupTotal.setSystem;
		nLanguage = dbSetupTotal.setSystem.nLanguage;
		dbSetupTimezoneNew = dbSetupTotal.setTimezone;
		dbSetupTotalTemp = dbSetupTotal;
	}
	else
	{
		int i;
		BYTE *pSrcSystem    = (BYTE*)&dbSetupTotal.setSystem;
		BYTE *pSrcTimezone  = (BYTE*)&dbSetupTotal.setTimezone;
		BYTE *pDstSystem    = (BYTE*)&dbSetupSystemNew;
		BYTE *pDstTimezone  = (BYTE*)&dbSetupTimezoneNew;
		BYTE *pTempSystem   = (BYTE*)&dbSetupTotalTemp.setSystem;
		BYTE *pTempTimezone = (BYTE*)&dbSetupTotalTemp.setTimezone;

		for (i = 0; i < (int)sizeof(DBSETUP_SYSTEM); i++)
		{
			if (pSrcSystem[i] != pTempSystem[i])
				pDstSystem[i] = pSrcSystem[i];
		}
		for (i = 0; i < (int)sizeof(DBSETUP_TIMEZONE); i++)
		{
			if (pSrcTimezone[i] != pTempTimezone[i])
				pDstTimezone[i] = pSrcTimezone[i];
		}
	}
}

void MenuSettingEnd(int nStrTitle)
{
	USER_INFO *pUserInfo = NULL;
	BOOL bChangedSystem = FALSE;
	BOOL bChangedUserInfo = FALSE;
	UINT64 nID = 0;
	BYTE bySLogAction = SLOG_SETTINGCHANGED;
	BYTE bySLogResult = nStrTitle;
	BYTE bySLogAction1[9];
	int i;

	memcpy(&dbSetupTotalTemp, &dbSetupTotal, sizeof(DBSETUP_TOTAL));
	memset(&bySLogAction1, 0, sizeof(bySLogAction1));

	switch (nStrTitle)
	{
	case UISTR_MENU_MAINMENU:
		break;
	case UISTR_MENU_USERMANAGE:
		break;
	case UISTR_MENU_USBMANAGE:
		break;
	case UISTR_MENU_SYSTEMSETTING:
		break;
	case UISTR_MENU_MAINSETTING:
		dbSetupTotal.setSystem.nLanguage =nLanguage;
		dbSetupTotalTemp.setSystem.nLanguage = dbSetupSystemNew.nLanguage;
		dbSetupTotalTemp.setSystem.nManagersNumber = dbSetupSystemNew.nManagersNumber;
//		dbSetupTotalTemp.setSystem.byTheme = dbSetupSystemNew.byTheme;
		dbSetupTotalTemp.setSystem.bVoiceOut = dbSetupSystemNew.bVoiceOut;
		dbSetupTotalTemp.setSystem.nVolume = dbSetupSystemNew.nVolume;
		dbSetupTotalTemp.setSystem.bKeyTones = dbSetupSystemNew.bKeyTones;
		dbSetupTotalTemp.setSystem.nBackgroupIconFile = dbSetupSystemNew.nBackgroupIconFile;   //xf 091106
		break;
	case UISTR_MENU_MAINSETTING_TIME:
		dbSetupTotalTemp.setSystem.nTimeFormat = dbSetupSystemNew.nTimeFormat;
		dbSetupTotalTemp.setSystem.nDateFormat = dbSetupSystemNew.nDateFormat;
		break;
	case UISTR_MENU_COMMSETTING:
		if (dbSetupTotalTemp.setSystem.nMachineID != dbSetupSystemNew.nMachineID)
			bySLogAction1[0] = SLOG_SET_ID;
		if (dbSetupTotalTemp.setSystem.ipAddress != dbSetupSystemNew.ipAddress)
			bySLogAction1[1] = SLOG_SET_IP;
		if (dbSetupTotalTemp.setSystem.ipSubnetMask != dbSetupSystemNew.ipSubnetMask)
			bySLogAction1[2] = SLOG_SET_MASK;
		if (dbSetupTotalTemp.setSystem.ipDefaultGateway != dbSetupSystemNew.ipDefaultGateway)
			bySLogAction1[3] = SLOG_SET_GATEWAY;
	//	if (dbSetupTotalTemp.setSystem.dwCommPassword != dbSetupSystemNew.dwCommPassword)
	//		bySLogAction1[4] = SLOG_SET_COMMPWD;
	//	if (dbSetupTotalTemp.setSystem.bDHCPUse != dbSetupSystemNew.bDHCPUse)
       //		bySLogAction1[5] = SLOG_SET_DHCP;
		if (dbSetupTotalTemp.setSystem.ipPCBackground != dbSetupSystemNew.ipPCBackground)
			bySLogAction1[6] = SLOG_SET_IPBACK;
		if (dbSetupTotalTemp.setSystem.DNSserverIp != dbSetupSystemNew.DNSserverIp)
			bySLogAction1[7] = SLOG_SET_DNS;
		if (dbSetupTotalTemp.setSystem.wPortNumBack != dbSetupSystemNew.wPortNumBack)
			bySLogAction1[8] = SLOG_SET_PORTBACK;
		dbSetupTotalTemp.setSystem.nMachineID = dbSetupSystemNew.nMachineID;
		dbSetupTotalTemp.setSystem.nBaudrate = dbSetupSystemNew.nBaudrate;
		dbSetupTotalTemp.setSystem.ipAddress = dbSetupSystemNew.ipAddress;
		dbSetupTotalTemp.setSystem.ipSubnetMask = dbSetupSystemNew.ipSubnetMask;
		dbSetupTotalTemp.setSystem.ipDefaultGateway = dbSetupSystemNew.ipDefaultGateway;
	//	dbSetupTotalTemp.setSystem.dwCommPassword = dbSetupSystemNew.dwCommPassword;
	//	dbSetupTotalTemp.setSystem.bDHCPUse = dbSetupSystemNew.bDHCPUse;
// 		dbSetupTotalTemp.setSystem.bRS232Use = dbSetupSystemNew.bRS232Use;
// 		dbSetupTotalTemp.setSystem.bRS485Use = dbSetupSystemNew.bRS485Use;
//		dbSetupTotalTemp.setSystem.bEthernetUse = dbSetupSystemNew.bEthernetUse;
		dbSetupTotalTemp.setSystem.ipPCBackground = dbSetupSystemNew.ipPCBackground;
		dbSetupTotalTemp.setSystem.DNSserverIp = dbSetupSystemNew.DNSserverIp;
              dbSetupTotalTemp.setSystem.wPortNumBack = dbSetupSystemNew.wPortNumBack;
		break;
	case UISTR_REMOTE_ATTENDANCE:
		dbSetupTotalTemp.setSystem.bRemoteAttUse = dbSetupSystemNew.bRemoteAttUse;
		dbSetupTotalTemp.setSystem.dwDataSaveTime = dbSetupSystemNew.dwDataSaveTime;
		break;	
	case UISTR_MENU_LOGSETTING:
		dbSetupTotalTemp.setSystem.nMLogWarning = dbSetupSystemNew.nMLogWarning;
		dbSetupTotalTemp.setSystem.nGLogWarning = dbSetupSystemNew.nGLogWarning;
		dbSetupTotalTemp.setSystem.nReverifyTime = dbSetupSystemNew.nReverifyTime;
		break;
	case UISTR_MENU_ADVANCEDSETTING:
		dbSetupTotalTemp.setSystem.bFPShow = dbSetupSystemNew.bFPShow;
		dbSetupTotalTemp.setSystem.dwSManagerPwd = dbSetupSystemNew.dwSManagerPwd;
		dbSetupTotalTemp.setSystem.nVerifyMode = dbSetupSystemNew.nVerifyMode;
		dbSetupTotalTemp.setSystem.dwCommPassword = dbSetupSystemNew.dwCommPassword;
		dbSetupTotalTemp.setSystem.bDHCPUse = dbSetupSystemNew.bDHCPUse;
		break;
	case UISTR_MENU_ADVANCEDSETTING_DAYLIGHT:
		dbSetupTotalTemp.setSystem.nDaylightOffset = dbSetupSystemNew.nDaylightOffset;
		dbSetupTotalTemp.setSystem.dwDaylightChangeTime = dbSetupSystemNew.dwDaylightChangeTime;
		dbSetupTotalTemp.setSystem.dwDaylightRestoreTime = dbSetupSystemNew.dwDaylightRestoreTime;
		break;
	case UISTR_MENU_POWERMANAGE:
		dbSetupTotalTemp.setSystem.dwAutoPoweronTime = dbSetupSystemNew.dwAutoPoweronTime;
		dbSetupTotalTemp.setSystem.dwAutoPoweroffTime = dbSetupSystemNew.dwAutoPoweroffTime;
		dbSetupTotalTemp.setSystem.dwAutoSleepTime = dbSetupSystemNew.dwAutoSleepTime;
		dbSetupTotalTemp.setSystem.bPowerkeyLock = dbSetupSystemNew.bPowerkeyLock;
		dbSetupTotalTemp.setSystem.nIdletimeForLcdswitch = dbSetupSystemNew.nIdletimeForLcdswitch;  //xf 091106
		break;
	case UISTR_MENU_POWERMANAGE_IDLE:
		dbSetupTotalTemp.setSystem.nIdletimeForPoweroff = dbSetupSystemNew.nIdletimeForPoweroff;
		dbSetupTotalTemp.setSystem.nIdletimeForSleep = dbSetupSystemNew.nIdletimeForSleep;
		dbSetupTotalTemp.setSystem.nIdletimeForLcdswitch = dbSetupSystemNew.nIdletimeForLcdswitch;
		break;
	case UISTR_MENU_SELFTEST:
		break;
	case UISTR_MENU_POWERMANAGE_BELL:
		memcpy(dbSetupTotalTemp.setTimezone.tzBell, dbSetupTimezoneNew.tzBell, sizeof(dbSetupTotalTemp.setTimezone.tzBell));
		break;
	case UISTR_MENU_POWERMANAGE_TRSWITCH:
		memcpy(dbSetupTotalTemp.setTimezone.tzTr, dbSetupTimezoneNew.tzTr, sizeof(dbSetupTotalTemp.setTimezone.tzTr));
		break;
	case UISTR_MENU_FREESPACES:
		break;
	case UISTR_MENU_DEVICEINFO:
		break;
	case UISTR_MENU_DATAVIEW:
		break;
	case UISTR_MENU_SYSINFOVIEW:
		break;
	default:
		bySLogResult = 0;
		break;
	}


	bChangedSystem = memcmp(&dbSetupTotal, &dbSetupTotalTemp, sizeof(DBSETUP_TOTAL));
	bChangedUserInfo = pUserInfo && memcmp(pUserInfo, &gUserInfoTemp, sizeof(USER_INFO));

	if (bChangedSystem || bChangedUserInfo)
	{
		if (uiLcdMessageBox(UI_MSG_QUESTION, UISTR_STATUS_SAVE_QUESTION, UITIME_OUT))
		{
			if (bChangedSystem)
			{
				nBackgroupIconFile = -1;   
				memcpy(&dbSetupTotal, &dbSetupTotalTemp, sizeof(DBSETUP_TOTAL));
				DbSetupTotalWrite();
				uiLogSlogAdd(g_uiProcStatus.nIDCurrentMgr, bySLogAction,  nID, bySLogResult);
				for (i = 0; i < 9; i++)
				{
					if (bySLogAction1[i] !=0)
						uiLogSlogAdd(g_uiProcStatus.nIDCurrentMgr, bySLogAction1[i], nID, bySLogResult);
				}
				nLanguage = dbSetupTotal.setSystem.nLanguage;
			}
			else if (bChangedUserInfo)
			{
				DbUserInfoEnroll(&gUserInfoTemp, BACKUP_ALL, NULL);
				uiLogSlogAdd(g_uiProcStatus.nIDCurrentMgr, bySLogAction, nID, bySLogResult);
				for (i = 0; i < 9; i++)
				{
					if (bySLogAction1[i] !=0)
						uiLogSlogAdd(g_uiProcStatus.nIDCurrentMgr, bySLogAction1[i], nID, bySLogResult);
				}
			}
			uiSoundOut(SOUND_OK, UI_BUZZER_OK);
		}
		else
		{
			if (dbSetupTotal.setSystem.nLanguage != dbSetupTotalTemp.setSystem.nLanguage)
				SET_LANGUAGE(dbSetupTotal.setSystem.nLanguage);
			MenuSettingStart();
		}
	}
}

//////////////////////////////////////////////////////////////////////////
CMenu::CMenu(QWidget *parent /* = NULL */)
	: CMainFrame(parent)
{
	m_bTerminateFlag = FALSE;
	ui.lblStatusText->hide();  
	ui.lblStatusIcon->hide();  
}

void CMenu::MenuProc(int nPopupMenuTitle /* = -1 */)
{
	int nKey;
	int i, j;
	int title, from, to;
    	int x, y, w, h, w_spacer, h_spacer;
	int nBottomIndex;
	int nCurrentKey;

	QPixmap pmap = m_pmapFrame;
	QPainter painter(&pmap);

_lStart:
	if (nPopupMenuTitle == -1)
	{
		MenuSettingStart(TRUE);
		nPopupMenuTitle = UISTR_MENU_MAINMENU;
		uiLogSlogAdd(g_uiProcStatus.nIDCurrentMgr, SLOG_ENTERMENU, 0, g_uiProcStatus.byMgr);
	}
	else if (nPopupMenuTitle == UISTR_MENU_DEVICEINFO)
		MenuSettingStart(TRUE);

	g_uiMenuItemTitle = nPopupMenuTitle;
	g_uiMenuItemIndex = uiProcMenuTitleIndex(nPopupMenuTitle) + 1;
	g_uiMenuTopIndex = g_uiMenuItemIndex;
	nCurrentKey = 1;   

	OnRedraw();

	if (nPopupMenuTitle == UISTR_MENU_MAINSETTING_TIME)
	{
		SETUP_TIMER(TIMER_DATETIME_SETUP, 1000, (DWORD)this, NULL);
	}

	while (!m_bTerminateFlag && uiTimeIsTimeout() == FALSE)  
	{
		POST_EVENTS();
		DM9000_Check();

		uiLockProc();
		if (uiPcCmdProc(FALSE))
		{
//			uiTimeSetLastActionTime();
			g_uiProcStatus.dwTimeDisableDevice = 0;
			MenuSettingStart(TRUE);
			OnRedraw();
		}

		if (g_uiProcStatus.bLcdSwitching || g_uiProcStatus.bSleeping)
			goto _lExitWithoutSave;

		if (g_uiMenuItems[g_uiMenuItemIndex].nType != UIMENU_TITLE && g_uiMenuItems[g_uiMenuItemIndex].nType != UIMENU_POPUP)
			g_uiHelpStr = g_uiMenuItems[g_uiMenuItemIndex].nHelpStr;
		else
			g_uiHelpStr = -1;

		if (g_uiBuildMenu && nPopupMenuTitle == UISTR_MENU_MAINMENU)
		{
			g_uiBuildMenu = FALSE;
			uiProcBuildMenu();
			goto _lStart;
		}

		nKey =  uiKeyGetKey();
		title = uiProcMenuTitleIndex(nPopupMenuTitle);      
		if (uiProcMenuGetCurrentRange(&from, &to))
		{
			switch ((int)(g_uiMenuItems[title].szIconFile))
			{
				case UIMENU_ICON:
					w = MENUITEM_ICONSTYLE_SIZE; h = MENUITEM_ICONSTYLE_SIZE;   
					w_spacer = (painter.window().width() - w * MENUITEM_COLS) / (MENUITEM_COLS + 1); 
					h_spacer = 15;  
					x = m_nFrameX + w_spacer; y = MENU_ICON_TOPMARGIN + m_nFrameY - h - h_spacer;

					for (i=from; i<=to; i++)
					{
						if ((i - from) % MENUITEM_COLS == 0)
						{
							x = m_nFrameX + w_spacer;
							y += h + h_spacer;
						}

						if ((nTouchX >= x) && (nTouchX <= (x+w)) && (nTouchY >= y) && (nTouchY <= (y+h)))  
						{
							nKey = ((i - from) + 1 ) + UIKEY_0;
							break;
						}

						x = x + w + w_spacer;
					}   
					break;
				case UIMENU_REPORT:
				case UIMENU_REPORT_NOICON:
					w = MENUITEM_REPORT_SIZE_X; h = MENUITEM_REPORT_SIZE_Y;   
					y = m_nFrameY + 20;
					w_spacer = (painter.window().width() - w * REPORTITEM_COLS) / (REPORTITEM_COLS + 1); 
					h_spacer = (painter.window().height() - h * REPORTITEM_ROWS - y) / (REPORTITEM_ROWS + 1);
					x = m_nFrameX - w - w_spacer;

					for (i=from; i<=to; i++)
					{
						if ((i - from) % REPORTITEM_ROWS == 0)
						{
							x += w + w_spacer;
							y = m_nFrameY + 20;
						}

                        if ((nTouchX >= x) && (nTouchX <= (x+w)) && (nTouchY >= y) && (nTouchY <= (y+h)))  
						{
							nKey = ((i - from) + 1 ) + UIKEY_0;
							break;
						}

                        y = y + h + h_spacer;  
					}
					break;
			}
		}   
	    
        if (uiKeyIsDigit((T_UI_KEY)nKey))
		{
			title = uiProcMenuTitleIndex(nPopupMenuTitle);      

			nKey -= UIKEY_0;
			if (nKey == 0)
				nKey = 17;
			if (uiProcMenuGetItemCount(nPopupMenuTitle) >= nKey)
			{
				g_uiMenuItemIndex = uiProcMenuTitleIndex(nPopupMenuTitle) + nKey;
				OnKeyPressArrow(UIKEY_NONE, nPopupMenuTitle);
				uiTimeDelay(1);
				nKey = UIKEY_OK;
			}   
		} 
        
        if ((nTouchX >= Ts_MainFrameNum_Min_X) && (nTouchX <= Ts_MainFrameNum_Max_X) && (nTouchY >= Ts_MainFrameNum_Min_Y) && (nTouchY <= Ts_MainFrameNum_Max_Y))  
		     nKey = UIKEY_ESC;


		switch (nKey)
		{
		case UIKEY_OK:
			OnKeyPressOk(nPopupMenuTitle);
			break;
	/*	case UIKEY_MENU:
//			uiTimeSetLastActionTime(uiTimeGetTickCount() - UITIME_OUT);
			m_bTerminateFlag = TRUE;
			break;   *////xf 091106
		case UIKEY_UP:
		case UIKEY_DOWN:
	/*	case UIKEY_LEFT:
		case UIKEY_RIGHT:*/
			OnKeyPressArrow(nKey, nPopupMenuTitle);
			break;
		case UIKEY_ESC:
			goto _lExit;
		}
	}

	if (uiTimeIsTimeout())
		goto _lExitWithoutSave;

_lExit:
	MenuSettingEnd(nPopupMenuTitle);
	SET_GUITHEME(dbSetupTotal.setSystem.byTheme);
	GUI_DLG_SET_THEME();

_lExitWithoutSave:
	if (nPopupMenuTitle == UISTR_MENU_MAINSETTING_TIME)
	{
		STOP_TIMER(TIMER_DATETIME_SETUP);
	}

	return;
}

void CMenu::OnKeyPressOk(int /*nTitle*/)
{
	int nID;  
	int nCurrentTitle, nCurrentIndex, nTopIndex;
	int __prev_col_cnt, __prev_item_size;

	nCurrentTitle = g_uiMenuItemTitle;
	nCurrentIndex = g_uiMenuItemIndex;
	nTopIndex = g_uiMenuTopIndex;

/*	if ((g_uiMenuItems[nCurrentIndex].nMenuStr == UISTR_MENU_ADVANCEDSETTING) ||
		(g_uiMenuItems[nCurrentIndex].nMenuStr == UISTR_MENU_COMMSETTING_COMMPWD) ||
		(g_uiMenuItems[nCurrentIndex].nMenuStr == UISTR_MENU_USERINFODOWNLOAD) ||
		(g_uiMenuItems[nCurrentIndex].nMenuStr == UISTR_MENU_USERINFOUPLOAD))  */
	if ((g_uiMenuItems[nCurrentIndex].nMenuStr == UISTR_MENU_USBMANAGE) ||
		(g_uiMenuItems[nCurrentIndex].nMenuStr == UISTR_MENU_SYSTEMSETTING))	

	{
		if (g_uiProcStatus.byMgr != PRIV_SMGR && Db_GetManagerCount(PRIV_SMGR))
		{
			uiLcdMessageBox(UI_MSG_ERROR, UISTR_VERIFY_ILLEGAL, UI_MSGTIMEOUT);
			return;
		}
	}

	if ((g_uiMenuItems[nCurrentIndex].nMenuStr == UISTR_MENU_COMMSETTING_BAUDRATE))
	{
		if (!dbSetupSystemNew.bRS232Use && !dbSetupSystemNew.bRS485Use)
			return;
	}

	if ((g_uiMenuItems[nCurrentIndex].nMenuStr == UISTR_MENU_COMMSETTING_IPADDRESS) ||
		(g_uiMenuItems[nCurrentIndex].nMenuStr == UISTR_MENU_COMMSETTING_MASKADDRESS) ||
		(g_uiMenuItems[nCurrentIndex].nMenuStr == UISTR_MENU_COMMSETTING_GWADDRESS) ||
		(g_uiMenuItems[nCurrentIndex].nMenuStr == UISTR_MENU_COMMSETTING_COMMPWD) ||
		(g_uiMenuItems[nCurrentIndex].nMenuStr == UISTR_MENU_COMMSETTING_DHCPUSE) ||
		(g_uiMenuItems[nCurrentIndex].nMenuStr == UISTR_MENU_COMMSETTING_PCBACKGROUND) ||
		(g_uiMenuItems[nCurrentIndex].nMenuStr == UISTR_MENU_COMMSETTING_PCBACKPORT) )
	{
		if (!dbSetupSystemNew.bEthernetUse)
			return;
	}

	if ((dbSetupSystemNew.nLockGroupMain) &&
		(g_uiMenuItems[nCurrentIndex].nMenuStr == UISTR_MENU_ACSETTING_LOCKGROUP_SET))
		return;

	switch (g_uiMenuItems[nCurrentIndex].nType)
	{
	case UIMENU_POPUP:
		__prev_col_cnt = __MENU_ICON_COL_CNT;
		__prev_item_size = __MENU_ICON_ITEM_SIZE;

		if (g_uiMenuItems[nCurrentIndex].nMenuStr == UISTR_MENU_SYSTEMSETTING)
		{
			__MENU_ICON_COL_CNT = 3;        
			__MENU_ICON_ITEM_SIZE = 105;     
		}
		if (g_uiMenuItems[nCurrentIndex].nMenuStr == UISTR_MENU_ENROLLNEW)
		{
			BOOL bResult;
			g_uiPopupTitle = g_uiMenuItems[nCurrentIndex].nMenuStr;
			bzero(&gUserInfoTemp, sizeof(USER_INFO));
			DbUserInfoFlagManagerSet(&gUserInfoTemp, PRIV_USER);
			bResult = (BOOL)DIALOGBOXEX(CInputUserIDName, CInputUserIDName::ID_ALL);
// 			if (!bResult || !gUserInfoTemp.ID)
// 				break;
// 			USER_INFO *pUI = (USER_INFO*)DbUserInfoGetPointer(gUserInfoTemp.ID);
// 			if (pUI && memcmp(pUI, &gUserInfoTemp, sizeof(USER_INFO)))
// 				uiEnrollUserInfo(&gUserInfoTemp);
			goto _lPopupExit;
		}
		if (g_uiMenuItems[nCurrentIndex].nMenuStr == UISTR_MENU_ENROLLDELETE)
		{
			if (!Db_GetUserCount())
			{
				uiLcdMessageBox(UI_MSG_ERROR, UISTR_ENROLLDELETE_NODATA, UI_MSGTIMEOUT);
				break;
			}
			g_uiPopupTitle = g_uiMenuItems[nCurrentIndex].nMenuStr;
			bzero(&gUserInfoTemp, sizeof(USER_INFO));
			nID = DIALOGBOX_RET(CInputUserID);    
			if (((int)nID != -1))
			{
				gUserInfoTemp.ID = nID;
			}
			goto _lPopupExit;
		}
		if ((g_uiMenuItems[nCurrentIndex].nMenuStr == UISTR_MENU_ACSETTING_USERTIMEZONE) ||
			(g_uiMenuItems[nCurrentIndex].nMenuStr == UISTR_MENU_ACSETTING_DURESS_MANAGE))
		{
			if (!Db_GetUserCount())
			{
				uiLcdMessageBox(UI_MSG_ERROR, UISTR_ENROLLDELETE_NODATA, UI_MSGTIMEOUT);
				break;
			}
			g_uiPopupTitle = g_uiMenuItems[nCurrentIndex].nMenuStr;
			g_uiMenuIDForUerTZ = (UINT64)DIALOGBOX_RET(CInputUserID);
			goto _lPopupExit;
		}
		uiSoundOut(SOUND_MENUSELECT, UI_BUZZER_NONE);
		MenuProc(g_uiMenuItems[nCurrentIndex].nMenuStr);

_lPopupExit:
		g_uiMenuItemTitle = nCurrentTitle;
		g_uiMenuItemIndex = nCurrentIndex;
		g_uiMenuTopIndex = nTopIndex;
		__MENU_ICON_COL_CNT = __prev_col_cnt;
		__MENU_ICON_ITEM_SIZE = __prev_item_size;
		g_uiPopupTitle = -1;
		OnRedraw();
		break;
	case UIMENU_HASVALUE:
		uiProcMenuHasValue(ui.lblBackgroundFrame, g_uiMenuItems[nCurrentIndex].nMenuStr);
		GUI_DLG_SET_THEME();
		OnRedraw();
		break;
	case UIMENU_CUSTOM:
	case UIMENU_CUSTOM_HASCHILD:
		uiProcMenuCustom(this, g_uiMenuItems[nCurrentIndex].nMenuStr);
		if (g_uiMenuItems[nCurrentIndex].nMenuStr == UISTR_MENU_ADVANCEDSETTING_DEFAULT)
		{
			GUI_DLG_SET_THEME();
		}
		OnRedraw();
		break;
	}
}

void CMenu::OnKeyPressArrow(int nKey, int nTitle)
{
	int nItemCnt, nItemCnt1;
	int nFirstIndex;
	BOOL bReport;

	nItemCnt = uiProcMenuGetItemCount(nTitle);
	nFirstIndex = uiProcMenuTitleIndex(nTitle) + 1;

	bReport = ((int)g_uiMenuItems[nFirstIndex-1].szIconFile == UIMENU_REPORT) ||
		((int)g_uiMenuItems[nFirstIndex-1].szIconFile == UIMENU_REPORT_NOICON);

	//if (bReport)
	//{
	//	if (nKey == UIKEY_UP)
	//		nKey = UIKEY_LEFT;
	//	else if (nKey == UIKEY_DOWN)
	//		nKey = UIKEY_RIGHT;
	//	else
	//		nKey = UIKEY_NONE;
	//}

	switch (nKey)
	{
	/*case UIKEY_UP:
		if ((g_uiMenuItems[nFirstIndex-1].nMenuStr == UISTR_MENU_ENROLLNEW) ||
			(g_uiMenuItems[nFirstIndex-1].nMenuStr == UISTR_MENU_ENROLLDELETE))
			g_uiMenuItemIndex = nFirstIndex + (g_uiMenuItemIndex - nFirstIndex + nItemCnt - 1) % nItemCnt;
		else
		{
			nItemCnt1 = (nItemCnt + MENUITEM_COLS - 1) / MENUITEM_COLS * MENUITEM_COLS;
			if ((nItemCnt1 > MENUITEM_COLS) && ((g_uiMenuItemIndex - nFirstIndex) % MENUITEM_COLS > (nItemCnt - 1) % MENUITEM_COLS))
				nItemCnt1 -= MENUITEM_COLS;
			g_uiMenuItemIndex = nFirstIndex + (g_uiMenuItemIndex - nFirstIndex + nItemCnt1 - MENUITEM_COLS) % nItemCnt1;
		}
		break;
	case UIKEY_DOWN:
		if ((g_uiMenuItems[nFirstIndex-1].nMenuStr == UISTR_MENU_ENROLLNEW) ||
			(g_uiMenuItems[nFirstIndex-1].nMenuStr == UISTR_MENU_ENROLLDELETE))
			g_uiMenuItemIndex = nFirstIndex + (g_uiMenuItemIndex - nFirstIndex + nItemCnt + 1) % nItemCnt;
		else
		{
			nItemCnt1 = (nItemCnt + MENUITEM_COLS - 1) / MENUITEM_COLS * MENUITEM_COLS;
			if ((nItemCnt1 > MENUITEM_COLS) && ((g_uiMenuItemIndex - nFirstIndex) % MENUITEM_COLS > (nItemCnt - 1) % MENUITEM_COLS))
				nItemCnt1 -= MENUITEM_COLS;
			g_uiMenuItemIndex = nFirstIndex + (g_uiMenuItemIndex - nFirstIndex + nItemCnt1 + MENUITEM_COLS) % nItemCnt1;
		}
		break;*/
	case UIKEY_UP:
		if ((g_uiMenuItems[nFirstIndex-1].nMenuStr == UISTR_MENU_ENROLLNEW) ||
			(g_uiMenuItems[nFirstIndex-1].nMenuStr == UISTR_MENU_ENROLLDELETE))
		{
			nItemCnt1 = (nItemCnt + ENROLLMENU_ROWCOUNT - 1) / ENROLLMENU_ROWCOUNT * ENROLLMENU_ROWCOUNT;
			if ((nItemCnt1 > ENROLLMENU_ROWCOUNT) && ((g_uiMenuItemIndex - nFirstIndex) % ENROLLMENU_ROWCOUNT > (nItemCnt - 1) % ENROLLMENU_ROWCOUNT))
				nItemCnt1 -= ENROLLMENU_ROWCOUNT;
			g_uiMenuItemIndex = nFirstIndex + (g_uiMenuItemIndex - nFirstIndex + nItemCnt1 - ENROLLMENU_ROWCOUNT) % nItemCnt1;
		}
		else
			g_uiMenuItemIndex = nFirstIndex + (g_uiMenuItemIndex - nFirstIndex + nItemCnt - 1) % nItemCnt;
		break;
	case UIKEY_DOWN:
		if ((g_uiMenuItems[nFirstIndex-1].nMenuStr == UISTR_MENU_ENROLLNEW) ||
			(g_uiMenuItems[nFirstIndex-1].nMenuStr == UISTR_MENU_ENROLLDELETE))
		{
			nItemCnt1 = (nItemCnt + ENROLLMENU_ROWCOUNT - 1) / ENROLLMENU_ROWCOUNT * ENROLLMENU_ROWCOUNT;
			if ((nItemCnt1 > ENROLLMENU_ROWCOUNT) && ((g_uiMenuItemIndex - nFirstIndex) % ENROLLMENU_ROWCOUNT > (nItemCnt - 1) % ENROLLMENU_ROWCOUNT))
				nItemCnt1 -= ENROLLMENU_ROWCOUNT;
			g_uiMenuItemIndex = nFirstIndex + (g_uiMenuItemIndex - nFirstIndex + nItemCnt1 + ENROLLMENU_ROWCOUNT) % nItemCnt1;
		}
		else
			g_uiMenuItemIndex = nFirstIndex + (g_uiMenuItemIndex - nFirstIndex + nItemCnt + 1) % nItemCnt;
		break;
	}

	if (bReport)
	{
		if (g_uiMenuItemIndex < g_uiMenuTopIndex)
			g_uiMenuTopIndex = g_uiMenuItemIndex;
		if (g_uiMenuItemIndex + 1 > g_uiMenuTopIndex + MENUITEM_ROWS)
			g_uiMenuTopIndex = g_uiMenuItemIndex - MENUITEM_ROWS + 1;
	}

	OnRedraw();
}

void CMenu::OnRedraw()
{
	int nTitleIndex = uiProcMenuTitleIndex(g_uiMenuItemTitle);

	
	if(g_uiMenuItemTitle == UISTR_MENU_SYSINFOVIEW)
	{
		setTitle(QString(RESOURCE_PATH) + QString(g_uiMenuItems[g_uiMenuItemIndex].szIconFile),
			UISTR(UISTR_SYMBOL_BRACKET_ON) +
			UISTR(g_uiMenuItemTitle) +
			UISTR(UISTR_SYMBOL_BRACKET_OFF));

		uiLcdSetLabelText(ui.lblTitleText1, UISTR(UISTR_UNIT_TOTAL), TITLECOLOR);
		ui.lblTitleText1->show();
	}
	else
		
	{
		ui.lblTitleText1->hide();
		setTitle(QString(RESOURCE_PATH) + QString(g_uiMenuItems[g_uiMenuItemIndex].szIconFile),
			UISTR(UISTR_SYMBOL_BRACKET_ON) +
			UISTR(g_uiMenuItemTitle) +
			UISTR(UISTR_SYMBOL_BRACKET_OFF) + QString("-") +
			UISTR(g_uiMenuItems[g_uiMenuItemIndex].nMenuStr));

	}
	if ((int)(g_uiMenuItems[nTitleIndex].szIconFile) == UIMENU_ICON)
		uiLcdSetLabelText(ui.lblStatusText, UISTR(UISTR_STATUS_MENU), FOREGROUND_COLOR);
	else
		uiLcdSetLabelText(ui.lblStatusText, UISTR(UISTR_STATUS_MENU1), FOREGROUND_COLOR);
	update();
}

//////////////////////////////////////////////////////////////////////////
void CMenu::paintEvent(QPaintEvent *e)
{	
	CMainFrame::paintEvent(e);  

	if (!g_uiMenuRedrawFlag)
		return;

	QPixmap pmap = m_pmapFrame;  
	QPainter painter(&pmap);
	int title, from, to;
  

// 	painter.save();
// 	painter.setPen(MENU_PEN_COLOR);
	title = uiProcMenuTitleIndex(g_uiMenuItemTitle);
	if (uiProcMenuGetCurrentRange(&from, &to))
	{
		switch ((int)(g_uiMenuItems[title].szIconFile))
		{
		case UIMENU_ICON:
			drawIconStyle(&painter, g_uiMenuItemIndex, from, to);  
			break;
		case UIMENU_REPORT:
			drawReportStyle(&painter, g_uiMenuItemIndex, from, to, TRUE);  
			break;
		case UIMENU_REPORT_NOICON: 
			drawReportStyle(&painter, g_uiMenuItemIndex, from, to, FALSE);  
			break;
		case UIMENU_CUSTOMDRAW:
			{
				funcMenuCustomDraw fp = (funcMenuCustomDraw)g_uiMenuItems[title].nHelpStr;
				if ((int)fp == -1)
					break;
				fp(this, &painter, g_uiMenuItems, from, to);
			}
			break;
		}
	}
// 	painter.restore();  

	ui.lblBackgroundFrame->setPixmap(pmap);  
}

void CMenu::drawIconStyle(QPainter *painter, int nCurrentIndex, int from, int to)
{
	painter->save();
	painter->setRenderHint(QPainter::Antialiasing);  

	int i;
	int x, y, w, h, w_spacer, h_spacer;
	T_UI_MENUITEM *item;
	const char *szIconFile = NULL;   

	w = MENUITEM_ICONSTYLE_SIZE; h = MENUITEM_ICONSTYLE_SIZE;   
	w_spacer = (painter->window().width() - w * MENUITEM_COLS) / (MENUITEM_COLS + 1);  
	h_spacer = 5;   
    x = m_nFrameX;   
	y = MENU_ICON_TOPMARGIN + m_nFrameY - h - h_spacer;

	for (i=from; i<=to; i++)
	{
		if ((i - from) % MENUITEM_COLS == 0)
		{
			x = m_nFrameX + w_spacer;  
			y += h + h_spacer;
		}

		item = &g_uiMenuItems[i];
		if( nCurrentIndex == i )
		{
            szIconFile = "mainmenu-image2.png";
			QIcon ico1(QString(GUI_RESOURCE_PATH) + QString(szIconFile));
			ico1.paint(painter, x, y, MENUITEM_ICONSTYLE_SIZE, MENUITEM_ICONSTYLE_SIZE, Qt::AlignCenter, QIcon::Normal);  
		}

		QIcon ico(QString(RESOURCE_PATH) + QString(item->szIconFile));
		ico.paint(painter, x, y, MENUITEM_ICONSTYLE_SIZE, MENUITEM_ICONSTYLE_SIZE - 10, Qt::AlignCenter, QIcon::Normal);  

		QString str = UISTR(item->nMenuStr);
		if (painter->fontMetrics().width(str) >= w)
		{
			while (str.length() > 1 && painter->fontMetrics().width(str) >= w - painter->fontMetrics().width("..."))
				str.resize(str.length() - 1);
			str.append("...");
		}

        if(nCurrentIndex == i)
		{	painter->setFont(SB_FONT_2());
			uiLcdDrawText(painter, x, y, w, h, Qt::AlignBottom | Qt::AlignHCenter, str, MENU_ITEM_SELET_COLOR);
			painter->setFont(SB_FONT_3());   
		}
		else
		{
			uiLcdDrawText(painter, x, y, w, h, Qt::AlignBottom | Qt::AlignHCenter, str, MENU_PEN_COLOR);  
		}	

		x = x + w + w_spacer;
	}

	painter->restore();
}

void CMenu::drawReportStyle(QPainter *painter, int nCurrentIndex, int from, int to, bool bDrawIcon)
{
	painter->save();
	
	int i;
	int nBottomIndex;
	int x, y, w, h, w_spacer, h_spacer;
	T_UI_MENUITEM *item;
	const char *szIconFile = NULL;

	w = MENUITEM_REPORT_SIZE_X; h = MENUITEM_REPORT_SIZE_Y;   
    y = m_nFrameY + 20;
	w_spacer = (painter->window().width() - w * REPORTITEM_COLS) / (REPORTITEM_COLS + 1); 
    h_spacer = (painter->window().height() - h * REPORTITEM_ROWS - y) / (REPORTITEM_ROWS + 1);
    x = m_nFrameX - w;
	
	for (i=from; i<=to; i++)
	{
		if ((i - from) % REPORTITEM_ROWS == 0)
		{
			x += w + w_spacer + m_nFrameX;
			y = m_nFrameY + 20;
		}
		
		item = &g_uiMenuItems[i];

		if (nCurrentIndex == i)
		{
			QPixmap pmap_sel(QString(RESOURCE_PATH) + QString(SELECTED_ITEM_FILENAME));
			QPainterPath roundPath = CustomStyle::roundRectPath(QRect(x, y, w, h));
			painter->setClipPath(roundPath);
			painter->setClipPath(roundPath, Qt::NoClip);
			g_uiMenuCurrentArea = QRect(x, y, w, h);
		}   
	
			if (nCurrentIndex == i)
                 szIconFile = "menu-image4.png";
			else szIconFile = "menu-image3.png";

        QIcon ico(QString(GUI_RESOURCE_PATH) + QString(szIconFile));
        ico.paint(painter, x, y, MENUITEM_REPORT_SIZE_X, MENUITEM_REPORT_SIZE_Y, Qt::AlignCenter, QIcon::Normal);  //xf 091106
     	
		if(nCurrentIndex == i)
		{
			painter->setFont(SB_FONT_2());
			uiLcdDrawText(painter, x + MENU_REPORT_LEFTMARGIN, y + MENU_REPORT_UPMARGIN, w, h, Qt::AlignLeft, UISTR(item->nMenuStr), MENU_ITEM_SELET_COLOR);
			if (item->nType == UIMENU_HASVALUE)
				uiLcdDrawText(painter, x, y + MENU_REPORT_UPMARGIN, w - MENU_REPORT_RIGHTMARGIN, h, Qt::AlignRight, uiProcMenuGetItemValue(item->nMenuStr), MENU_ITEM_SELET_COLOR);
			painter->setFont(SB_FONT_3());
		}
		else
		{
			uiLcdDrawText(painter, x + MENU_REPORT_LEFTMARGIN, y + MENU_REPORT_UPMARGIN, w, h, Qt::AlignLeft, UISTR(item->nMenuStr), MENU_PEN_COLOR);
			if (item->nType == UIMENU_HASVALUE)
				uiLcdDrawText(painter, x, y + MENU_REPORT_UPMARGIN, w - MENU_REPORT_RIGHTMARGIN, h, Qt::AlignRight, uiProcMenuGetItemValue(item->nMenuStr), MENU_PEN_COLOR);
		}
		
        y = y + h + h_spacer;
	}

	painter->restore();   
}  

/************************************************************************/
/*                                                                      */
/************************************************************************/
int uiProcCustomDrawEnroll(CMenu *pWnd, QPainter *painter, T_UI_MENUITEM */*pItems*/, int from, int to)
{
	painter->save();

	int i;
	int cnt = to - from + 1;
	int x, y, w, h;
	T_UI_MENUITEM *item;
	WORD wEnrollStatus = Db_GetEnrolledIDMask(gUserInfoTemp.ID);

	uiEnrollSetTitle(pWnd->ui.lblTitleText);

	x = pWnd->getFrameX() + MENU_REPORT_LEFTMARGIN;
	y = pWnd->getFrameY() + MENU_ICON_TOPMARGIN;
	w = pWnd->getFrameWidth();
	h = pWnd->getFrameHeight();

	for (i=0; i<cnt; i++)
	{
		if (i == ENROLLMENU_ROWCOUNT)
		{
			x += ENROLLMENU_COLWIDTH;
			y = pWnd->getFrameY() + MENU_ICON_TOPMARGIN;
		}

		item = &g_uiMenuItems[from + i];

		if (g_uiMenuItemIndex == i + from)
		{
			QPixmap pmap_sel(QString(RESOURCE_PATH) + QString(SELECTED_ITEM_FILENAME));
			QPainterPath roundPath = CustomStyle::roundRectPath(QRect(x, y, ENROLLMENU_COLWIDTH, ENROLLMENU_ROWHEIGHT));
			painter->setClipPath(roundPath);
			painter->drawPixmap(x, y, ENROLLMENU_COLWIDTH, ENROLLMENU_ROWHEIGHT, pmap_sel, 0, 0, pmap_sel.width(), pmap_sel.height());
			painter->setClipPath(roundPath, Qt::NoClip);
//			g_uiMenuCurrentArea = QRect(x, y, w, h);
		}

		QIcon ico(QString(RESOURCE_PATH) + QString(item->szIconFile));
		ico.paint(painter, x, y, ENROLLMENU_ICONSIZE, ENROLLMENU_ICONSIZE, Qt::AlignCenter, QIcon::Normal);

		uiLcdDrawText(
			painter, x + ENROLLMENU_ICONSIZE, y,
			ENROLLMENU_COLWIDTH - ENROLLMENU_ICONSIZE, ENROLLMENU_ROWHEIGHT,
			Qt::AlignTop | Qt::AlignLeft, UISTR(item->nMenuStr),
			MENU_PEN_COLOR);

		BOOL bDisabled = TRUE;
		const char *szIconFile = NULL;

		switch (item->nMenuStr)
		{
		case UISTR_MENU_ENROLL_FP:
		case UISTR_MENU_DELETE_FP:
			break;
		case UISTR_MENU_ENROLL_RFCARD:
		case UISTR_MENU_DELETE_RFCARD:
			bDisabled = ((wEnrollStatus & (1 << BACKUP_CARD)) == 0);
			szIconFile = "icon-card.png";
			break;
		case UISTR_MENU_ENROLL_PWD:
		case UISTR_MENU_REMOVE_PWD:
			bDisabled = ((wEnrollStatus & (1 << BACKUP_PASSWORD)) == 0);
			szIconFile = "icon-pwd.png";
			break;
		case UISTR_MENU_ENROLL_VOICE:
		case UISTR_MENU_DELETE_VOICE:
			bDisabled = !DbUserInfoHasVoice(gUserInfoTemp.ID);
			szIconFile = "icon-voice.png";
			break;
		case UISTR_MENU_ENROLL_PHOTO:
		case UISTR_MENU_DELETE_PHOTO:
			bDisabled = !DbUserInfoHasPhoto(gUserInfoTemp.ID);
			szIconFile = "icon-camera.png";
			break;
		}

		if ((item->nMenuStr == UISTR_MENU_ENROLL_FP) ||
			(item->nMenuStr == UISTR_MENU_DELETE_FP))
		{
			ico = QIcon(QString(RESOURCE_PATH) + "icon-fingerenrolled.png");
			for (int k=BACKUP_FINGER0; k<=BACKUP_FINGER9; k++)
			{
				bDisabled = ((wEnrollStatus & (1 << k)) == 0);
				ico.paint(painter, x + ENROLLMENU_ICONSIZE + 5 + (k%5)*16, y + 20 + (k<5?0:14), 12, 12, Qt::AlignCenter, bDisabled ? QIcon::Disabled : QIcon::Normal);
			}
		}
		else
		if ((item->nMenuStr != UISTR_MENU_ENROLL_FP) &&
			(item->nMenuStr != UISTR_MENU_DELETE_FP) &&
			(item->nMenuStr != UISTR_MENU_DELETE_ALL))
		{
			if (szIconFile)
				ico = QIcon(QString(RESOURCE_PATH) + QString(szIconFile));
			ico.paint(painter, x + ENROLLMENU_ICONSIZE + 5, y + 20, 14, 14, Qt::AlignCenter, bDisabled ? QIcon::Disabled : QIcon::Normal);
		}

		y += ENROLLMENU_ROWHEIGHT;
	}

	painter->restore();
	return 0;
}
