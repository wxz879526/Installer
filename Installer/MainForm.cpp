// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MainForm.h"
#include <sstream>

CMainForm* CMainForm::g_pMainForm = nullptr;

CMainForm::CMainForm() : SHostWnd(_T("LAYOUT:XML_MAINWND"))
{
    m_bLayoutInited = FALSE;
}

CMainForm::~CMainForm()
{
    shellNotifyIcon.Hide();
}

void CMainForm::ShowUI()
{
	if (!g_pMainForm)
	{
		g_pMainForm = new CMainForm;
		g_pMainForm->Create(GetActiveWindow());
		g_pMainForm->SendMessage(WM_INITDIALOG);
		g_pMainForm->CenterWindow();
	}

	g_pMainForm->ShowWindow(SW_SHOWNORMAL);
}

BOOL CMainForm::OnInitDialog(HWND hWnd, LPARAM lParam)
{
    //////初始化控件变量/////
    tab = FindChildByName2<STabCtrl>(L"tab_main");

    //////Welcome Page//////
    pbtn_install = FindChildByName2<SImageButton>(L"btn_install");
    /*if (pbtn_install){
        pbtn_install->EnableWindow(FALSE, TRUE);
    }*/

    pbtn_custominstall = FindChildByName2<SImageButton>(L"btn_custominstall");
    /*if (pbtn_custominstall){
        pbtn_custominstall->EnableWindow(FALSE, TRUE);
    }*/

    pchk_agreement = FindChildByName2<SCheckBox>(L"chk_agreement");
    /*if (pchk_agreement){
        pchk_agreement->SetCheck(FALSE);
    }*/
    //////END//////

    /////Choose Path Page/////
    pedit_choose_url = FindChildByName2<SEdit>(L"edit_choose_url");
    ptxt_choose_requiredspace = FindChildByName2<SStatic>(L"txt_choose_requiredspace");
    ptxt_choose_freespace = FindChildByName2<SStatic>(L"txt_choose_freespace");
    /////END//////

    m_bLayoutInited = TRUE;
    SStringW t = L"title";
    shellNotifyIcon.Create(m_hWnd, GETRESPROVIDER->LoadIcon(_T("ICON_LOGO"), 16), NIF_ICON | NIF_MESSAGE | NIF_TIP, WM_ICONNOTIFY, ID_TASKBARICON, GETSTRING(t));
    shellNotifyIcon.Show();
    return 0;
}

//TODO:消息映射
void CMainForm::OnClose()
{
    shellNotifyIcon.Hide();
    PostMessage(WM_QUIT);
}

void CMainForm::OnMaximize()
{
    SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE);
}
void CMainForm::OnRestore()
{
    SendMessage(WM_SYSCOMMAND, SC_RESTORE);
}
void CMainForm::OnMinimize()
{
    SendMessage(WM_SYSCOMMAND, SC_MINIMIZE);
}

void CMainForm::OnSize(UINT nType, CSize size)
{
    SetMsgHandled(FALSE);
    if (!m_bLayoutInited) return;

    SWindow *pBtnMax = FindChildByName(L"btn_max");
    SWindow *pBtnRestore = FindChildByName(L"btn_restore");
    if (!pBtnMax || !pBtnRestore) return;

    if (nType == SIZE_MAXIMIZED)
    {
        pBtnRestore->SetVisible(TRUE);
        pBtnMax->SetVisible(FALSE);
    }
    else if (nType == SIZE_RESTORED)
    {
        pBtnRestore->SetVisible(FALSE);
        pBtnMax->SetVisible(TRUE);
    }
}


LRESULT CMainForm::OnIconNotify(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL/* bHandled*/)
{
    switch (lParam)
    {
    case  WM_RBUTTONDOWN:
        {
            //显示右键菜单
            menu.LoadMenu(_T("menu_tray"), _T("smenu"));
            POINT pt;
            GetCursorPos(&pt);
            menu.TrackPopupMenu(0, pt.x, pt.y, m_hWnd);
        }break;
    case WM_LBUTTONDOWN:
        {
            //显示/隐藏主界面
            if (IsIconic())
                ShowWindow(SW_SHOWNORMAL);
            else
                ShowWindow(SW_MINIMIZE);
        }break;
    default:
        break;
    }
    return S_OK;
}

