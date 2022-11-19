#include "stdafx.h"
#include "Game.h"
#include "IMark.h"
#include "ScreenTools.h"

CGame::CGame(HWND hWnd, float x, float y, float w, float h)
    : m_hWnd(hWnd)
    , m_x(x)
    , m_y(y)
    , m_width(w)
    , m_height(h)
{
    // ����ȫ��ָ��
    g_game = this;
    // �˵���ʼ��
    m_menu = std::make_shared<CDMenu>(hWnd);
    {
        // ��ͼ������Ļ�������Լ��Ĵ�����
        RECT r{(long)x, (long)y, (long)(x + w), (long)(y + h)};
        HBITMAP hBmp = CScreenTools::CopyScreenToBitmap(&r);
        // ���汳��ͼ
        m_imgBk = Bitmap::FromHBITMAP(hBmp, NULL);
    }

    // ��ȡ���ڿͻ�����С
    GetClientRect(m_hWnd, &m_rcClient);
}


CGame::~CGame()
{
}


// ��Ϸ��һ֡
bool CGame::EnterFrame(DWORD dwTime)
{
    /*
        �滭
        ����
    */
    Draw();
    return false;
}

// ����������
void CGame::OnLButtonDown(UINT nFlags, CPoint point)
{
    switch(m_eStatus) {
        case CGame::EGameStatusSelect: {
            // �˵� �׶� : ���� m_menu �˵�����
            if(m_menu->OnLButtonDown(nFlags, point)) {
                break;
            }

            // ��������
            break;
        }
        case CGame::EGameStatusNormal: {
            // ��Ϸ �׶�
            if(m_pTool->OnLButtonDown(nFlags, point)) {
                break;
            }
            // ��������
            break;
        }
        default: {
            break;
        }
    }
}

// ������̧��
void CGame::OnLButtonUp(UINT nFlags, CPoint point)
{
    switch(m_eStatus) {
        case CGame::EGameStatusSelect: {
            // �˵� �׶� : ���� m_menu �˵�����
            if(m_menu->OnLButtonUp(nFlags, point)) {
                break;
            }

            // ��������
            break;
        }
        case CGame::EGameStatusNormal: {
            // ��Ϸ �׶�
            if(m_pTool->OnLButtonUp(nFlags, point)) {
                break;
            }
            // ��������
            break;
        }
        default: {
            break;
        }
    }

}

// ������˫��
void CGame::OnLButtonDblClk(UINT nFlags, CPoint point)
{
}

// ����Ҽ�����
void CGame::OnRButtonDown(UINT nFlags, CPoint point)
{
    switch(m_eStatus) {
        case CGame::EGameStatusSelect: {
            // �˵� �׶� : ���� m_menu �˵�����
            if(m_menu->OnRButtonDown(nFlags, point)) {
                break;
            }

            // ��������
            break;
        }
        case CGame::EGameStatusNormal: {
            // ��Ϸ �׶�
            m_pTool->OnRButtonDown(nFlags, point);
            break;
        }
        default: {

            break;
        }
    }
}

// ����Ҽ�̧��
void CGame::OnRButtonUp(UINT nFlags, CPoint point)
{
    switch(m_eStatus) {
        case CGame::EGameStatusSelect: {
            // �˵� �׶� : ���� m_menu �˵�����
            if(m_menu->OnRButtonUp(nFlags, point)) {
                break;
            }

            // ��������
            break;
        }
        case CGame::EGameStatusNormal: {
            // ��Ϸ �׶�
            m_pTool->OnRButtonUp(nFlags, point);
            break;
        }
        default: {

            break;
        }
    }
}

// ����Ҽ�˫��
void CGame::OnRButtonDblClk(UINT nFlags, CPoint point)
{
    // ʲôҲ����
}

// ����ƶ�
void CGame::OnMouseMove(UINT nFlags, CPoint point)
{
    switch(m_eStatus) {
        case CGame::EGameStatusSelect: {
            // �˵� �׶� : ���� m_menu �˵�����
            if(m_menu->OnMouseMove(nFlags, point)) {
                break;
            }

            // ��������
            break;
        }
        case CGame::EGameStatusNormal: {
            // ��Ϸ �׶�
            m_pTool->OnMouseMove(nFlags, point);

            // ��������
            break;
        }
        default: {
            break;
        }
    }
}

