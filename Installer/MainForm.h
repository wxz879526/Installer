
/////////////////////////////////////////////////////////////////////////////
#pragma once
#include <map>
#include "event.h"
#include "SShellNotifyIcon.h"
using namespace std;

#define TMR_AUTOCHANGE     10000001

class CMainForm : public SHostWnd
{
public:
	CMainForm();
    ~CMainForm();

	static void ShowUI();

    void OnClose();
    void OnMaximize();
    void OnRestore();
    void OnMinimize();
    void OnSize(UINT nType, CSize size);

    //托盘通知消息处理函数
    LRESULT OnIconNotify(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL/* bHandled*/);

    void OnCommand(UINT uNotifyCode, int nID, HWND wndCtl);

	BOOL OnInitDialog(HWND wndFocus, LPARAM lInitParam);
   
    //点击查看软件协议
    void OnAgreementClick();
    //点击同意协议
    void OnChkAgreementClick();
    //点击自定义按钮
    void OnCustomInstallClick();
    //点击快速安装
    void OnInstallClick();

    //点击协议确认按钮
    void OnAgreementSureClick();

    //自定义安装页面-返回上一步
    void OnChoosePreviousClick();

    //自定义安装页面-安装
    void OnChooseInstallClick();
    //选择安装目录
    void OnChooseChangeDirClick();
    //更新磁盘空闲大小
    LRESULT OnUpdateHDFreeSpaceClick(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL/* bHandled*/);
    //更新所需空间大小
    LRESULT OnUpdateRequiredSpaceClick(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL/* bHandled*/);

    LRESULT OnStopMsgLoop(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL/* bHandled*/);

    //卸载第一页-下一页
    void OnUnstallStartNext();

	void OnStartUninstall();

    void OnTimer(UINT_PTR nIDEvent);

protected:
    //soui消息
    EVENT_MAP_BEGIN()
        EVENT_NAME_COMMAND(L"btn_min", OnMinimize)
        EVENT_NAME_COMMAND(L"btn_max", OnMaximize)
		EVENT_NAME_COMMAND(L"btn_close", OnClose)
        EVENT_NAME_COMMAND(L"btn_restore", OnRestore)
		EVENT_NAME_COMMAND(L"link_agreement", OnAgreementClick)
		EVENT_NAME_COMMAND(L"btn_agreement_sure", OnAgreementSureClick)
		EVENT_NAME_COMMAND(L"btn_custominstall", OnCustomInstallClick)
		EVENT_NAME_COMMAND(L"btn_choose_previous", OnChoosePreviousClick)
		EVENT_NAME_COMMAND(L"btn_choose_install", OnChooseInstallClick)
		EVENT_NAME_COMMAND(L"chk_agreement", OnChkAgreementClick)
		EVENT_NAME_COMMAND(L"btn_install", OnInstallClick)
		EVENT_NAME_COMMAND(L"btn_unstallstart_next", OnUnstallStartNext)
		EVENT_NAME_COMMAND(L"btn_unstallchoose_unnstall", OnStartUninstall)
	EVENT_MAP_END()

    //HostWnd真实窗口消息处理
    BEGIN_MSG_MAP_EX(CMainForm)
        MSG_WM_INITDIALOG(OnInitDialog)
        MSG_WM_SIZE(OnSize)
        MSG_WM_TIMER(OnTimer)

        //托盘消息处理
        MESSAGE_HANDLER(WM_ICONNOTIFY, OnIconNotify)
        MSG_WM_COMMAND(OnCommand)

        MESSAGE_HANDLER(WM_SJTHREEUPDATEFREESPACE, OnUpdateHDFreeSpaceClick)
        MESSAGE_HANDLER(WM_SJTHREEUPDATEREQUIREDSPACE, OnUpdateRequiredSpaceClick)
        MESSAGE_HANDLER(WM_SJMSGLOOPSTOP, OnStopMsgLoop)


		REFLECT_NOTIFICATIONS_EX()
		CHAIN_MSG_MAP(SHostWnd)
    END_MSG_MAP()

private:
    BOOL			m_bLayoutInited;
    SShellNotifyIcon shellNotifyIcon;
    //安装主导航
    STabCtrl *tab;

    ////////Welcome Page/////////
    //立刻安装按钮
    SImageButton *pbtn_install;
    //自定义安装按钮
    SImageButton *pbtn_custominstall;
    //同意协议按钮
    SCheckBox *pchk_agreement;
    //安装路径
    SEdit *pedit_choose_url;
    //需要空间大小
    SStatic *ptxt_choose_requiredspace;
    //可用空间大小
    SStatic *ptxt_choose_freespace;

    //子控件与外部脚本绑定，方便程序反向调用触发脚本函数
    // wstring : 控件名称	int: 脚本函数地址
    std::map<wstring, int> m_controlCallbackMap;

	static CMainForm *g_pMainForm;
public:
    SMenu menu;

    //执行NSIS脚本
    bool DoExecuteCodeSegment(EventArgs* evt) {

        std::map<wstring, int >::iterator iter = this->m_controlCallbackMap.find(evt->nameFrom);
        if (iter != m_controlCallbackMap.end()) {
            //MessageBox(NULL, evt->nameFrom, _T(""), MB_OK);
            //g_pluginParms->ExecuteCodeSegment(iter->second - 1, g_hwndParent);
        }
        return true;
    }

    //外部调用-添加子控件与外部脚本绑定
    void AddToControlCallbackMap(wstring ctlName, int callback)
    {
        m_controlCallbackMap[ctlName] = callback;
        SWindow *child = FindChildByName(ctlName.c_str());
        child->GetEventSet()->subscribeEvent(EVT_CMD, Subscriber(&CMainForm::DoExecuteCodeSegment, this));
    }
};
