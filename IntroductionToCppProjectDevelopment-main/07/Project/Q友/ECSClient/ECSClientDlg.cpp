// ECSClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ECSClient.h"
#include "ECSClientDlg.h"
#include "Message.h"
#include "SendDlg.h"
#include "ScrollParent.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
#define SEX_MAN 10000
#define SEX_WOMAN 10001

extern CScrollParent *SkinScrollBar(CWnd *pWnd);

class CAboutDlg : public CDialog
{
public:
    CAboutDlg();

// Dialog Data
    //{{AFX_DATA(CAboutDlg)
    enum { IDD = IDD_ABOUTBOX };
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CAboutDlg)
protected:
    virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:
    //{{AFX_MSG(CAboutDlg)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
    //{{AFX_DATA_INIT(CAboutDlg)
    //}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange *pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CAboutDlg)
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
    //{{AFX_MSG_MAP(CAboutDlg)
    // No message handlers
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CECSClientDlg dialog

CECSClientDlg::CECSClientDlg(CWnd *pParent /*=NULL*/)
    : CDialog(CECSClientDlg::IDD, pParent)
{
    //{{AFX_DATA_INIT(CECSClientDlg)
    //}}AFX_DATA_INIT
    // Note that LoadIcon does not require a subsequent DestroyIcon in Win32
    m_hIcon = AfxGetApp()->LoadIcon(IDI_MAINICON);
    m_nLoginUser = 12345;
    m_nTestNum  = 0;
    m_bLogined = FALSE;
    HRESULT hr;
    hr = m_pXMLDoc.CreateInstance(__uuidof(DOMDocument30));
}

void CECSClientDlg::DoDataExchange(CDataExchange *pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CECSClientDlg)
    DDX_Control(pDX, IDC_ACLIST, m_ACList);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CECSClientDlg, CDialog)
    //{{AFX_MSG_MAP(CECSClientDlg)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_NOTIFY(TVN_SELCHANGED, IDC_ACLIST, OnSelchangedAclist)
    ON_NOTIFY(NM_DBLCLK, IDC_ACLIST, OnDblclkAclist)
    ON_WM_CLOSE()
    ON_WM_TIMER()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CECSClientDlg message handlers