// ���� ESC ��ʱ�Ĵ���
BOOL CGame::OnESC()
{
    switch(m_eStatus) {
        case CGame::EGameStatusSelect:
            // ��ǰ û������Ϸ��������
            return FALSE;
            break;
        case CGame::EGameStatusNormal:
            // ��ǰ����Ϸ���ص� �˵�
            m_eStatus = EGameStatusSelect;
            // ��ʾ���
            {
                // ��ʼ״̬,������0,���Ա�֤��0�Ϳ�����ʾ��
                int i = ShowCursor(TRUE);
                if(i > 0) {
                    // ���ٵ�0
                    while(ShowCursor(FALSE) > 0) {
                        ;
                    }
                }
                else if(i < 0) {
                    // ���ӵ�0
                    while(ShowCursor(TRUE) < 0) {
                        ;
                    }
                }
            }
            return TRUE;
        default:
            break;
    }

    return FALSE;
}

void CGame::Draw()
{
    // ����Ǵ���DC
    HDC hdc = ::GetDC(m_hWnd);
    // �뿪����������ʱ���ͷ�DC
    ON_SCOPE_EXIT([&]() {
        ::ReleaseDC(m_hWnd, hdc);
    });


    // ��ָ����һ����ʱָ�룬�����ͷ�
    CDC *dc = CClientDC::FromHandle(hdc);

    // ˫�����ͼ��
    // �ڴ�DC
    CDC m_dcMemory;
    // ��������λͼ���󣬲�ѡ�� �ڴ�DC
    CBitmap bmp;
    bmp.CreateCompatibleBitmap(dc, m_rcClient.Width(), m_rcClient.Height());
    m_dcMemory.CreateCompatibleDC(dc);
    // ѡ��DC
    CBitmap *pOldBitmap = m_dcMemory.SelectObject(&bmp);

    // �������
    Graphics gh(m_dcMemory.GetSafeHdc());
    // ���õ�λ
    gh.SetPageUnit(Gdiplus::UnitPixel);

    // �������
    Color clr;
    clr.SetFromCOLORREF(BACK_GROUND_LAYER);
    gh.Clear(clr);
    gh.ResetClip();

    // �ϲ�����ͼ�Ͳ�������
    if(!m_vMarks.empty()) {
        Graphics gh(m_imgBk);
        for(auto ptr : m_vMarks) {
            // ���ٱ仯�Ķ���ֱ�Ӻϲ��뱳��ͼƬ�У�������߻�ͼЧ��
            if(!ptr->IsChanging()) {
                ptr->Draw(gh);
            }
        }
        // ɾ�����ٱ仯�ĵĶ���
        m_vMarks.erase(std::remove_if(m_vMarks.begin(),
                                      m_vMarks.end(),
                                      [](auto & lhs)->bool {return !lhs->IsChanging(); })
                       , m_vMarks.end());
    }

    // ������ͼƬ
    gh.DrawImage(m_imgBk, m_x, m_y, m_width, m_height);

    // ���������䶯�Ķ���:���䶯�ļ����뱳��ͼƬ��
    for(auto &ptr : m_vMarks) {
        ptr->Draw(gh);
    }

    // ������Ϸ��ǰ�׶Σ�����ͬ�Ķ���
    {
        switch(m_eStatus) {
            case CGame::EGameStatusSelect:
                // ���˵�
                m_menu->Draw(gh);
                break;
            case CGame::EGameStatusNormal:
                // ��������
                m_pTool->Draw(gh);
                break;
            default:
                break;
        }
    }

    // ����FPS
    DrawFps(gh);

    // ��������Ļ
    ::BitBlt(hdc, 0, 0, m_rcClient.Width(), m_rcClient.Height(), m_dcMemory.GetSafeHdc(), 0, 0, SRCCOPY);

    return;
}

// �� fps
void CGame::DrawFps(Gdiplus::Graphics &gh)
{
    // ��¼��ǰfps
    static int fps = 0;
    // ÿ֡+1
    m_fps++;
    // ���һ�����ʱ��
    static DWORD dwLast = GetTickCount();
    // ������� 1���ӣ������fps,�����������
    if(GetTickCount() - dwLast >= 1000) {
        fps = m_fps;
        m_fps = 0;
        dwLast = GetTickCount();
    }

    // ���fps
    {
        // ���������
        CString s;
        s.Format(_T("FPS:%d"), fps);
        gh.DrawString(s.GetString(), -1, &m_font, origin, &m_brush);
    }
}