void CMainForm::OnCommand(UINT uNotifyCode, int nID, HWND wndCtl)
{
    if (uNotifyCode == 0)
    {
        switch (nID)
        {
        case 6:
            OnClose();
            break;
        default:
            break;
        }
    }
}

void CMainForm::OnAgreementClick() {
    if (tab) 
	{
        tab->SetCurSel(1);
    }
}

void CMainForm::OnChkAgreementClick() 
{
    if (pchk_agreement && pchk_agreement->IsChecked()) {
        pbtn_install->EnableWindow(TRUE, TRUE);
        pbtn_custominstall->EnableWindow(TRUE, TRUE);
    }
    else if (pchk_agreement && !pchk_agreement->IsChecked()) 
	{
        pbtn_install->EnableWindow(FALSE, TRUE);
        pbtn_custominstall->EnableWindow(FALSE, TRUE);
    }
}

void CMainForm::OnCustomInstallClick() 
{
    if (tab) 
	{
        tab->SetCurSel(2);
    }
}

void CMainForm::OnInstallClick() 
{
    if (tab) 
	{
        tab->SetCurSel(5);
    }
}

void CMainForm::OnAgreementSureClick() 
{
    if (tab) 
	{
        tab->SetCurSel(0);
    }
}

void CMainForm::OnChoosePreviousClick()
{
    if (tab) 
	{
        tab->SetCurSel(0);
    }
}

void CMainForm::OnChooseInstallClick() {
    if (tab) 
	{
        tab->SetCurSel(3);
		//tab->SetCurSel(4);
    }
}

void CMainForm::OnChooseChangeDirClick() {

    //pedit_choose_url
}

LRESULT CMainForm::OnUpdateHDFreeSpaceClick(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL/* bHandled*/) {
    if (ptxt_choose_freespace) {
        wstring freeSize = (wchar_t*)wParam;
        freeSize += _T("MB");
        //s1.Replace(_T("$"), freeSize.c_str());
        ptxt_choose_freespace->SetWindowTextW(freeSize.c_str());
    }
    return 0;
}
LRESULT CMainForm::OnUpdateRequiredSpaceClick(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL/* bHandled*/) {
    if (ptxt_choose_requiredspace) {
        wstring requiredSize = (wchar_t*)wParam;
        requiredSize += _T("MB");
        ptxt_choose_requiredspace->SetWindowTextW(requiredSize.c_str());
    }
    return 0;
}

LRESULT CMainForm::OnStopMsgLoop(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL/* bHandled*/) {
    /*if (tab){
        tab->SetCurSel(3);
    }*/
    SImageButton* pbtn_close = FindChildByName2<SImageButton>(L"btn_close");
    SImageButton* pbtn_min = FindChildByName2<SImageButton>(L"btn_min");
    if (pbtn_close)
        pbtn_close->SetVisible(FALSE, TRUE);
    if (pbtn_min)
        pbtn_min->SetVisible(FALSE, TRUE);

    SetTimer(TMR_AUTOCHANGE, 3000);
    PostMessage(WM_QUIT);
    //if (theApp->isRun)
    //theApp->isRun = FALSE;
    //else theApp->isRun = TRUE;
    return 0;
}

void CMainForm::OnUnstallStartNext() 
{
    if (tab) 
	{
        tab->SetCurSel(6);
    }
}


void CMainForm::OnStartUninstall()
{
	if (tab)
		tab->SetCurSel(8);
}

void CMainForm::OnTimer(UINT_PTR nIDEvent)
{
    SetMsgHandled(FALSE);
    if (nIDEvent == TMR_AUTOCHANGE)
    {
        if (tab)
        {
            size_t tab_index = tab->GetCurSel();
            if (tab_index == 3)
            {
                STabCtrl* ptab_installing = FindChildByName2<STabCtrl>(L"tab_installing");
                if (ptab_installing)
                {
                    size_t index = ptab_installing->GetCurSel();
                    if (index >= ptab_installing->GetItemCount() - 1)
                    {
                        index = 0;
                    }
                    else
                    {
                        index++;
                    }
                    ptab_installing->SetCurSel(index);
                }
            }
        }

    }
}

