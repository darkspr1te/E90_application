#include "../precomp.h"
#include "MainWindow.h"
#include "Menu.h"
#include "Mainframe.h"
#include "UserManage.h"
#include "SystemManage.h"
#include <QtGui/QPainter>
#include <QtCore/QTime>
#include <QtCore/QTimer>
#include <QtGui/QKeyEvent>
#include <QtGui/QBitmap>
#include <QtCore/QMap>
#include <QtCore/QSet>
#include <QtCore/QDir>

extern BOOL   LINK_LOST;
/************************************************************************/
/*                                                                      */
/************************************************************************/
T_UI_PROCSTATUS g_uiProcStatus =
{
	FALSE, // bReqManager;
	FALSE, // bMenuRequested;
	FALSE, // bMenuProcessing;
	FALSE, // bVerifying;
	0,     // dwReqManagerTime;
	FALSE, // bManagerVerifyOK;
	0,     // nIDCurrentMgr;
	0,     // byMgr;
	0,     // nTrType;
	0,     // nVerifyFail;
	0,     // dwLastVerifyFailTime;
	FALSE, // bAlarming;
	FALSE, // bAlarmPrevStatus;
	FALSE, // bControllerCommError;
	FALSE, // bControllerCommError1;
	-1,    // nAlarmStatusFromController;
	0,     // dwMsgStartTime;
	FALSE, // bLcdSwitching;
	FALSE, // bSleeping;
	0,     // dwRtcSyncTime;
	FALSE, // bDisableDevice;
	FALSE, // bCameraStatus;
	FALSE, // bSDCardStatus;
	FALSE, // bNetworkStatus;
	FALSE, // bUSBStatus;
	FALSE, // bSOSKeyPressed;
	0,     // dwTimeDisableDevice;
	0,     // dwCurrentSecond;
	UILANG_SC,//nPrevLanguage;
	UI_LED_NORMAL, // nLedCurrStatus;
	0,     // dwTimeLedStart;
	FALSE, // bPrevDhcpConfigStatus;
	FALSE, // bDuressFlag;
	FALSE, // bDrawClock, not used
	FALSE, // bDrawClockPrevStatus, not used
	0,     // nLastVerifiedUser;
	FALSE, // bExistRFMod;
	0,		//preTheme
	FALSE,	//AlarmStatus,
	0,           //LcdBack
};

extern speed_t __UART_BAUDRATE_MAP[];      
extern unsigned int nTouchX, nTouchY, nTouchPress;      

#define MESSGAEBOX_BACK_X   (480 - 270) / 2   //105
#define MESSGAEBOX_BACK_Y   (272 - 120) / 2   //76

#define MESSAGEBOX_STOP_X 	MESSGAEBOX_BACK_X + 180
#define MESSAGEBOX_STOP_Y 	MESSGAEBOX_BACK_Y + 70
#define MESSAGEBOX_STOP_W 	80
#define MESSAGEBOX_STOP_H 	40

T_TIMER_DATA *g_TimerList = NULL;

int nBackgroupIconFile;        
int nTrType;                   

CMainWindow *g_MainWindow = NULL;
QLabel *g_StatusWindow = NULL;
QLabel *g_StatusIcon = NULL;
CVerify *g_VerifyWindow = NULL;
static DWORD g_dwStatusTime;
void uiProcBuildMenu();

void uiProcOnTimer(QWidget *pWidget, DWORD dwTimerID, DWORD dwParam);
int uiProcDrawStatus();
void uiProcDrawLicenseStatus();
void uiProcDeviceStatusNotify(BOOL bStatus, int nSuccessSound, int nFailSound);
void uiProcMenu();
void uiProcTimerManage();
void uiProcHostCommandMonitor();
void uiProcVerify(int nFirstDigit = 0);
void uiProcKeyboardManager(int nKey = UIKEY_NONE);
void uiProcLockManager();
void uiProcScreensaver();
void uiProcMain(BOOL bFirst);

/************************************************************************/
/*                                                                      */
/************************************************************************/
static BOOL __LED_ONOFF = FALSE;