BOOL CECSClientDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // Add "About..." menu item to system menu.

    // IDM_ABOUTBOX must be in the system command range.
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu *pSysMenu = GetSystemMenu(FALSE);
    if(pSysMenu != NULL) {
        CString strAboutMenu;
        strAboutMenu.LoadString(IDS_ABOUTBOX);
        if(!strAboutMenu.IsEmpty()) {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    // Set the icon for this dialog.  The framework does this automatically
    //  when the application's main window is not a dialog
    SetIcon(m_hIcon, TRUE);         // Set big icon
    SetIcon(m_hIcon, FALSE);        // Set small icon

    // ??????????????????????????????????
    m_ImageList.Create(16, 16, ILC_COLOR32 | ILC_MASK, 1, 0);
    CBitmap bmp;
    // ????????
    bmp.LoadBitmap(IDB_DEPART);
    m_ImageList.Add(&bmp, RGB(255, 255, 255));
    bmp.Detach();

    // ????????
    bmp.LoadBitmap(IDB_MAN);
    m_ImageList.Add(&bmp, RGB(255, 255, 255));
    bmp.Detach();

    // ????????
    bmp.LoadBitmap(IDB_WOMAN);
    m_ImageList.Add(&bmp, RGB(255, 255, 255));
    bmp.Detach();

    // ????????
    bmp.LoadBitmap(IDB_PERSON);
    m_ImageList.Add(&bmp, RGB(255, 255, 255));

    // ????????????
    m_ACList.SetImageList(&m_ImageList, TVSIL_NORMAL);

    // ??????????
    SkinScrollBar(&m_ACList);

    // ??????????:????????????
    SetTimer(1, 2000, NULL);

    return TRUE;  // return TRUE  unless you set the focus to a control
}

void CECSClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if((nID & 0xFFF0) == IDM_ABOUTBOX) {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    }
    else {
        CDialog::OnSysCommand(nID, lParam);
    }
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CECSClientDlg::OnPaint()
{
    if(IsIconic()) {
        CPaintDC dc(this); // device context for painting

        SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

        // Center icon in client rectangle
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // Draw the icon
        dc.DrawIcon(x, y, m_hIcon);
    }
    else {
        CDialog::OnPaint();
    }
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CECSClientDlg::OnQueryDragIcon()
{
    return (HCURSOR) m_hIcon;
}

void CECSClientDlg::OnOK()
{
//  CSendDlg dlg;
//  dlg.DoModal();
}



// ??xml??????????????
void CECSClientDlg::LoadOrgFromFile(BSTR csFileName)
{
    m_pXMLDoc->load(csFileName);
    MSXML2::IXMLDOMElementPtr childNode ;

    // ??????????????
    m_ACList.DeleteAllItems();
    //??????????
    childNode = m_pXMLDoc->selectSingleNode("// ITEM[@????ID = 0]");
    // ????????
    while(childNode != NULL) {
        // ????????
        FindSubNode(childNode, TVI_ROOT);
        childNode = childNode->GetnextSibling();
    }
    // ??????????
    HTREEITEM hRoot = m_ACList.GetRootItem();
    // ????
    m_ACList.Expand(hRoot, TVE_EXPAND);
    // ????????????
    SetUserState(m_nLoginUser, 1);
}

void CECSClientDlg::FindSubNode(MSXML2::IXMLDOMElementPtr pParentNode ,
                                HTREEITEM hParentItem)
{
    if(pParentNode != NULL) {
        VARIANT varVal;
        CString strValue = "";
        CString csText = "";
        // ????text????

        varVal = pParentNode->getAttribute("text");
        if(varVal.vt != VT_EMPTY) {
            csText = (char *)(_bstr_t)varVal;
        }

        // ????????ID
        strValue = "";
        varVal = pParentNode->getAttribute("????ID");
        int DepartID = 0;
        if(varVal.vt != VT_EMPTY) {
            strValue = (char *)(_bstr_t)varVal;
            DepartID = atoi(strValue);
        }

        // ????????????ID
        strValue = "";
        varVal = pParentNode->getAttribute("????ID");
        int ParentID = 0;
        if(varVal.vt != VT_EMPTY) {
            strValue = (char *)(_bstr_t)varVal;
            ParentID = atoi(strValue);
        }

        // ????????ID
        strValue = "";
        varVal = pParentNode->getAttribute("????ID");
        int UserID = 0;
        if(varVal.vt != VT_EMPTY) {
            strValue = (char *)(_bstr_t)varVal;
            UserID = atoi(strValue);
        }

        // ????????????
        strValue = "";
        varVal = pParentNode->getAttribute("????????");
        if(varVal.vt != VT_EMPTY) {
            strValue = (char *)(_bstr_t)varVal;
        }

        // ????????
        CString csSex = "";
        varVal = pParentNode->getAttribute("????");
        if(varVal.vt != VT_EMPTY) {
            csSex = (char *)(_bstr_t)varVal;
        }

        // ??????????????????????
        HTREEITEM hRoot;
        DWORD dwData = 0;
        if(UserID == 0) {
            hRoot = m_ACList.InsertItem(csText, 0, 0, hParentItem);
            dwData = MAKELPARAM(DepartID, ParentID); // ????????????????

        }
        else {
            hRoot = m_ACList.InsertItem(csText, 3, 3, hParentItem); // ????????

            // ??????????????????????????
            if(csSex == "??") {
                dwData = MAKELPARAM(SEX_MAN, UserID); // ????????????
            }
            else if(csSex == "??") {
                dwData = MAKELPARAM(SEX_WOMAN, UserID); // ????????????
            }

        }

        // ????????????
        m_ACList.SetItemData(hRoot, dwData);

        MSXML2::IXMLDOMElementPtr pNode = pParentNode->GetfirstChild();
        while(pNode != NULL) {
            // ????????

            FindSubNode(pNode, hRoot);
            pNode = pNode->GetnextSibling();
        }
    }
}

void CECSClientDlg::OnSelchangedAclist(NMHDR *pNMHDR, LRESULT *pResult)
{
    *pResult = 0;
}

// ??????
void CECSClientDlg::OnDblclkAclist(NMHDR *pNMHDR, LRESULT *pResult)
{
    NM_TREEVIEW *pNMTreeView = (NM_TREEVIEW *)pNMHDR;
    HTREEITEM hItem = m_ACList.GetSelectedItem();
    HTREEITEM hRoot = m_ACList.GetRootItem();
    if(hItem != NULL) {
        // ??????????????????????????0????????????????ID
        DWORD dwData = m_ACList.GetItemData(hItem);
        int ID = HIWORD(dwData);
        int lowID = LOWORD(dwData);
        // ????????????????????????????????????????????????????????????????
        if((lowID == SEX_MAN || lowID == SEX_WOMAN) &&
           ID != 0 && ID != m_nLoginUser) {
            CSendDlg *pDlg = NULL;
            POSITION pos = NULL;
            if(SearchSendDlg(ID, pos) == FALSE) {
                pDlg = new CSendDlg();
                // ????????????????ID
                pDlg->m_UserID = ID;
                pDlg->Create(IDD_SENDDLG_DIALOG);
                m_pSdDlgList.AddTail(pDlg);
            }
            else if(pDlg == NULL && pos != NULL) {
                pDlg = (CSendDlg *)m_pSdDlgList.GetAt(pos);
            }
            if(pDlg != NULL) {
                // ????????????ID

                CString csID;
                csID.Format("%d", ID);
                pDlg->m_DesID.ResetContent();   // ????????

                pDlg->m_DesID.AddString(csID);
                pDlg->m_DesID.SetCurSel(0);
                CString csName = m_ACList.GetItemText(hItem);
                // ??????????????
                pDlg->m_DesName.ResetContent(); // ????????
                pDlg->m_DesName.AddString(csName);
                pDlg->m_DesName.SetCurSel(0);

                // ????????????ID??????
                CString csLocalID;
                csLocalID.Format("%d", m_nLoginUser);
                pDlg->m_LocalID.SetWindowText(csLocalID);
                CString csLocalName = "";
                BOOL bRet = FindUserName(m_nLoginUser, csLocalName);
                if(bRet) {
                    pDlg->m_LocalName.SetWindowText(csLocalName);
                }
                // ????????
                pDlg->ShowWindow(SW_SHOW);

                // ??????????????????????????????????
                pDlg->SetWindowPos(&wndTop, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
            }
        }
    }
    *pResult = 0;
}

/********************************************************

????????????????????????ID????????????????????????????????
          ????????????????????????????????????????????????
          ????

*********************************************************/
BOOL CECSClientDlg::SearchSendDlg(int nID, POSITION &ptPos)
{
    BOOL bRet = FALSE;
    int nCount = m_pSdDlgList.GetCount();
    if(nCount != 0)     // ??????????????????????????????

    {
        POSITION pos = m_pSdDlgList.GetHeadPosition();
        while(pos != NULL) {
            CSendDlg *pDlg = NULL;
            ptPos = pos;
            pDlg = (CSendDlg *)m_pSdDlgList.GetNext(pos);
            if(pDlg != NULL) {
                if(pDlg->m_UserID == nID) {
                    bRet = TRUE;
                    break;
                }
            }
            else {
                ptPos = NULL;
            }
        }
    }
    return bRet;
}
// ????????ID,??????????????????????

BOOL CECSClientDlg::FindUserName(int nUserID, CString &csName)
{
    HTREEITEM hRoot = m_ACList.GetRootItem();
    if(hRoot != NULL) {
        HTREEITEM hSubItem;
        return  FindNode(hRoot, nUserID, csName, hSubItem);
    }
    return FALSE;
}

BOOL CECSClientDlg::FindNode(HTREEITEM hParent, int nUserID,
                             CString &csName, HTREEITEM &hRetItem)
{
    // ????????????????????

    // ????????????????????????????????????????????????ID

    DWORD dwData = m_ACList.GetItemData(hParent);
    int ID = HIWORD(dwData);
    int lowID = LOWORD(dwData);
    CString csNodeName =  m_ACList.GetItemText(hParent);
    if((lowID == SEX_MAN || lowID == SEX_WOMAN) && ID == nUserID) // ??????????

    {
        csName = m_ACList.GetItemText(hParent);
        hRetItem = hParent;
        return TRUE;
    }
    else    // ????????????????????????????

    {
        if(m_ACList.ItemHasChildren(hParent)) {
            HTREEITEM hSubItem = m_ACList.GetChildItem(hParent);
            while(hSubItem != NULL) {
                BOOL bRet = FindNode(hSubItem, nUserID, csName, hRetItem);
                if(bRet) {
                    return bRet;
                }
                hSubItem = m_ACList.GetNextItem(hSubItem, TVGN_NEXT);
            }
        }
        // ????????????????????????????

        HTREEITEM hNextNode = m_ACList.GetNextItem(hParent, TVGN_NEXT);
        while(hNextNode != NULL) {
            return FindNode(hNextNode, nUserID, csName, hRetItem);
            hNextNode = m_ACList.GetNextItem(hNextNode, TVGN_NEXT);
        }
    }
    return FALSE;
}

void CECSClientDlg::OnClose()
{
    CDialog::OnClose();
}

void CECSClientDlg::OnCancel()
{
    if(m_nLoginUser != 0) {
        // ????????????????????

        CMessage Msg;
        Msg.m_nMsgType = MT_DISCONNECT;
        Msg.m_nAccountID[0] = m_nLoginUser;
        m_ClientSock.Send(&Msg, sizeof(CMessage), MSG_OOB);
    }
    CDialog::OnCancel();
}

// ????????ID????????????
void CECSClientDlg::SetUserState(int nUserID, int nState)
{
    // ????????ID????????????

    HTREEITEM hRoot = m_ACList.GetRootItem();
    if(hRoot != NULL) {
        HTREEITEM hSubItem;
        CString csName;
        BOOL bRet = FindNode(hRoot, nUserID, csName, hSubItem);
        if(bRet) {
            // ????????????????

            DWORD dwData = m_ACList.GetItemData(hSubItem);
            WORD nSex = LOWORD(dwData);
            int nImage, nSelImage;
            m_ACList.GetItemImage(hSubItem, nImage, nSelImage);
            if(nState == 0) {
                if(nImage != 3) {
                    m_ACList.SetItemImage(hSubItem, 3, 3);
                }
            }
            else {
                if(nSex == SEX_MAN) {
                    if(nImage != 1) {
                        m_ACList.SetItemImage(hSubItem, 1, 1);
                    }
                }
                else if(nSex == SEX_WOMAN) {
                    if(nImage != 2) {
                        m_ACList.SetItemImage(hSubItem, 2, 2);
                    }
                }
            }
        }
    }
}

void CECSClientDlg::OnTimer(UINT nIDEvent)
{
    if(nIDEvent == 1) {
        if(m_nTestNum > 4) { // 4*2??????????????????????????????????????????
            HTREEITEM hRoot = m_ACList.GetRootItem();
            SetAllUserState(hRoot, 0);
            m_nTestNum = 0;
            SetUserState(m_nLoginUser, 0);

            // ??????????????
            // ??????
            char chHostName[MAX_PATH] = {0};
            gethostname(chHostName, MAX_PATH);
            hostent *phost = gethostbyname(chHostName);
            // ???? ????IP
            char *chIP = inet_ntoa(*(in_addr *)phost->h_addr_list[0]);
            m_ClientSock.ShutDown();
            m_ClientSock.Close();
            m_ClientSock.Create(3000 + rand() % 2000, SOCK_STREAM, chIP);

            BOOL bEnable = TRUE;
            m_ClientSock.SetSockOpt(SO_OOBINLINE, &bEnable , sizeof(BOOL));

            BOOL bRet = m_ClientSock.Connect(m_ServerIP, m_nPort);
            // ????????????
            if(bRet) {
                // ????????????????
                CMessage cmLoginInfo;
                CString csID;
                csID.Format("%d", m_nLoginUser);

                strncpy(cmLoginInfo.m_chAccount, csID, csID.GetLength());
                strncpy(cmLoginInfo.m_chPassword, m_Password, m_Password.GetLength());
                cmLoginInfo.m_nMsgType = MT_FIRSTLOG;
                m_ClientSock.Send(&cmLoginInfo, sizeof(CMessage));
            }
        }
        else {
            m_nTestNum++;
        }
    }
    CDialog::OnTimer(nIDEvent);
}

void CECSClientDlg::SetAllUserState(HTREEITEM hParent, int nState)
{
    // ????????????????????
    // ????????????????????????????????????????????????ID
    DWORD dwData = m_ACList.GetItemData(hParent);
    int ID = HIWORD(dwData);
    int lowID = LOWORD(dwData);
    if(lowID == SEX_MAN || lowID == SEX_WOMAN) { // ??????????
        if(nState == 0) {
            m_ACList.SetItemImage(hParent, 3, 3);
        }
        else {
            if(lowID == SEX_MAN) {
                m_ACList.SetItemImage(hParent, 1, 1);
            }
            else if(lowID == SEX_WOMAN) {
                m_ACList.SetItemImage(hParent, 2, 2);
            }
        }
    }
    else {  // ????????????????????????????
        if(m_ACList.ItemHasChildren(hParent)) {
            HTREEITEM hSubItem = m_ACList.GetChildItem(hParent);
            while(hSubItem != NULL) {
                SetAllUserState(hSubItem, nState);
                hSubItem = m_ACList.GetNextItem(hSubItem, TVGN_NEXT);
            }
        }
        // ????????????????????????????

        HTREEITEM hNextNode = m_ACList.GetNextItem(hParent, TVGN_NEXT);
        while(hNextNode != NULL) {
            SetAllUserState(hNextNode, nState);
            hNextNode = m_ACList.GetNextItem(hNextNode, TVGN_NEXT);
        }
    }
}