void __timerLedControl()
{
	if (g_uiProcStatus.bAlarming || g_uiProcStatus.bControllerCommError1)
		uiLedAbnormal();
	else if (g_bDeviceBusy)
		uiLedBusy();

	switch (g_uiProcStatus.nLedCurrStatus)
	{
	case UI_LED_NORMAL:
		if (uiTimeGetTickCount() - g_uiProcStatus.dwTimeLedStart >= 500)
		{
			if (__LED_ONOFF)
			{
			//	LED_G_ON(); LED_R_OFF();
				__LED_ONOFF = FALSE;
			}
			else
			{
				LED_G_OFF(); LED_R_OFF();
				__LED_ONOFF = TRUE;
			}

			g_uiProcStatus.dwTimeLedStart = uiTimeGetTickCount();
		}
		break;
	case UI_LED_ABNORMAL:
		if (!g_uiProcStatus.bAlarming && !g_uiProcStatus.bControllerCommError1)
		{
			uiLedNormal();
			break;
		}

		if (uiTimeGetTickCount() - g_uiProcStatus.dwTimeLedStart >= 500)
		{
			if (__LED_ONOFF)
			{
				LED_G_OFF(); LED_R_ON();
				__LED_ONOFF = FALSE;
			}
			else
			{
				LED_G_OFF(); LED_R_OFF();
				__LED_ONOFF = TRUE;
			}

			g_uiProcStatus.dwTimeLedStart = uiTimeGetTickCount();
		}
		break;
	case UI_LED_SUCCESS:
		if (uiTimeGetTickCount() - g_uiProcStatus.dwTimeLedStart >= 1000)
		{
			uiLedNormal();
			LED_G_OFF();
			//g_uiProcStatus.dwTimeLedStart = uiTimeGetTickCount();
		}	
		else
		{
			//g_uiProcStatus.dwTimeLedStart = uiTimeGetTickCount();
			LED_G_ON();
		}	
		break;
	case UI_LED_FAIL:
		if (uiTimeGetTickCount() - g_uiProcStatus.dwTimeLedStart >= 3000)
			uiLedNormal();
		break;
	case UI_LED_BUSY:
		if (!g_bDeviceBusy)
		{
			uiLedNormal();
			break;
		}

		if (uiTimeGetTickCount() - g_uiProcStatus.dwTimeLedStart >= 100)
		{
			if (__LED_ONOFF)
			{
			//	LED_G_ON(); LED_R_OFF();
				__LED_ONOFF = FALSE;
			}
			else
			{
				LED_G_OFF(); LED_R_OFF();
				__LED_ONOFF = TRUE;
			}

			g_uiProcStatus.dwTimeLedStart = uiTimeGetTickCount();
		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
void uiProcOnTimer(QWidget */*pWidget*/, DWORD dwTimerID, DWORD dwParam)
{
	static int __status_checked_time = 0;
	int nRet;
	BOOL bRedrawStatusbar = FALSE;

	if (uiTimeGetTickCount() - __status_checked_time > 2000)
	{
		__status_checked_time = uiTimeGetTickCount();

		//RTC Synchronize; Do synchronize RTC per 5 minutes
		if (uiTimeGetTickCount() - g_uiProcStatus.dwRtcSyncTime >= 300 * 1000)
		{
			uiRtcSynchronize();
			g_uiProcStatus.dwRtcSyncTime = uiTimeGetTickCount();
		}

		//Camera status check
		//if (TRUE)
		//{
		//	if (g_uiProcStatus.bCameraStatus != CAMERA_ON() && !g_uiProcStatus.bMenuProcessing)
		//	{
		//		g_uiProcStatus.bCameraStatus = CAMERA_ON();
		//		g_MainWindow->ui.lblstatCamera->setEnabled(g_uiProcStatus.bCameraStatus);
		//	}
		//}

		//SD Card status check
		if (!g_uiProcStatus.bMenuProcessing && !g_uiProcStatus.bVerifying && g_uiProcStatus.bSDCardStatus != SDCARD_DETECT())
		{
			g_uiProcStatus.bSDCardStatus = SDCARD_DETECT();
			
		}

		//Webserver status check
		if (dbLicense.bUseWebServer && !WEBSERVER_ISALIVE())
		{
			WEBSERVER_START();
			g_MainWindow->ui.lblstatWebserver->setEnabled(TRUE);
		}
		else if(!dbLicense.bUseWebServer)
		{
			g_MainWindow->ui.lblstatWebserver->setEnabled(FALSE);
		}

		//Network status check
		if (!g_uiProcStatus.bMenuProcessing && dbLicense.bUseEthernet && g_uiProcStatus.bNetworkStatus != TCPIP_ON())
		{
			g_uiProcStatus.bNetworkStatus = TCPIP_ON();
			//g_MainWindow->ui.lblStatNetwork->setEnabled(g_uiProcStatus.bNetworkStatus);
		}

		//USB status check  (UDISK) //////////////////////////////////////////////////////////////////////////
		if (!g_uiProcStatus.bMenuProcessing && dbLicense.bUseUSB && g_uiProcStatus.bUSBStatus != UDISK_ON())
		{
			g_uiProcStatus.bUSBStatus = UDISK_ON();
		}

		//TR transition check
		if ((g_uiProcStatus.nTrType != TR_DUTYNO) && (uiTimeGetIdleTime() >= 8000))  
		{
			g_StatusWindow ->clear();
         	g_uiProcStatus.nTrType = TR_DUTYNO;   
			uiProcDrawStatus();   
		}

		//Bell time check
		if ((nRet = uiBellGetStatus()) >= 0)
		{
			uiTimeSetLastActionTime();
			uiProcScreensaver();
			DIALOGBOXEX(CBellDlg, nRet);
		}

		//Message Check
		if (!g_uiProcStatus.bMenuProcessing && !g_uiProcStatus.bVerifying)
		{
			QString szMessage = uiMsgGetCurrentString(0, 0);
			if (szMessage.length())
				uiMsgStart(szMessage, FALSE);
			else
				uiMsgStop();
		}
/*
		//DHCP Check
		if (dbComm_ipIsDHCP && !dbComm_dhcpSuccess)
		{
			xdhcpconfigure(0, FALSE);
			g_uiProcStatus.bPrevDhcpConfigStatus = FALSE;
		}
		if (dbComm_ipIsDHCP && dbComm_dhcpSuccess && !g_uiProcStatus.bPrevDhcpConfigStatus)
		{
			xifconfig("eth0", dbComm_macAddress, &dbComm_ipAddress, &dbComm_ipSubnetMask, &dbComm_ipDefaultGateway, FALSE);
			g_uiProcStatus.bPrevDhcpConfigStatus = TRUE;
			uiLcdMessageBox(UI_MSG_OK, UISTR_STATUS_DHCP_CONFIGURE_SUCCESS, UI_MSGTIMEOUT);
			if (dbLicense.byTcpipMode == TCPIP_CLIENT)
			{
				tcpclient_connect_start();
			}
		}
		*/
	}

	//AC Controller's Alarm Check
	if (dbSetupTotal.setSystem.dwBindingID)
	{
		if (g_uiProcStatus.bControllerCommError)
		{
			uiLcdMessageBox(UI_MSG_ERROR, UISTR_STATUS_CONTROLLER_CONNECT_ERROR, UI_MSGTIMEOUT);
			g_uiProcStatus.bControllerCommError = FALSE;
		}
		if (g_uiProcStatus.nAlarmStatusFromController >= UI_ALARM_START &&
			g_uiProcStatus.nAlarmStatusFromController <= UI_ALARM_END)
		{
			UINT64 ID = 0;
			switch (g_uiProcStatus.nAlarmStatusFromController)
			{
			case UI_ALARM_NOCLOSE:
				ID = g_uiProcStatus.nLastVerifiedUser;
				g_uiProcStatus.nLastVerifiedUser = 0;
			case UI_ALARM_ILGOPEN:
				if (uiAlarmStart(g_uiProcStatus.nAlarmStatusFromController, TRUE))
					uiEventSend_ALARM_ON(g_uiProcStatus.nAlarmStatusFromController, ID);
				break;
			}
			g_uiProcStatus.nAlarmStatusFromController = -1;
		}
		//Auto stopped alarm
		if (g_uiProcStatus.nAlarmStatusFromController >= UI_ALARM_START + 128 &&
			g_uiProcStatus.nAlarmStatusFromController <= UI_ALARM_END + 128)
		{
			if (uiAlarmStop(g_uiProcStatus.nAlarmStatusFromController - 128))
				uiEventSend_ALARM_OFF(g_uiProcStatus.nAlarmStatusFromController - 128, ALARMRELEASE_AUTO, 0);
			g_uiProcStatus.nAlarmStatusFromController = -1;
		}
	}

	//RF Card exist check
 	if (g_uiProcStatus.bExistRFMod)
		RFMOD_READ(FALSE);

	switch (dwTimerID)
	{
	case TIMER_RTCCLOCK:
		g_MainWindow->DrawClock();
		break;
	case TIMER_LED_ON:
		uiLedOff(); STOP_TIMER(dwTimerID);
		break;
	case TIMER_MANAGERREQUEST:
		g_uiProcStatus.bReqManager = FALSE;
		g_uiProcStatus.bMenuRequested = FALSE;
		bRedrawStatusbar = TRUE;
		STOP_TIMER(dwTimerID);
		break;
	case TIMER_DATETIME_SETUP:
		((QWidget*)dwParam)->update();
		break;
	case TIMER_ALARM:
		if (g_uiProcStatus.bAlarmPrevStatus)
		{
			if (dwParam)
				uiBuzzerOff();
			if (!dbSetupTotal.setSystem.dwBindingID)
				ALARM_OFF();
		}
		else
		{
			if (dwParam)
				uiBuzzerOn(UI_BUZZER_ON);
			if (!dbSetupTotal.setSystem.dwBindingID)
				ALARM_ON();
		}
		g_uiProcStatus.bAlarmPrevStatus = !g_uiProcStatus.bAlarmPrevStatus;
		break;
	case TIMER_SYSMONITOR:
		break;
	case TIMER_SMSG:
// 		g_StatusWindow->setText(dbSetupTotal.setTimezone.tzMsg[dwParam].Contents);
// 		if (uiTimeGetTickCount() - g_uiProcStatus.dwMsgStartTime > 10000)
// 		{
// 			STOP_TIMER(TIMER_SMSG);
// 			uiProcDrawStatus();
// 		}
		if (!g_uiProcStatus.bMenuProcessing)
			uiMsgDrawCurrentStatus();
		break;
	case TIMER_ACCACHE_FLUSH:
		g_VerifyWindow->ACCacheFlush();
		STOP_TIMER(TIMER_ACCACHE_FLUSH);
		break;
	case TIMER_DURESS_ALARM:
		STOP_TIMER(TIMER_DURESS_ALARM);
		uiAlarmStart(UI_ALARM_DURESS);
		break;
	case TIMER_SOSKEY_RELEASE:
		STOP_TIMER(TIMER_SOSKEY_RELEASE);
		g_uiProcStatus.bSOSKeyPressed = FALSE;
	case TIMER_KEYPAD_BACKGROUND:
		STOP_TIMER(TIMER_KEYPAD_BACKGROUND);
		uiLedKeyBackground(FALSE);
		break;
	case TIMER_LOCK_RESTORE:
		STOP_TIMER(TIMER_LOCK_RESTORE);
		uiDoorClose();
		break;
	case TIMER_LOGOUT_ALARM:
		// dwParam == 0 ? glog : slog
		STOP_TIMER(TIMER_LOGOUT_ALARM);
		uiAlarmStop(UI_ALARM_LOGOVERFLOW);
		uiEventSend_ALARM_OFF(UI_ALARM_LOGOVERFLOW, ALARMRELEASE_AUTO, 0);
		break;
	}
	
	/*if (bRedrawStatusbar)*/
	//	uiProcDrawStatus();
	if(g_bDisableDevice||g_uiWorkingDisplay||g_uiProcStatus.bReqManager)
	{
		g_StatusWindow->show();
	}
	else if(g_dwStatusTime < uiTimeGetTickCount()-5000)
	{
		g_StatusWindow ->clear();
		g_StatusWindow->hide();
		if (g_uiProcStatus.nTrType != TR_DUTYNO)
		{
         	g_uiProcStatus.nTrType = TR_DUTYNO;   
			uiProcDrawStatus();   
			g_StatusWindow->show();
		}   
	}

}

/************************************************************************/
/*                                                                      */
/************************************************************************/
int uiProcDrawStatus()
{
	if (/*dbSetupTotal.setNoMenu.*/g_bDisableDevice||g_uiWorkingDisplay)
	{
		g_StatusWindow->setFont(SB_FONT_4());
		uiLcdSetLabelText(g_StatusWindow,UISTR(UISTR_WORKING),QColor(255,255,214), QColor(255, 255, 255));
	}
	else
	{
		if (g_uiProcStatus.bReqManager)
		{
			g_StatusWindow->setFont(SB_FONT_4());
			uiLcdSetLabelText(g_StatusWindow,UISTR(UISTR_MANAGER_CONFIRM),QColor(255,255,214), QColor(255, 255, 255));
		}
		else
		{
            if (g_uiProcStatus.nTrType >= TR_START && g_uiProcStatus.nTrType <= TR_END )  
			{
			    if((g_uiProcStatus.nTrType == TR_DUTYON) || (g_uiProcStatus.nTrType == TR_DUTYOFF) 
					|| (g_uiProcStatus.nTrType == TR_OVERTIMEON) || (g_uiProcStatus.nTrType == TR_OVERTIMEOFF) 
					|| (g_uiProcStatus.nTrType == TR_GOOUTON) || (g_uiProcStatus.nTrType == TR_GOOUTOFF)
					|| (g_uiProcStatus.nTrType == TR_IN) || (g_uiProcStatus.nTrType == TR_OUT))   
				{
					g_StatusWindow->setFont(SB_FONT_1());  
					uiLcdSetLabelText(g_StatusWindow,UISTR(UISTR_FUNC_START + g_uiProcStatus.nTrType),QColor(255,255,214), QColor(255, 255, 255));  
				
					if(g_uiProcStatus.nTrType == TR_DUTYON)  
						 g_StatusIcon->setPixmap(QPixmap(GUI_RESOURCE_PATH"check-in.png"));
					if(g_uiProcStatus.nTrType == TR_DUTYOFF)  
						 g_StatusIcon->setPixmap (QPixmap(GUI_RESOURCE_PATH"check-out.png"));
					if(g_uiProcStatus.nTrType == TR_OVERTIMEON)  
						 g_StatusIcon->setPixmap(QPixmap(GUI_RESOURCE_PATH"check1-in.png"));
					if(g_uiProcStatus.nTrType == TR_OVERTIMEOFF)  
						 g_StatusIcon->setPixmap (QPixmap(GUI_RESOURCE_PATH"check1-out.png"));
					if(g_uiProcStatus.nTrType == TR_GOOUTON)  
						 g_StatusIcon->setPixmap(QPixmap(GUI_RESOURCE_PATH"check2-in.png"));
					if(g_uiProcStatus.nTrType == TR_GOOUTOFF)  
						 g_StatusIcon->setPixmap (QPixmap(GUI_RESOURCE_PATH"check2-out.png"));
					if(g_uiProcStatus.nTrType == TR_IN)  
						 g_StatusIcon->setPixmap(QPixmap(GUI_RESOURCE_PATH"check3-in.png"));
					if(g_uiProcStatus.nTrType == TR_OUT)  
						 g_StatusIcon->setPixmap (QPixmap(GUI_RESOURCE_PATH"check3-out.png"));  
				}
                else g_StatusIcon->setPixmap(QPixmap(GUI_RESOURCE_PATH"check-no.png"));
				
			}	
				g_dwStatusTime = uiTimeGetTickCount();
		}
	
	}
	
	g_StatusWindow->show();
	POST_EVENTS();
	return 0;
}

void uiProcDrawLicenseStatus()
{
	if (dbLicense.bUseEthernet)
	{
		g_uiProcStatus.bNetworkStatus = FALSE;
		//g_MainWindow->ui.lblStatNetwork->setEnabled(FALSE);
		//g_MainWindow->ui.lblStatNetwork->show();
	}
	else
	{
		g_uiProcStatus.bNetworkStatus = FALSE;
		//g_MainWindow->ui.lblStatNetwork->hide();
	}

	if (dbLicense.bUseUSB)
	{
		g_uiProcStatus.bUSBStatus = FALSE;
		/*g_MainWindow->ui.lblstatUSB->setEnabled(TRUE);*/
		/*g_MainWindow->ui.lblstatUSB->hide();*/
	}
	else
	{
		g_uiProcStatus.bUSBStatus = FALSE;
		/*g_MainWindow->ui.lblstatUSB->hide();*/
	}

	g_MainWindow->ui.lblstatFingerprint->setEnabled(gbIsCMOS);
	g_MainWindow->ui.lblstatCard->setEnabled(dbLicense.bUseCard);
	g_MainWindow->ui.lblstatUSB->setEnabled(dbLicense.bUseUSB);
	g_MainWindow->ui.lblstatUDisk->setEnabled(dbLicense.bUseUSB);    
	g_MainWindow->ui.lblstatWebserver->setEnabled(dbLicense.bUseWebServer);
	//g_MainWindow->ui.lblstatRS232->setEnabled(dbLicense.bUseRS232);
}

//void uiProcDrawMsgArea(BOOL bStart)
//{
//	int i;
//	QLabel *lbls[] = 
//	{
//		g_MainWindow->ui.lblMenuUser,
//		g_MainWindow->ui.lblMenuSetting,
//		g_MainWindow->ui.lblMenuUSB,
//		g_MainWindow->ui.lblMenuData,
//		g_MainWindow->ui.lblMenuAlarm,
//	};
//
//	for (i=0; i<(int)ITEM_CNT(lbls); i++)
//	{
//		if (bStart)
//			lbls[i]->hide();
//		else
//			lbls[i]->show();
//	}
//	if (bStart)
//		g_MainWindow->ui.label->show();
//	else
//		g_MainWindow->ui.label->hide();
//}

void uiProcDrawStatusbar(QLabel *pLbl, int nOK, int nESC)
{
	QString str;
	int nCtrlType;
	QWidget *w = QApplication::focusWidget();

	if (!w)
		return;
	nCtrlType = DetermineControlType((QObject*)w);
	if(nCtrlType == CTRL_COMBOBOX)
	{
		str = UISTR(UISTR_MSG_TEXTMARK);
		goto _exit;
	}
	if (nOK >= 0)
		str = UISTR(nOK);
	if (nCtrlType == CTRL_TEXTBOX && w->objectName().contains("useT9") == TRUE)
		str = UISTR(UISTR_STATUS_OK_T9);
	if (nESC >= 0)
		str += QString(" ") + UISTR(nESC);
	if (nCtrlType == CTRL_TEXTBOX)
		str += QString(" ") + UISTR(UISTR_STATUS_MENU_CLEAR);
_exit:
	uiLcdSetLabelText(pLbl, str, FOREGROUND_COLOR);
}

void uiProcDeviceStatusNotify(BOOL bStatus, int nSuccessSound, int nFailSound)
{
	if (uiTimeGetTickCount() < 10000/*WAITINGSCREEN_TIMEOUT*/)
		return;
	if (bStatus)
		uiSoundOut(nSuccessSound, UI_BUZZER_ALARM, UITIME_VOICE);
	else
		uiSoundOut(nFailSound, UI_BUZZER_ERROR, UITIME_VOICE);
	uiTimeSetLastActionTime();
}

void uiProcPowerOff()
{
	QString szPoweroffString = UISTR(UISTR_STATUS_POWEROFF);
	int nStep = 0;
	DWORD dwTime = uiTimeGetTickCount();
	int POWERBELL[] = {1, 0, 1, 1, 1, 1};
	g_dwStatusTime =dwTime;
	uiBuzzerOn(UI_BUZZER_ON);
	g_StatusWindow ->clear();
	g_StatusWindow->show();
	////
	while (POWER_KEY()) 
	{
		POST_EVENTS();
		DM9000_Check();	
		
		if (nStep >= (int)ITEM_CNT(POWERBELL))
		{
			uiBuzzerOff();
			uiPowerSetStatus(UI_POWER_OFF, 1);
			break;   
		}

		if (POWERBELL[nStep])
			uiBuzzerOn(UI_BUZZER_ON);
		else
			uiBuzzerOff();

        if (uiTimeGetTickCount() - dwTime >= 50)   
		{
			nStep++;
			dwTime = uiTimeGetTickCount();
			szPoweroffString += ".";
			g_StatusWindow->setFont(SB_FONT_4());
			uiLcdSetLabelText(g_StatusWindow, szPoweroffString, QColor(255, 255, 214), QColor(255, 255, 255));
			
		}
	}  
	//////debug shengchengziku 
	//uiPowerSetStatus(UI_POWER_OFF, 1);  
	////debug
	uiBuzzerOff();
	g_dwStatusTime -=5000;
if(g_bDisableDevice)
	uiProcDrawStatus();
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
void uiProcTimerManage()
{
	int nRet;
	BOOL bRedrawStatusbar = FALSE;
	
	//Power status check
	nRet = uiPowerGetStatus();
	switch (nRet)
	{
		case UI_POWER_ON:
			break;
		case UI_POWER_OFF:
			uiPowerSetStatus(UI_POWER_OFF, 0);
			g_uiProcStatus.bSleeping = TRUE;
			break;
		case UI_POWER_SLEEP:
			uiPowerSetStatus(UI_POWER_SLEEP, 0);
			g_uiProcStatus.bSleeping = TRUE;
			break;
		case UI_POWER_LCDSWITCH:
			g_uiProcStatus.bLcdSwitching = TRUE;
			break;
	}

	//DisableDevice status check
	if (TRUE/*g_uiProcStatus.bDisableDevice != g_bDisableDevice*/)
	{
		if (g_uiProcStatus.bDisableDevice != g_bDisableDevice)
			bRedrawStatusbar = TRUE;

		if ((g_uiProcStatus.bDisableDevice = g_bDisableDevice))
		{
			if (g_uiProcStatus.dwTimeDisableDevice == 0)
				g_uiProcStatus.dwTimeDisableDevice = uiTimeGetTickCount();

			if (uiTimeGetTickCount() - g_uiProcStatus.dwTimeDisableDevice > 60000)
			{
				g_uiProcStatus.bDisableDevice = g_bDisableDevice = DISABLE_MODE_NONE;
				bRedrawStatusbar = TRUE;
			}
		}
		else
		{
			g_uiProcStatus.dwTimeDisableDevice = 0;
		}
	}

	if (!g_uiProcStatus.bVerifying && g_uiProcStatus.bReqManager)
	{
		if (uiTimeGetTickCount() - g_uiProcStatus.dwReqManagerTime >= 5000)
		{
			g_uiProcStatus.bReqManager = FALSE;
			g_uiProcStatus.bMenuRequested = FALSE;
		//	bRedrawStatusbar = TRUE;
		}
	}

	if (uiTimeGetTickCount() - g_uiProcStatus.dwLcdBackTime >= 30000)
	{
		LCD_CTL_OFF();
	}

// 	if (g_uiProcStatus.nPrevLanguage != dbSetupTotal.setSystem.nLanguage)
// 	{
// 		g_uiProcStatus.nPrevLanguage = dbSetupTotal.setSystem.nLanguage;
// 		bRedrawStatusbar = TRUE;
// 	}

	if (g_uiProcStatus.bManagerVerifyOK)
	{
		g_uiProcStatus.bManagerVerifyOK = FALSE;
		if (g_uiProcStatus.bMenuRequested)
		{
			g_uiProcStatus.bMenuRequested = FALSE;
			g_uiProcStatus.bMenuProcessing = TRUE;
			uiSoundOut(SOUND_ENTERMENU, UI_BUZZER_OK);  
			CMenu m(g_MainWindow);
			m.show();
			m.MenuProc();
// 			if (!g_uiProcStatus.bLcdSwitching && !g_uiProcStatus.bSleeping)
// 				uiTimeSetLastActionTime();
			g_uiProcStatus.bReqManager = FALSE;
			g_uiProcStatus.bMenuProcessing = FALSE;
				g_MainWindow->DrawClock(TRUE);
		}
		else
		{
			DIALOGBOX(CGLogList);
		}
		//bRedrawStatusbar = TRUE;
	}

	if (g_uiBuildMenu)
	{
		uiProcBuildMenu();
		g_uiBuildMenu = FALSE;
	}

	if (g_uiLicenseChanged)
	{
		uiProcDrawLicenseStatus();
		dbLicense.bUseWebServer ? WEBSERVER_START() : WEBSERVER_STOP();
		g_uiLicenseChanged = FALSE;
	}

	if (bRedrawStatusbar)
		uiProcDrawStatus();
}

void uiProcHostCommandMonitor()
{
	if (uiPcCmdProc(TRUE))
	{
		uiTimeSetLastActionTime();
		g_uiProcStatus.dwTimeDisableDevice = 0;
	}
}

void uiProcKeyboardManager(int nKey)
{
	if (nKey == UIKEY_NONE)
		nKey = uiKeyGetKey();  
   	if ((nKey == UIKEY_NONE) && (nTouchPress != PEN_DOWN))    
		return;  

	uiProcScreensaver();

	if ((nTouchX >= Ts_MainWindowNum_Min_X) && (nTouchX <= Ts_MainWindowNum_Max_X) && (nTouchY >= Ts_MainWindowNum_Min_Y) && (nTouchY <= Ts_MainWindowNum_Max_Y))  
	{
		uiTimeSetLastActionTime();  
        		nKey = UIKEY_0;             
		g_VerifyWindow->VerifyLoop(nKey);
		return;
	}
	
	if (!g_bDisableDevice && (nTouchX >= Ts_MainWindowMenu_Min_X) && (nTouchX <= Ts_MainWindowMenu_Max_X) && (nTouchY >= Ts_MainWindowMenu_Min_Y) && (nTouchY <= Ts_MainWindowMenu_Max_Y))  
	{
		uiTimeSetLastActionTime();  
		g_uiProcStatus.bReqManager = TRUE;
		g_uiProcStatus.bMenuRequested = TRUE;
		g_uiProcStatus.dwReqManagerTime = uiTimeGetTickCount();
		
		if ((g_uiProcStatus.bReqManager && !Db_GetManagerCountTotal())&&( dbSetupTotal.setSystem.dwSManagerPwd == STRING2PWD("0") ))
		{	
				g_uiProcStatus.bReqManager = FALSE;
				g_uiProcStatus.bManagerVerifyOK = TRUE;
				g_uiProcStatus.nIDCurrentMgr = 0;
				g_uiProcStatus.byMgr = PRIV_SMGR;		
		}
		else
		{
			uiProcDrawStatus();
		}
	
//		SETUP_TIMER(TIMER_MANAGERREQUEST, 8000, 0, NULL);
	}
	else if (!g_bDisableDevice && (nKey == UIKEY_OK))
	{
		DIALOGBOXEX(CSearchLog, CSearchLog::LOG_GLOG_BY_USER);
		uiProcKeyboardManager(UIKEY_ESC);
	}
	else if (!g_bDisableDevice && nKey == UIKEY_ESC && g_uiProcStatus.bReqManager)
	{
//		STOP_TIMER(TIMER_MANAGERREQUEST);
		g_uiProcStatus.bReqManager = FALSE;
		g_uiProcStatus.bMenuRequested = FALSE;
		g_StatusWindow ->clear();

	}
	else if(!g_bDisableDevice && nKey ==UIKEY_ESC)
	{
		g_StatusWindow ->clear();
        		g_uiProcStatus.nTrType = TR_DUTYNO;
		uiProcDrawStatus();    
	}
      else if (!g_bDisableDevice && nKey == UIKEY_F1)  
	{
		//g_uiProcStatus.nTrType--;
	//	if (g_uiProcStatus.nTrType < TR_START)
	//		g_uiProcStatus.nTrType = TR_END;
		g_uiProcStatus.nTrType = TR_DUTYON;
		uiProcDrawStatus();   
	}
    	else if (!g_bDisableDevice && nKey == UIKEY_F2)  
	{
		/*g_uiProcStatus.nTrType++;
		if (g_uiProcStatus.nTrType > TR_END)
			g_uiProcStatus.nTrType = TR_START;*/
		g_uiProcStatus.nTrType = TR_DUTYOFF;
		uiProcDrawStatus();
	}
	else if (!g_bDisableDevice && nKey == UIKEY_F3)  
	{
		g_uiProcStatus.nTrType = TR_OVERTIMEON;
		uiProcDrawStatus();   
	}
    else if (!g_bDisableDevice && nKey == UIKEY_F4)  
	{
		g_uiProcStatus.nTrType = TR_OVERTIMEOFF;
		uiProcDrawStatus();
	}
	else if (!g_bDisableDevice && nKey == UIKEY_F5)  
	{
		g_uiProcStatus.nTrType = TR_GOOUTON;
		uiProcDrawStatus();   
	}
    else if (!g_bDisableDevice && nKey == UIKEY_F6)  
	{
		g_uiProcStatus.nTrType = TR_GOOUTOFF;
		uiProcDrawStatus();
	}
	else if (!g_bDisableDevice && nKey == UIKEY_F7)  
	{
		g_uiProcStatus.nTrType = TR_IN;
		uiProcDrawStatus();   
	}
    else if (!g_bDisableDevice && nKey == UIKEY_F8)  
	{
		g_uiProcStatus.nTrType = TR_OUT;
		uiProcDrawStatus();
	}  
	else if (!g_bDisableDevice && nKey == UIKEY_1 && dbLicense.bUseACFunction && dbSetupTotal.setSystem.bSOSKeyUse)
	{
		if (uiKeyGetKeyLong(3000) == UIKEY_1)
		{
			uiAlarmDuress(0); //SOS key duress
			uiEventSend_ALARM_ON(UI_ALARM_DURESS, 0);
		}
		else
		{
			g_uiProcStatus.bSOSKeyPressed = TRUE;
			SETUP_TIMER(TIMER_SOSKEY_RELEASE, 3000, 0, NULL);
		}
	}
}

void uiProcLockManager()
{
	uiLockProc();
}

void uiProcScreensaver()
{
	static QLabel *lblImage = NULL;
	static DWORD __prev_time = 0;
	static int __image_index = 0;

	if (!g_uiProcStatus.bLcdSwitching)
	{
		if (lblImage)
		{
			MP3_PLAY(NULL);
			DELETE(lblImage);
		}
		return;
	}
	if (!lblImage)
	{
		lblImage = new QLabel;
		lblImage->setGeometry(0, 0, LCD_SIZE_X, LCD_SIZE_Y);
		lblImage->show();
		if (dbSetupTotal.setSystem.bVoiceOut)
			MP3_PLAY(MAKE_FULLPATH(FLASH_SCREENSAVER_CURRENT_DIRNAME, FLASH_SCREENSAVER_MP3_FILENAME, NULL), 0);
	}

	if (dbSetupTotal.setSystem.bVoiceOut && MP3_STATUS() == MAD_FLOW_STOP)
		MP3_PLAY(MAKE_FULLPATH(FLASH_SCREENSAVER_CURRENT_DIRNAME, FLASH_SCREENSAVER_MP3_FILENAME, NULL), 0);

	if (uiTimeGetTickCount() - __prev_time >= 2000)
	{
		QDir dir(FLASH_SCREENSAVER_CURRENT_DIRNAME, "*.jpg");
		QStringList files = dir.entryList();
		if (files.count())
		{
			__image_index = (__image_index + 1) % files.count();
			QPixmap pmap(QString(FLASH_SCREENSAVER_CURRENT_DIRNAME) + QString("/") + files[__image_index]);
			lblImage->setPixmap(pmap);
			lblImage->setScaledContents(TRUE);
		}
		else
		{
			int i;
			QPixmap pmap(LCD_SIZE_X, LCD_SIZE_Y);
			QPainter p(&pmap);
			Qt::GlobalColor __color_table[] = {Qt::red, Qt::green, Qt::blue};

			for (i=0; i<4; i++)
				p.fillRect(i*(LCD_SIZE_X / 4), 0, LCD_SIZE_X / 4, LCD_SIZE_Y, QBrush(__color_table[(__image_index + i) % 3]));
			lblImage->setPixmap(pmap);
			__image_index++;
		}
		__prev_time = uiTimeGetTickCount();
	}
}

BOOL http_WEB_CONNECT=FALSE;
void DispDeviceState(void)
{
	if(LINK_LOST==1)//连接失败,网线断开
	{
		g_MainWindow->ui.lblNet->setPixmap(QPixmap(GUI_RESOURCE_PATH"net-lost.png"));
		g_MainWindow->ui.lblNet->show();
	
	}
	else if(tcpclient_connect_isok()==0 &&(dbLicense.byTcpipMode == TCPIP_CLIENT))
	{
		g_MainWindow->ui.lblNet->setPixmap(QPixmap(GUI_RESOURCE_PATH"net-err.png"));
		g_MainWindow->ui.lblNet->show();
	}		
	else if(LINK_LOST==0 && http_WEB_CONNECT==TRUE)
	{
		g_MainWindow->ui.lblNet->setPixmap(QPixmap(GUI_RESOURCE_PATH"net-ok.png"));
		g_MainWindow->ui.lblNet->show();
	}
	else
	{
		g_MainWindow->ui.lblNet->setPixmap(QPixmap(GUI_RESOURCE_PATH"net-err.png"));
		g_MainWindow->ui.lblNet->show();
	}
}

/*                                                                      */
/************************************************************************/
#define UIPROC_WRAPPER(_f_)	{POST_EVENTS(); (_f_);} 
//////////////////////////////////////////////////////////////////////////
void uiProcMain(BOOL bFirst)
{
	nBackgroupIconFile = -1;   

	uiRtcSynchronize();

	if (!g_MainWindow)
		return;

	g_MainWindow->DrawClock(TRUE);
	uiProcDrawStatus();
	g_MainWindow->show();

	POST_EVENTS();

	SETUP_TIMER(TIMER_RTCCLOCK, 100, 0, NULL);

	if (bFirst)
	{
		g_VerifyWindow = new CVerify;
		if (!g_VerifyWindow)
		{
			printf("Verify window creating error, %s !\n", strerror(errno));
			while (!g_VerifyWindow)
				g_VerifyWindow = new CVerify;
		}

		uiLogSlogAdd(0, SLOG_TURNON, 0, 0);
//		uiSoundOut(SOUND_TURNON, UI_BUZZER_OK);
	}
	else
	{
		//g_MainWindow->ui.lblstatCamera->setEnabled(g_uiProcStatus.bCameraStatus);
		/*g_MainWindow->ui.lblstatCard->setEnabled(g_uiProcStatus.bSDCardStatus);*/
		//g_MainWindow->ui.lblStatNetwork->setEnabled(g_uiProcStatus.bNetworkStatus);
	/*	g_MainWindow->ui.lblstatUSB->setEnabled(g_uiProcStatus.bUSBStatus);*/
	/*	if (g_uiProcStatus.bUSBStatus)
			g_MainWindow->ui.lblstatUSB->show();
		else
			g_MainWindow->ui.lblstatUSB->hide();*/
	}

	uiProcDrawLicenseStatus();
	uiProcBuildMenu();

	g_uiProcStatus.nPrevLanguage = dbSetupTotal.setSystem.nLanguage;
	g_uiProcStatus.byPrevTheme = dbSetupTotal.setSystem.byTheme;
	g_uiProcStatus.bExistRFMod = RFMOD_EXIST();


	if (LCD_BLANK_STATUS() == FBINFO_BLANK_PAUSE)
		LCD_BLANK(FBINFO_BLANK_RESUME);
	
	//nfs调试暂时删除
        //StartDhchclient();
        //if (dbLicense.byTcpipMode == TCPIP_CLIENT)
            //tcpclient_connect_Creatthread();

	while (1)
	{
        #if 1
		 //OtherDev_Test();
		 DM9000_Check();
		 DispDeviceState();
        #endif	 
		DbUserTimeOut(dbSetupTotal.setSystem.dwDataSaveTime*86400);  

		UIPROC_WRAPPER(uiProcTimerManage());          
		//UIPROC_WRAPPER(uiProcHostCommandMonitor());
		UIPROC_WRAPPER(uiProcKeyboardManager());      
		//UIPROC_WRAPPER(g_VerifyWindow->VerifyLoop());
		UIPROC_WRAPPER(uiProcLockManager());          
		UIPROC_WRAPPER(uiProcScreensaver());          

		if (g_uiProcStatus.nPrevLanguage != dbSetupTotal.setSystem.nLanguage ||
			g_uiProcStatus.byPrevTheme != dbSetupTotal.setSystem.byTheme)
		{
			g_uiProcStatus.nPrevLanguage = dbSetupTotal.setSystem.nLanguage;
			g_uiProcStatus.byPrevTheme = dbSetupTotal.setSystem.byTheme;
			uiMsgStop();
			LCD_BLANK(FBINFO_BLANK_PAUSE);
			break;
		}   
	}

	g_MainWindow = NULL;
	g_StatusWindow = NULL;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
CMainWindow::CMainWindow(QWidget *parent)
	: QWidget(parent)
{
	GUI_DLG_IMPL(TRUE);
	//ui.lblBackground->setPixmap(QPixmap(BACKGROUND_IMAGE));
	//ui.label->setPixmap(QPixmap(BOTTOM_IMAGE));
	
	QPalette pal1 = ui.lblTime->palette();
	QPalette pal = ui.lblMonth->palette();

	pal.setColor(QPalette::All, QPalette::WindowText, QColor(255, 255, 214));
	pal1.setColor(QPalette::All, QPalette::WindowText, QColor(0, 255, 255));
	ui.lblMonth->setPalette(pal);
//	ui.lblDay->setPalette(pal);
	ui.lblTime->setPalette(pal1);
	ui.lblAMPM->setPalette(pal);
	ui.lblWeekday->setPalette(pal);
	ui.lblStatusbarText->setPalette(pal);
//	ui.lblStatusbarText->setAlignment(Qt::AlignVCenter);
	ui.lblMonth->setAlignment(Qt::AlignCenter);

	ui.lblTime->setFont(SB_FONT_0());
	ui.lblMonth->setFont(SB_FONT_3());
	ui.lblWeekday->setFont(SB_FONT_3());
	ui.lblStatusbarText->setFont(SB_FONT_1());
	ui.lblMessageArea->setFont(SB_FONT_4());

//	ui.lblAMPM->hide();           //xf 090818  sec
//	ui.lblstatUSB->hide();
	m_ClockPixmap = QPixmap(CLOCK_IMAGE);
	m_ClockW = ui.lblClock->width();;
	m_ClockH = ui.lblClock->height();;

    ui.lblstatUSB->hide();
	ui.lblstatCard->hide();
	ui.lblstatFingerprint->hide();
	ui.lblstatUDisk->hide();
	ui.lblstatWebserver->hide();
	ui.lblClock->hide();
	ui.lblAMPM->hide();
	ui.lblNet->hide();

// 	DrawClock(TRUE);

	g_MainWindow = this;
	g_StatusWindow = ui.lblStatusbarText;
	g_StatusIcon = ui.lblStatbarFingerprint;
	g_rgbForeColor = qRgb(255, 255, 214);    
	//g_rgbForeColor1 = qRgb(255, 255, 255);
	if (!g_TimerList)
	{
		g_TimerList = new T_TIMER_DATA[MAX_TIMER_COUNT];
		bzero(g_TimerList, sizeof(T_TIMER_DATA) * MAX_TIMER_COUNT);
	}

	QTimer::singleShot(50, this, SLOT(OnTimer()));   
}

//////////////////////////////////////////////////////////////////////////
// static const QPoint hourHand[] = {
// 	QPoint(2, 4),
// 	QPoint(2, -40),
// 	QPoint(6, -45),
// 	QPoint(0, -60),
// 	QPoint(-6, -45),
// 	QPoint(-2, -40),
// 	QPoint(-2, 4),
// };
// static const QPoint minuteHand[] = {
// 	QPoint(2, 6),
// 	QPoint(2, -45),
// 	QPoint(6, -60),
// 	QPoint(0, -80),
// 	QPoint(-6, -60),
// 	QPoint(-2, -45),
// 	QPoint(-2, 6),
// };
// 
// static const QPoint secondHand[2] = {
// 	QPoint(0, 15),
// 	QPoint(0, -70)
// };
static const QPointF hourHand[] = {
	QPointF(3, 12),
	QPointF(1, -50),
	QPointF(-1,-50),
	QPointF(-3, 12),
};
static const QPointF minuteHand[] = {
	QPointF(3, 15),
	QPointF(1, -65),
	QPointF(-1,-65),
	QPointF(-3, 15),
};
static const QPointF secondHand[] = {
	QPointF(1, 15),
	QPointF(0, -70),
	QPointF(-1,15),
};

void CMainWindow::DrawClock(BOOL bForce  /*= FALSE*/)
{
	QPixmap pmap = m_ClockPixmap;
	QPainter painter(&pmap);
	int nYear, nMonth, nDay, nWeekday, nHour, nMinute, nSecond;
// 	QDate date = QDate::currentDate();
// 	QTime time = QTime::currentTime();
	char szBuffer[12]; 

	uiRtcGet(&nYear, &nMonth, &nDay, &nWeekday, &nHour, &nMinute, &nSecond);
	g_uiProcStatus.dwCurrentSecond = uiRtcGetSeconds(nYear, nMonth, nDay, nHour, nMinute, nSecond);

// 	if (g_uiProcStatus.bMenuProcessing)
// 		return;

	if( nBackgroupIconFile != dbSetupTotal.setSystem.nBackgroupIconFile )
	{
		switch(dbSetupTotal.setSystem.nBackgroupIconFile + UISTR_BK_START)
		{
			case UISTR_BK_1: 
					ui.lblBackground->setPixmap(QPixmap(GUI_RESOURCE_PATH"backgroup1.png"));
					break;
			case UISTR_BK_2: 
					ui.lblBackground->setPixmap(QPixmap(GUI_RESOURCE_PATH"backgroup2.png"));
					break;
			case UISTR_BK_3: 
					ui.lblBackground->setPixmap(QPixmap(GUI_RESOURCE_PATH"backgroup3.png"));
					break;
			case UISTR_BK_4: 
					ui.lblBackground->setPixmap(QPixmap(GUI_RESOURCE_PATH"backgroup4.png"));
					break;
			case UISTR_BK_5: 
					ui.lblBackground->setPixmap(QPixmap(GUI_RESOURCE_PATH"backgroup5.png"));
					break;
			case UISTR_BK_6: 
					ui.lblBackground->setPixmap(QPixmap(GUI_RESOURCE_PATH"backgroup6.png"));
					break;
			default:
				    ui.lblBackground->setPixmap(QPixmap(GUI_RESOURCE_PATH"backgroup1.png"));
				    break;
		}
		nBackgroupIconFile = dbSetupTotal.setSystem.nBackgroupIconFile;
	}

	//sprintf(szBuffer, ":%02d", nSecond);
	//uiLcdSetLabelText(ui.lblAMPM, szBuffer, QColor(255, 255, 200), QColor(255, 255, 255));

	if (bForce || !nSecond)
	{
		char szBuf[12];
		int __weekday_list[] = {UISTR_WEEKDAY_SUN, UISTR_WEEKDAY_MON, UISTR_WEEKDAY_TUE, UISTR_WEEKDAY_WED, UISTR_WEEKDAY_THU, UISTR_WEEKDAY_FRI, UISTR_WEEKDAY_SAT};

		DWORD dwSeconds;
		dwSeconds = uiRtcGetSeconds();
	//	uiRtcGetDate(dwSeconds);
		uiLcdSetLabelText(ui.lblMonth, uiRtcGetDate(dwSeconds), QColor(255, 255, 200), QColor(255, 255, 255));


		sprintf(szBuf, "%02d:%02d", nHour, nMinute);
		uiLcdSetLabelText(ui.lblTime, szBuf, QColor(255, 255, 0), QColor(255, 255, 255));
		uiLcdSetLabelText(ui.lblWeekday, UISTR(__weekday_list[nWeekday - 1]), QColor(255, 255, 214), QColor(255, 255, 255));
	}
}

int CMainWindow::SetTimer(DWORD dwTimerID, int nElapse, DWORD dwParam, TIMERPROC/* lpTimerFunc*/)
{
	StopTimer(dwTimerID);

	for (int i = 0; i < MAX_TIMER_COUNT; i++)
	{
		if (!g_TimerList[i].dwTimerID)
		{
			g_TimerList[i].dwTimerID = dwTimerID;
			g_TimerList[i].nElapse = nElapse;
			g_TimerList[i].dwParam = dwParam;
			g_TimerList[i].dwProcessedTime = uiTimeGetTickCount();
			break;
		}
	}
	return 0;
}

void CMainWindow::StopTimer(DWORD dwTimerID)
{
	for (int i = 0; i < MAX_TIMER_COUNT; i++)
	{
		if (g_TimerList[i].dwTimerID == dwTimerID)
		{
			bzero(&g_TimerList[i], sizeof(T_TIMER_DATA));
			break;
		}
	}
}

void CMainWindow::OnTimer()
{
	static DWORD __wdog_prev_time = 0;
	int i;
	DWORD dwCurrentTime = uiTimeGetTickCount();

	if (dwCurrentTime - __wdog_prev_time > 1000)
	{
		wdog_app_alive();
		__wdog_prev_time = dwCurrentTime;
		if (g_bDeviceBusy)
			DrawClock();
	}

	__timerLedControl();

	if (!g_bDeviceBusy)
	{
		for (i = 0; i < MAX_TIMER_COUNT; i++)
		{
			if (!g_TimerList[i].dwTimerID)
				continue;
			if (dwCurrentTime - g_TimerList[i].dwProcessedTime >= (DWORD)g_TimerList[i].nElapse)
			{
				g_TimerList[i].dwProcessedTime = dwCurrentTime;
				uiProcOnTimer(this, g_TimerList[i].dwTimerID, g_TimerList[i].dwParam);
			}
		}
	}
	QTimer::singleShot(50, this, SLOT(OnTimer()));
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
// typedef enum
// {
// 	UI_VERIFYSTATUS_SUCCESS,
// 	UI_VERIFYSTATUS_FAIL,
// 	UI_VERIFYSTATUS_GETID,
// 	UI_VERIFYSTATUS_INVALID_VM,
// 	UI_VERIFYSTATUS_INVALID_TZ,
// 	UI_VERIFYSTATUS_INVALID_LG,
// 	UI_VERIFYSTATUS_DOOROPEN
// }T_UI_VERIFY_STATUS;

CVerify::CVerify(QWidget *parent /* = NULL */)
	: QDialog(parent)
{
	GUI_DLG_IMPL(TRUE);
	GUI_DLG_SET_THEME();
	//m_pmapPhoto = *ui.lblPhotoArea->pixmap();
	//m_pmapCamera = *ui.lblCameraArea->pixmap();
//	m_pmapFinger = *ui.lblFpArea->pixmap();
	m_pmapFinger = QPixmap(GUI_RESOURCE_PATH "area-fingerprint.png");
	m_pmapCard = QPixmap(GUI_RESOURCE_PATH "area-card.png");
	m_pmapPassword = QPixmap(GUI_RESOURCE_PATH "area-password.png");

// 	sb_ResumeVideo(&g_VideoIn);
// 	sb_grab(&g_VideoIn);
// 	sb_PauseVideo(&g_VideoIn);
// 	sb_save_jpg("/tmp/photo.jpg", &g_VideoIn);
// 	QPixmap pmap("/tmp/photo.jpg");
// 	ui.lblCameraArea->setPixmap(pmap);
	ui.lblDate->setFont(SB_FONT_2());
	ui.lblTrStatus->setFont(SB_FONT_2());

	QPalette pal = palette();
	GUI_DLG_SET_FORE_COLOR(&pal, TITLECOLOR);

	ui.lblDate->setPalette(pal);
	ui.lblTrStatus->setPalette(pal);

	ui.lblID->setFont(SB_FONT_4());
	ui.lblName->setFont(SB_FONT_4());
	ui.lblPriv->setFont(SB_FONT_4());
	ui.lblPart->setFont(SB_FONT_4());
	ui.lblStatusText->setFont(SB_FONT_4());

	ui.lblPart->hide();

// 	ui.lblDate->setText(QString("%1 : %2").arg(UISTR(UISTR_VERIFY_DATE)).arg(uiRtcGetDate()));
// 	ui.lblTime->setText(QString("%1 : %2").arg(UISTR(UISTR_VERIFY_TIME)).arg(uiRtcGetTime()));
	InitResults();
	ACCacheFlush();
	g_uiProcStatus.bVerifying = FALSE;
}

void CVerify::InitResults(int nVerifyMode /* = 0 */)
{
	g_uiProcStatus.bVerifying = TRUE;
	ui.lblDate->setText(QString("%1 %2").arg(uiRtcGetDate()).arg(uiRtcGetTime()));
	ui.lblTrStatus->setText(UISTR(UISTR_FUNC_START + nTrType));                
	ui.lblID->setText(UISTR(UISTR_VERIFY_ID));
	ui.lblName->setText(UISTR(UISTR_VERIFY_NAME));
	ui.lblPriv->setText(UISTR(UISTR_VERIFY_PRIV));
	ui.lblPart->setText(UISTR(UISTR_VERIFY_PART));
	//ui.lblPhotoArea->setPixmap(m_pmapPhoto);
	//ui.lblCameraArea->setPixmap(m_pmapCamera);
	ui.lblStatusText->setText("");

	switch (nVerifyMode)
	{
	case UI_VERIFY_FP:
		break;
	case UI_VERIFY_RF:
		ui.lblFpArea->setPixmap(m_pmapCard);
		break;
	case UI_VERIFY_PW:
		ui.lblFpArea->setPixmap(m_pmapPassword);
		break;
	default:
		ui.lblFpArea->setPixmap(m_pmapFinger);
		break;
	}
}

#define EnterVerifyInterface() __asm("NOP")
#define LeaveVerifyInterface() __asm("NOP")
//////////////////////////////////////////////////////////////////////////
void CVerify::VerifyLoop(int nFirstDigit /* = -1 */)
{
	BOOL bResult;
	int nVerifyModeOld = UI_VERIFY_NONE, nVerifyMode = UI_VERIFY_NONE;
	int nVerifiedList = 0;
	int nUserVerifyMode = VM_NONE;
	UINT64 nID = 0;
	DWORD dwCardNumber = 0;
	DWORD dwPassword = 0;
	BOOL bAdapted = FALSE;
	BYTE byFingerNumber = 0;
	int nStep = 0;
	USER_INFO UserInfo;
	UINT64 nVerifiedID = 0, nVerifiedIDPrev = 0;
	BOOL bDisabled = FALSE;
	int nKey = UIKEY_NONE;
	BOOL bSuccess = FALSE;
	BOOL bSlaveVerified = FALSE;
	int USER_ID[IDNUMBER_LENGTH];
	int USER_ID_IDX = -1;
	QString szMessage;
	BOOL bUserVoiceOut = FALSE;
	DWORD dwTimeout = 5000;
//xprintf("loveywm1\r\n");
	BYTE pbuf[50];  
	char szUserName[10];  

	nTrType = g_uiProcStatus.nTrType;   

	if (g_bDisableDevice)
		return;

	if (nFirstDigit >= 0)
	{
		CInputUserID w(this); w.show();
		if ((nID = w.DoProcess(FALSE, nFirstDigit)))  
			nVerifyMode = UI_VERIFY_ID;
		w.close();
        if (((int)nID == 0))  
		{
			VerifySManager0();
			xprintf("loveywm2\r\n");
			return;
		}
        if (((int)nID == -1))
		{
			nVerifyMode = UI_VERIFY_NONE;
			xprintf("loveywm3\r\n");
			return;
		}
	}
	else if (uiCMOSCaptureFP())
	{
		nVerifyMode = UI_VERIFY_FP;
		xprintf("loveywm4\r\n");
		uiBuzzerAlarm();
	}
	else if ((dwCardNumber = uiCardCapture()))
	{
		nVerifyMode = UI_VERIFY_RF;
		uiBuzzerAlarm();
	}
	if (nVerifyMode == UI_VERIFY_NONE)
		return;

	InitResults();  

	//if (!g_uiProcStatus.bReqManager)
		/*show();*/
	xprintf("loveywm6\r\n");
	xprintf("nStep==%d\r\n",nStep);

	while (nStep < 4)
	{
		bSuccess = FALSE;
		bSlaveVerified = FALSE;
		USER_ID_IDX = -1;

		if (nStep == 0)
		{
			nVerifiedList = 0;
			nVerifiedIDPrev = nVerifiedID = 0;
			nUserVerifyMode = VM_NONE;
			VERIFY_DURESS_INIT();
			xprintf("nUserVerifyMode ==%d\r\n",nUserVerifyMode);
		}

		MP3_PLAY(NULL, 0);

		xprintf("loveywm7\r\n");
		xprintf("nVerifyMode ==%d\r\n",nVerifyMode);
		switch (nVerifyMode)
		{
		case UI_VERIFY_ID:
			bResult = uiIDVerify(nID, &UserInfo, &bDisabled);
		//	xfprintf("bResult=%d\n",bResult);
			if(!bResult && dbSetupTotalTemp.setSystem.bRemoteAttUse)
			{
				Com_VerifyLoop(nID);
				return ;
			}  
			if (nStep == 0)
				LeaveVerifyInterface();
			else
				EnterVerifyInterface();
			break;
		case UI_VERIFY_FP:
			EnterVerifyInterface();
			if (dbSetupTotal.setSystem.bFPShow)
			{
				DrawFingerprint(ui.lblFpArea, &m_pmapFinger);   
				POST_EVENTS();                                  
			}
			if (dbSetupTotal.setSystem.byAntipassStatus != ANTIPASS_SLAVE || g_uiProcStatus.bReqManager)
			{
				if (nStep == 0)
					bResult = uiFpVerifyO2N(NULL, &UserInfo, &bDisabled, &bAdapted, &byFingerNumber);
				else
					bResult = uiFpVerifyO2O(NULL, UserInfo.ID, &bAdapted, &byFingerNumber);
                
				if (bResult && dbLicense.bUseACFunction && DbUserInfoFlagDuressStatusGet(&UserInfo, byFingerNumber))
					VERIFY_DURESS_START(UserInfo.ID); //FP duress
			}
			else
			{
				bSlaveVerified = bResult =
					uiFpVerifyByMaster(NULL, &UserInfo, &bDisabled, &bAdapted, &byFingerNumber);
			}
			break;
		case UI_VERIFY_RF:
			EnterVerifyInterface();
			ui.lblFpArea->setPixmap(m_pmapCard);
			if (dbSetupTotal.setSystem.byAntipassStatus != ANTIPASS_SLAVE || g_uiProcStatus.bReqManager)
			{
				bResult = uiCardVerify(dwCardNumber, &UserInfo, &bDisabled);
			}
			else
			{
				bSlaveVerified = bResult = 
					uiCardVerifyByMaster(dwCardNumber, &UserInfo, &bDisabled);
			}
		//	uiTimeDelay(500);   //xf 091106
			break;
		case UI_VERIFY_PW:
			EnterVerifyInterface();
			ui.lblFpArea->setPixmap(m_pmapPassword);
			bResult = uiPwdVerify(nID, PWD2STRING(dwPassword), &UserInfo, &bDisabled);
			if (bResult && dbLicense.bUseACFunction && dbSetupTotal.setSystem.bPwdAlarmUse)
				VERIFY_DURESS_START(UserInfo.ID); //PWD duress
			break;
		default:
			LeaveVerifyInterface();
			bResult = FALSE;
			break;
		}

		if (!bResult || (bSlaveVerified && UserInfo.ID == 0))
		{
			uiProcTimerManage();
			uiMsgStop();
			InitResults(nVerifyMode);
			nStep = 0;
			uiLedFail();
			show();
			if (!bResult && dbSetupTotal.setSystem.byAntipassStatus == ANTIPASS_SLAVE)
				uiLcdMessageBox(UI_MSG_ERROR, USITR_VERIFY_MASTER_CONNECT_ERROR, UI_MSGTIMEOUT);
			else if (!bDisabled)
			{
				//Verfiy Failure !
				if (uiTimeGetTickCount() - g_uiProcStatus.dwLastVerifyFailTime > ILLEGAL_VERIFY_TIMEOUT)
					g_uiProcStatus.nVerifyFail = 0;

				g_uiProcStatus.nVerifyFail++;
				g_uiProcStatus.dwLastVerifyFailTime = uiTimeGetTickCount();

				if (dbSetupTotal.setSystem.nIllegalVerifyWarning &&
					g_uiProcStatus.nVerifyFail >= dbSetupTotal.setSystem.nIllegalVerifyWarning)
				{
					g_uiProcStatus.nVerifyFail = 0;
					uiAlarmStart(UI_ALARM_ILGVERIFY);
					uiEventSend_ALARM_ON(UI_ALARM_ILGVERIFY, 0);
				}

				uiLcdSetLabelText(ui.lblStatusText, UISTR(UISTR_VERIFY_FAIL), FOREGROUND_COLOR);
				if(nVerifyMode == UI_VERIFY_FP)
					uiSoundOut(SOUND_VERIFY_FAIL, UI_BUZZER_ERROR, UITIME_VOICE);
				else
					uiSoundOut(SOUND_ERROR,UI_BUZZER_ERROR,UITIME_VOICE);
				uiEventSend_VERIFY_FAIL(nVerifyMode);
			}
			else
			{
				uiLcdMessageBox(UI_MSG_ERROR, UISTR_VERIFY_DISABLED, UI_MSGTIMEOUT);
			}

			nVerifyMode = UI_VERIFY_NONE;
			goto _lCapture;
		}

		nVerifiedIDPrev = nVerifiedID;
		nID = nVerifiedID = UserInfo.ID;

		if (TRUE)
		{
			uiEventSend_VERIFY_SUCCESS(nVerifyMode, UserInfo.ID);  
		}

		if (bSlaveVerified)
			goto _lSuccess;

		if (nVerifyMode != UI_VERIFY_ID)
			g_uiProcStatus.nVerifyFail = 0;

		nVerifyModeOld = nVerifyMode;
		nVerifiedList |= (1 << nVerifyMode);
		if (nVerifiedList & (1 << UI_VERIFY_PW))
			nVerifiedList |= (1 << UI_VERIFY_ID);

		if (dbLicense.bUseACFunction && g_uiProcStatus.bSOSKeyPressed)
		{
			g_uiProcStatus.bSOSKeyPressed = FALSE;
			VERIFY_DURESS_START(UserInfo.ID); //SOS key + verify duress
		}

		if ((nVerifyMode != UI_VERIFY_ID) && (g_uiProcStatus.bReqManager) && !g_uiProcStatus.bDuressFlag)
		{
			if (DbUserInfoFlagManagerGet(&UserInfo) != PRIV_USER)
			{
//				STOP_TIMER(TIMER_MANAGERREQUEST);
				g_uiProcStatus.bReqManager = FALSE;
				g_uiProcStatus.bManagerVerifyOK = TRUE;
				g_uiProcStatus.nIDCurrentMgr = UserInfo.ID;
				g_uiProcStatus.byMgr = DbUserInfoFlagManagerGet(&UserInfo);
				uiProcTimerManage();
			}
			else
			{
				nStep = 0;
				show();
				uiLcdSetLabelText(ui.lblStatusText, UISTR(UISTR_VERIFY_ILLEGAL), FOREGROUND_COLOR);
				uiSoundOut(SOUND_ERROR, UI_BUZZER_ERROR, UITIME_VOICE, TRUE);
				uiLedFail();
				uiProcTimerManage();
// 				//No manager, Log view
// 				CGLogList *pLogView = new CGLogList(NULL, &UserInfo);
// 				if (pLogView)
// 				{
// 					pLogView->show();
// 					pLogView->DoProcess();
// 					delete pLogView;
// 				}
			}
			break;
		}

// 		if (nVerifyMode != UI_VERIFY_ID)
// 			DrawPhoto(&UserInfo[0], nVerifyMode);

		if (nStep != 0)
		{
			if (nVerifiedID != nVerifiedIDPrev)
			{
				//1:1 Verify Failure
				show();
				uiLedFail();
				uiMsgStop();
				InitResults(nVerifyMode);
				nStep = 0;
				nVerifyMode = UI_VERIFY_NONE;
				uiLcdSetLabelText(ui.lblStatusText, UISTR(UISTR_VERIFY_FAIL), FOREGROUND_COLOR);
				uiBuzzerError();
//				uiSoundOut(SOUND_VERIFY_FAIL, UI_BUZZER_ERROR);
				goto _lCapture;
			}

			//RSI090227, In the case of forced pwd verify for pwd alarm, prompt "Invalid verify mode"
			if (nVerifyMode == UI_VERIFY_PW && dbSetupTotal.setSystem.bPwdAlarmUse)
			{
				bResult = CurrentVerifyIsValid(nUserVerifyMode, (1 << UI_VERIFY_ID), &nVerifyMode);
				if (!bResult || nVerifyMode != UI_VERIFY_PW)
					goto _lVerifyModeCheck;
			}
		}

		if (nStep == 0)
		{
			if (DbUserInfoFlagGVMStatusGet(&UserInfo))
			{
				nUserVerifyMode = dbSetupTotal.setTimezone.tzGrupVM[UserInfo.TIMEGROUP - 1];
				if (nUserVerifyMode == VM_NONE)
					nUserVerifyMode = dbSetupTotal.setSystem.byDefaultGVM;
			}
			else
				nUserVerifyMode = UserInfo.VERIFYMODE;
			if (g_uiProcStatus.bReqManager && nVerifyMode == UI_VERIFY_ID)
				nUserVerifyMode = VM_IDPW;

			if (nUserVerifyMode == VM_NONE)
				nUserVerifyMode = dbSetupTotal.setSystem.nVerifyMode;
		}

		if (TRUE)
		{
			bResult = CurrentVerifyIsValid(nUserVerifyMode, nVerifiedList, &nVerifyMode);

			//RSI090227, For pwd verify alarm, force go to pwd verify
			if (!bResult && dbSetupTotal.setSystem.bPwdAlarmUse && nVerifyModeOld == UI_VERIFY_ID)
			{
				bResult = TRUE;
				nVerifyMode = UI_VERIFY_PW;
			}

_lVerifyModeCheck:
			if (!bResult)
			{
				//Invalid Verify Mode !
				show();
				uiLedFail();
				uiMsgStop();
				InitResults(nVerifyModeOld);
				nStep = 0;
				nVerifyMode = UI_VERIFY_NONE;
				uiLcdSetLabelText(ui.lblStatusText, UISTR(UISTR_VERIFY_ILLEGAL), FOREGROUND_COLOR);
				uiSoundOut(SOUND_ERROR, UI_BUZZER_ERROR, UITIME_VOICE);
				goto _lCapture;
			}

			nStep++;

			if (nVerifyMode != UI_VERIFY_NONE)
			{
				switch (nVerifyMode)
				{
				case UI_VERIFY_ID:
					uiLcdSetLabelText(ui.lblStatusText, UISTR(UISTR_VERIFY_INPUT_ID), FOREGROUND_COLOR);
					break;
				case UI_VERIFY_FP:
					uiLcdSetLabelText(ui.lblStatusText, UISTR(UISTR_VERIFY_PRESS_FINGER), FOREGROUND_COLOR);
					break;
				case UI_VERIFY_RF:
					uiLcdSetLabelText(ui.lblStatusText, UISTR(UISTR_VERIFY_INPUT_CARD), FOREGROUND_COLOR);
					break;
				case UI_VERIFY_PW:
					uiLcdSetLabelText(ui.lblStatusText, UISTR(UISTR_VERIFY_INPUT_PWD), FOREGROUND_COLOR);
					break;
				}
				goto _lCapture;
			}
		}
// 		else
// 		{
// 			if (nVerifiedID != nVerifiedIDPrev)
// 			{
// 				//1:1 Verify Failure
// 				uiLedFail();
// 				uiMsgStop();
// 				InitResults(nVerifyMode);
// 				nStep = 0;
// 				nVerifyMode = UI_VERIFY_NONE;
// 				ui.lblStatusText->setText(UISTR(UISTR_VERIFY_FAIL));
// 				uiSoundOut(SOUND_VERIFY_FAIL, UI_BUZZER_ERROR);
// 				goto _lCapture;
// 			}
// 
// 			//RSI090227
// 			if (nVerifyMode == UI_VERIFY_PW && dbSetupTotal.setSystem.bPwdAlarmUse)
// 			{
// 				bResult = CurrentVerifyIsValid(nUserVerifyMode, UI_VERIFY_ID, &nVerifyMode);
// 				if (!bResult || nVerifyMode != UI_VERIFY_PW)
// 					goto _lVerifyModeCheck;
// 			}
// 		}


_lSuccess:
		bSuccess = TRUE;
		g_uiProcStatus.nLastVerifiedUser = UserInfo.ID;
		show();
		BOOL bIsReverify;
		BYTE bIsAntipassOut;
		char *szUserID;
		bIsReverify = DbGlogIsReverify2(UserInfo.ID);
		bIsAntipassOut = DbAntipassGet(UserInfo.ID);

// 		if (!DbUserInfoTzVerify(&UserInfo[0]))
// 		{
// 			uiLcdMessageBox(UI_MSG_ERROR, UISTR_VERIFY_INVALID_TZ, UI_MSGTIMEOUT);
// 			nStep = 0;
// 			nVerifyMode = UI_VERIFY_NONE;
// 			goto _lExit;
// 		}

		if ((dbSetupTotal.setSystem.byAntipassStatus == ANTIPASS_MASTER && bIsAntipassOut == ANTIPASSOUT_IN) ||
			(bSlaveVerified && UserInfo.RES[0]))
		{
			uiLcdMessageBox(UI_MSG_ERROR, UISTR_VERIFY_ANTIPASS_NOT, UI_MSGTIMEOUT);
			nStep = 0;
			nVerifyMode = UI_VERIFY_NONE;
			goto _lCapture;
		}
		//Show UserInfo
		ui.lblTrStatus->setText(UISTR(UISTR_FUNC_START + nTrType));  //xf 091120
		ui.lblID->setText(UISTR(UISTR_VERIFY_ID) + QString(":") + QString(ID2STRING(UserInfo.ID)));
		ui.lblName->setText(UISTR(UISTR_VERIFY_NAME) + QString(":") + UNICODE2STRING(UserInfo.NAME, USERNAME_LENGTH));
		ui.lblPriv->setText(UISTR(UISTR_VERIFY_PRIV) + QString(":") + UISTR(UISTR_PRIV_START + PRIV_INDEX(DbUserInfoFlagManagerGet(&UserInfo))));
		ui.lblPart->setText(UISTR(UISTR_VERIFY_PART) + QString(":") + DbPartGet(UserInfo.PART));

		uiLedOK();

		if (bSlaveVerified)
		{
			uiLcdSetLabelText(ui.lblStatusText, UISTR(UISTR_VERIFY_SUCCESS), FOREGROUND_COLOR);
			uiSoundOut(SOUND_VERIFY_SUCCESS, UI_BUZZER_OK, UITIME_VOICE);
			nStep = 0;
			nVerifyMode = UI_VERIFY_NONE;
			goto _lCapture;
		}

		if (dbLicense.bUseWiegand)
			uiWiegandSend(UserInfo.ID);

		szMessage = uiMsgGetCurrentString(UserInfo.ID, UserInfo.TIMEGROUP);

		if (szMessage.length() > 0)
			uiMsgStart(szMessage, TRUE);
		else
		{
			uiMsgStop();
			if (!bIsReverify)
				uiLcdSetLabelText(ui.lblStatusText, UISTR(UISTR_VERIFY_SUCCESS), FOREGROUND_COLOR);
			else
				uiLcdSetLabelText(ui.lblStatusText, UISTR(UISTR_VERIFY_REVERIFY), FOREGROUND_COLOR);
		}

		POST_EVENTS();

		if (dbLicense.bUseMP3 && dbSetupTotal.setSystem.bVoiceOut)
		{
			DrawPhoto(&UserInfo, nVerifyModeOld, bIsReverify);

			if (DbUserInfoHasVoice(UserInfo.ID))
			{
				char szNewFilename[] = "/tmp/tmp.mp3";
				bUserVoiceOut = TRUE;
				COPY_FILE(DbUserInfoGetVoiceFilename(UserInfo.ID), szNewFilename);
				MP3_PLAY(szNewFilename, 0);
			}
			else
			{
				bUserVoiceOut = FALSE;
				szUserID = ID2STRING(UserInfo.ID);
				for (int i=0; i<(int)strlen(szUserID); i++)
//					uiSoundOut(SOUND_START + szUserID[i] - '0', UI_BUZZER_NONE, UITIME_VOICE);
					USER_ID[i] = szUserID[i] - '0';
				USER_ID_IDX = 0;
// 				uiSoundOut(SOUND_VERIFY_SUCCESS, UI_BUZZER_OK, UITIME_VOICE);
			}   
		}
		else
		{
			if (bIsReverify)
				uiSoundOut(APLUS_REVERIFY, UI_BUZZER_OK);
			else
			{
				uiSoundOut(APLUS_OK, UI_BUZZER_OK); 
 
				xuartconfig(g_hUart[0], __UART_BAUDRATE_MAP[UISTR_BPS_9600], CS8, 0);  //BAUDRATE_9600
				xuartconfig(g_hUart[1], __UART_BAUDRATE_MAP[UISTR_BPS_9600], CS8, 0);  
                
				strcpy(szUserName, (char*)STR2ASCII(UNICODE2STRING(UserInfo.NAME,10)));
				pbuf[0] = 0xfe; pbuf[1] = 0x01; 
				pbuf[2] = 0; pbuf[3] = strlen(szUserName);
				comm_uartsend(0, pbuf, 4);
				comm_uartsend(0, szUserName, strlen(szUserName));   
				xuartconfig(g_hUart[0], __UART_BAUDRATE_MAP[dbSetupTotal.setSystem.nBaudrate], CS8, 0);
				xuartconfig(g_hUart[1], __UART_BAUDRATE_MAP[dbSetupTotal.setSystem.nBaudrate], CS8, 0);

			}
			
			DrawPhoto(&UserInfo, nVerifyModeOld, bIsReverify);
		}

		if (!bIsReverify)
		{
			int nAction = VM_NONE;

			if (nUserVerifyMode == VM_ANY)
			{
				if (nVerifiedList & (1 << UI_VERIFY_FP))
					nAction = VM_FP;
				else if (nVerifiedList & (1 << UI_VERIFY_RF))
					nAction = VM_RF;
				else if (nVerifiedList & (1 << UI_VERIFY_PW))
					nAction = VM_IDPW;
			}
			else
				nAction = nUserVerifyMode;

			if (nAction != VM_NONE)
			{
			    uiLogGlogAdd(UserInfo.ID, (BYTE)nAction, nTrType);                  
				nTrType = 0;
			}
		}

		if (dbLicense.bUseACFunction)
		{
			if (!DbUserInfoTzVerify(&UserInfo))
			{
				uiLcdMessageBox(UI_MSG_ERROR, UISTR_VERIFY_INVALID_TZ, UI_MSGTIMEOUT);
				nStep = 0;
				nVerifyMode = UI_VERIFY_NONE;
				goto _lCapture;
			}
			DoAccessControl(&UserInfo);
		}
		nStep = 0;
		nVerifyMode = UI_VERIFY_NONE;

_lCapture:
		if (!bSuccess)
			uiMsgStop();

		uiTimeSetLastActionTime();
		while (uiTimeIsTimeout(dwTimeout) == FALSE || uiMsgPersonalIsFlowing())
		{
			POST_EVENTS();
			DM9000_Check();

			if (USER_ID_IDX >= 0 && MP3_STATUS() == MAD_FLOW_STOP)
				uiSoundOut(SOUND_START + USER_ID[USER_ID_IDX++], UI_BUZZER_NONE, UITIME_VOICE);
			if (USER_ID_IDX == IDNUMBER_LENGTH)
				USER_ID_IDX = -1;

			uiProcLockManager();
			uiProcHostCommandMonitor();
			if (g_uiCommandProc)
				goto _lExit;

			nKey = uiKeyGetKey();  

			if ((nTouchX >= Ts_MainFrameNum_Min_X) && (nTouchX <= Ts_MainFrameNum_Max_X) && (nTouchY >= Ts_MainFrameNum_Min_Y) && (nTouchY <= Ts_MainFrameNum_Max_Y))  
			    goto _lExit;
			if (nKey != UIKEY_NONE)
				goto _lExit; 
			if (nKey == UIKEY_POWER ||   
				nKey == UIKEY_MENU ||
				nKey == UIKEY_UP)
			{
// 				if (nKey != UIKEY_POWER)
// 					uiProcKeyboardManager(nKey);
				goto _lExit;
			}
			if (nKey == UIKEY_DOWN)
				uiProcKeyboardManager(nKey);
			if ((nKey >= UIKEY_1 && nKey <= UIKEY_9) || (nKey == UIKEY_0 && g_uiProcStatus.bReqManager))
				nFirstDigit = nKey;
			else
				nFirstDigit = -1;


			if (nKey >= UIKEY_F1 && nKey <= UIKEY_F8) 
				nTrType = g_uiProcStatus.nTrType;   

//			if ((nVerifyMode == UI_VERIFY_ID) || (nStep == 0 && nFirstDigit))
			if (nFirstDigit >= 0)
			{
				CInputUserID w(this); w.show();
				nID = w.DoProcess(FALSE, nFirstDigit);
				w.close();
			//	if (nID)  //xf 091120
                if (nID != 0)  //xf 091120
				{
				//	if (g_uiProcStatus.bReqManager && (int)nID == -1)  //xf 091120
                    if (g_uiProcStatus.bReqManager && (int)nID == 0)  //xf 091120
					{
						VerifySManager0();
						goto _lExit;
					}
					nVerifyMode = UI_VERIFY_ID;
					if (!NextVerifyIsValid(nUserVerifyMode, nVerifiedList, nVerifyMode))
						nStep = 0;
					break;
				}
			}
//			if ((nVerifyMode == UI_VERIFY_FP) || (nStep == 0))
			if (TRUE)
			{
				if (uiCMOSCaptureFP())
				{
					nVerifyMode = UI_VERIFY_FP;
					if (!NextVerifyIsValid(nUserVerifyMode, nVerifiedList, nVerifyMode))
						nStep = 0;
					uiBuzzerAlarm();
					break;
				}
			}
//			if ((nVerifyMode == UI_VERIFY_RF) || (nStep == 0))
			if (TRUE)
			{
				if ((dwCardNumber = uiCardCapture()))
				{
					nVerifyMode = UI_VERIFY_RF;
					if (!NextVerifyIsValid(nUserVerifyMode, nVerifiedList, nVerifyMode))
						nStep = 0;
					uiBuzzerAlarm();
					break;
				}
			}
			if (nVerifyMode == UI_VERIFY_PW)
			{
				CInputUserID w(this); w.show();
				nID = (DWORD)UserInfo.ID;
				dwPassword = w.DoPwdInputProcess();
				if (dwPassword)
					break;
				else
				{
					goto _lExit;
				}
			}
		}

		if (uiTimeIsTimeout(5000))
			goto _lExit;
	}

_lExit:
	VERIFY_DURESS_INIT();
	uiMsgStop();

	if (bUserVoiceOut)
		MP3_PLAY(NULL);

	g_uiProcStatus.bVerifying = FALSE;

	LeaveVerifyInterface();
	uiProcDrawStatus();
	hide();

	if (nKey == UIKEY_MENU ||
		nKey == UIKEY_UP ||
		nKey == UIKEY_DOWN ||
		nKey == UIKEY_ESC)
	{
		uiProcKeyboardManager(nKey);
	}
}

void CVerify::VerifySManager0()
{
	if (g_uiProcStatus.bReqManager && !Db_GetManagerCountTotal())
	{
		CInputUserID w(this); w.show();
		DWORD dwPassword;
		w.SetPasswordLength(SMANAGER_PWD_LEN);
		dwPassword = w.DoPwdInputProcess();
		if (dwPassword == dbSetupTotal.setSystem.dwSManagerPwd)
		{
//			STOP_TIMER(TIMER_MANAGERREQUEST);
			g_uiProcStatus.bReqManager = FALSE;
			g_uiProcStatus.bManagerVerifyOK = TRUE;
			g_uiProcStatus.nIDCurrentMgr = 0;
			g_uiProcStatus.byMgr = PRIV_SMGR;
		}
		else if (dwPassword)
			uiSoundOut(SOUND_ERROR, UI_BUZZER_ERROR, UITIME_VOICE);
	}
}

void CVerify::DoAccessControl(USER_INFO *pUserInfo)
{
	BOOL bDoorOpen = FALSE;
	BOOL bContain = FALSE;

	SETUP_TIMER(TIMER_ACCACHE_FLUSH, 30000, 0, NULL);

	m_AcCacheGroups |= NUMBER2LOCKGROUP(pUserInfo->TIMEGROUP);
	m_ACCacheUsers.insert(pUserInfo->ID);

	if (dbSetupTotal.setSystem.nLockGroupMain > 0)
	{
		if (m_ACCacheUsers.count() >= dbSetupTotal.setSystem.nLockGroupMain)
			bDoorOpen = TRUE;
	}
	else
	{
		for (int i=0; i<MULTI_IDENT_SET_COUNT; i++)
		{
			if (dbSetupTotal.setTimezone.tzLockGroup[i] == m_AcCacheGroups)
			{
				bDoorOpen = TRUE;
				break;
			}
			if ((dbSetupTotal.setTimezone.tzLockGroup[i] & m_AcCacheGroups) == m_AcCacheGroups)
				bContain = TRUE;
		}

		if (!bDoorOpen && !bContain)
		{
			//Invalid LockGroup
			uiLcdMessageBox(UI_MSG_ERROR, UISTR_VERIFY_INVALID_GROUP, UI_MSGTIMEOUT);
			ACCacheFlush();
		}
	}

	if (bDoorOpen)
	{
		uiDoorOpen(pUserInfo->ID);
		ACCacheFlush();
	}
}

void CVerify::ACCacheFlush()
{
	m_AcCacheGroups = 0;
	m_ACCacheUsers.clear();
}

void CVerify::DrawPhoto(USER_INFO *pUserInfo, int nVerifyMode, BOOL bIsReverify)
{
	QPixmap pmap;
	int nSize;
	int nVerifyCount, nPercent;
	const char *szPrefix = NULL;
	char szFilename[64];
	BOOL bMustShowPhotoArea = FALSE;

// 	if(!SDCARD_MOUNT())
// 		return;

	if (!dbLicense.bUseCamera)
		goto _lExit;

	//ui.lblPhotoArea->setPixmap(m_pmapPhoto);

	if (dbSetupTotal.setSystem.bPhotoShow)
	{
		if (DbUserInfoHasPhoto(pUserInfo->ID) && pmap.load(DbUserInfoGetPhotoFilename(pUserInfo->ID)))
		{
	/*		DrawCamera(ui.lblPhotoArea, &m_pmapPhoto, &pmap);*/
		}
		else
			//ui.lblPhotoArea->setPixmap(m_pmapPhoto);
		POST_EVENTS();
	}

	switch (nVerifyMode)
	{
	case UI_VERIFY_FP:
		nVerifyCount = (int)g_dwVerifyCountFP;
		nPercent = (int)dbSetupTotal.setSystem.byCameraRateForFP;
		if (!bIsReverify)
			g_dwVerifyCountFP++;
		szPrefix = "FP";
		break;
	case UI_VERIFY_RF:
		nVerifyCount = (int)g_dwVerifyCountCD;
		nPercent = (int)dbSetupTotal.setSystem.byCameraRateForCard;
		if (!bIsReverify)
			g_dwVerifyCountCD++;
		szPrefix = "RF";
		break;
	case UI_VERIFY_PW:
		nVerifyCount = (int)g_dwVerifyCountPW;
		nPercent = (int)dbSetupTotal.setSystem.byCameraRateForPWD;
		if (!bIsReverify)
			g_dwVerifyCountPW++;
		szPrefix = "PW";
		break;
	}

	if (dbSetupTotal.setSystem.bCameraSave && CAMERA_CAPTURE())
	{
		nSize = sb_get_jpg_size(&g_VideoIn);
		if (pmap.loadFromData(g_VideoIn.pFramebuffer, nSize))
		{
//			if (dbSetupTotal.setSystem.bCameraShow)
//				DrawCamera(ui.lblPhotoArea, &m_pmapCamera, &pmap);
			uiSoundOut(SOUND_CAMERA_TONE, UI_BUZZER_NONE, UITIME_VOICE);
		}
		else
			goto _lExit;
	}
	else
	{
//		ui.lblCameraArea->setPixmap(m_pmapCamera);
		goto _lExit;
	}

	if (bMustShowPhotoArea && dbLicense.bUseCamera && (dbSetupTotal.setSystem.bCameraShow || dbSetupTotal.setSystem.bPhotoShow))
	{
// 		ui.lblClock->hide();
// 		ui.lblPhotoArea->show();
	}

	if (dbSetupTotal.setSystem.bCameraSave &&
		!bIsReverify &&
		SDCARD_MOUNT() &&
		(nVerifyCount*nPercent/100) != ((nVerifyCount+1)*nPercent/100))
	{
		strcpy(szFilename, SDCARD_MOUNTPOINT PATH_PHOTO_LOG);
		sprintf(&szFilename[strlen(szFilename)], "/%s-%s.jpg", uiRtcSeconds2LogStringForCamera(), ID2STRING(pUserInfo->ID));
		SAVE_FILE(szFilename, (BYTE*)g_VideoIn.pFramebuffer, nSize);
	}

_lExit:
	//ui.lblPhotoArea->show();
	if (!bMustShowPhotoArea)
	{
// 		ui.lblClock->show();
// 		ui.lblPhotoArea->hide();
	}
}

BOOL CVerify::CurrentVerifyIsValid(int nUserVerifyMode, DWORD dwVerifiedStatus, int *pnNextVerify)
{
	int nNextVerify = UI_VERIFY_NONE;
	DWORD dwMask = VERIFYMODE2MASK(nUserVerifyMode);
	BOOL bValid = TRUE;

	if (dwMask == -1UL && (dwVerifiedStatus == (1 << UI_VERIFY_ID)))
		nNextVerify = UI_VERIFY_PW;
	if ((dwMask != -1UL) && (dwVerifiedStatus ^ dwMask))
	{
		for (int i=UI_VERIFY_END; i>=UI_VERIFY_START; i--)
		{
			if (!(dwVerifiedStatus & (1 << i)) && (dwMask & (1 << i)))
				nNextVerify = i;
			if ((dwVerifiedStatus & (1 << i)) && !(dwMask & (1 << i)))
			{
				bValid = FALSE;
				break;
			}
		}
		if (!bValid)
			nNextVerify = UI_VERIFY_NONE;
	}

	if (pnNextVerify)
		*pnNextVerify = nNextVerify;

	return bValid;
}

BOOL CVerify::NextVerifyIsValid(int nUserVerifyMode, DWORD dwVerifiedStatus, int nNextVerifyMode)
{
	DWORD dwMask = VERIFYMODE2MASK(nUserVerifyMode);
	dwMask ^= dwVerifiedStatus;
	return ((dwMask & (1 << nNextVerifyMode)) >> nNextVerifyMode);
}

// void CVerify::SetVerifyStatus(int nStatus, struct _user_info *pUserInfo, int nVerifyMode)
// {
// 	switch (nStatus)
// 	{
// 	case UI_VERIFYSTATUS_SUCCESS:
// 		uiSoundOut(UISTR_SOUND_VERIFY_SUCCESS, UI_BUZZER_OK);
// 		uiLedOK(); SETUP_TIMER(TIMER_LED_ON, 1000, 0, NULL);
// 		break;
// 	case UI_VERIFYSTATUS_FAIL:
// 		uiSoundOut(UISTR_SOUND_VERIFY_FAIL, UI_BUZZER_ERROR);
// 		uiLedFail(); SETUP_TIMER(TIMER_LED_ON, 1000, 0, NULL);
// 		break;
// 	case UI_VERIFYSTATUS_GETID:
// 		ui.lblID->setText(UISTR(UISTR_VERIFY_ID) + QString(ID2STRING(pUserInfo->ID)));
// 		ui.lblName->setText(UISTR(UISTR_VERIFY_NAME) + UNICODE2STRING(pUserInfo->NAME, USERNAME_LENGTH));
// 		ui.lblPriv->setText(UISTR(UISTR_VERIFY_PRIV) + UISTR(UISTR_PRIV_START + PRIV_INDEX(UI_MANAGER_STATUS(pUserInfo))));
// 		break;
// 	case UI_VERIFYSTATUS_INVALID_VM:
// 		break;
// 	case UI_VERIFYSTATUS_INVALID_TZ:
// 		break;
// 	case UI_VERIFYSTATUS_INVALID_LG:
// 		break;
// 	case UI_VERIFYSTATUS_DOOROPEN:
// 		break;
// 	default:
// 		break;
// 	}
// }

/************************************************************************/
/*                                                                      */
/************************************************************************/
CBellDlg::CBellDlg(QWidget *parent /* = NULL */)
	: QDialog(parent)
{
	GUI_DLG_IMPL(FALSE);
	GUI_DLG_CENTER(this);
	GUI_DLG_SET_THEME_1();

	ui.label->hide();   
	ui.btnESC->hide();  
}

int CBellDlg::DoProcess(int nBellNumber)
{
	if (nBellNumber == -1)
	{
		uiBellOn(TRUE); uiSoundOut(SOUND_BELL1, UI_BUZZER_ON);
		DelayMiliSecond(1000);
		uiBellOn(FALSE); uiBuzzerOff();
		return 0;
	}
	if (nBellNumber < 0 || nBellNumber >= BELL_INFO_COUNT)
		return 0;

	int nKey = UIKEY_NONE;
	DB_TZ_NORMAL *tz = &dbSetupTotal.setTimezone.tzBell[nBellNumber];
	BYTE BellType = tz->RANGE.bEndHour;
	DWORD dwETime = uiTimeGetTickCount() + tz->RANGE.bEndMinute * 1000;
	DWORD dwLoopTime;

	ui.txtBellTime->setText(uiRtcGetTime(tz->RANGE.bStartHour * 3600 + tz->RANGE.bStartMinute * 60));
	ui.txtBellLength->setText(QString("%1").arg(tz->RANGE.bEndMinute));

	while (uiTimeGetTickCount() < dwETime)
	{
		POST_EVENTS();
		DM9000_Check();
		wdog_app_alive();

		uiBellOn(TRUE); uiSoundOut(SOUND_BELL1 + BellType, UI_BUZZER_ON);
		dwLoopTime = MIN(uiTimeGetTickCount() + 3000, dwETime);
		while (uiTimeGetTickCount() < dwLoopTime)
		{
			nKey = uiKeyGetKey();

			if ((nTouchX >= MESSAGEBOX_STOP_X) && (nTouchX <= (MESSAGEBOX_STOP_X+MESSAGEBOX_STOP_W)) && (nTouchY >= MESSAGEBOX_STOP_Y) && (nTouchY <= (MESSAGEBOX_STOP_Y+MESSAGEBOX_STOP_H)))  
				nKey = UIKEY_ESC;

			if (nKey == UIKEY_OK || nKey == UIKEY_ESC)
				break;
		}
		g_MainWindow->DrawClock();
		if (nKey == UIKEY_OK || nKey == UIKEY_ESC)
			break;

		uiBellOn(FALSE); uiBuzzerOff();
		dwLoopTime = MIN(uiTimeGetTickCount() + 1000, dwETime);
		while (uiTimeGetTickCount() < dwLoopTime)
		{
			nKey = uiKeyGetKey();

			if ((nTouchX >= MESSAGEBOX_STOP_X) && (nTouchX <= (MESSAGEBOX_STOP_X+MESSAGEBOX_STOP_W)) && (nTouchY >= MESSAGEBOX_STOP_Y) && (nTouchY <= (MESSAGEBOX_STOP_Y+MESSAGEBOX_STOP_H)))  
				nKey = UIKEY_ESC;

			if (nKey == UIKEY_OK || nKey == UIKEY_ESC)
				break;
		}
		g_MainWindow->DrawClock();
		if (nKey == UIKEY_OK || nKey == UIKEY_ESC)
			break;
	}

	BELL_OFF(); uiBuzzerOff(); MP3_PLAY(NULL);

	return 0;
}
