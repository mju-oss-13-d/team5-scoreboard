#include "boardframe.hpp"
#include "teampanel.hpp"
#include "gamepanel.hpp"
#include "ctrlpanel.hpp"
#include "confdlg.hpp"
#include <wx/aboutdlg.h>

#if defined(__WXGTK__) || defined(__WXMOTIF__)
#include "scoreboard.xpm"
#endif

//      1    :         2         :    1
// +---------+-------------------+---------+
// |         |                   |         |
// |         |                   |         |
// |  team   |                   |  team   |
// |  panel  |     game panel    |  panel  |
// |         |                   |         | 1
// |         |                   |         |
// |         |                   |         |
// |         |                   |         |
// |         |                   |         |
// |         +-------------------+         | :
// |         |                   |         |
// |         |     ctrl panel    |         | 0
// |         |                   |         |
// +---------+-------------------+---------+

wxSize wxBoardFrame::MIN_SIZE(1280, 720);
wxColour wxBoardFrame::BG_COLOR(0x43, 0x43, 0x43);

wxBoardFrame::wxBoardFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxBoardFrame::MIN_SIZE)
{
    // 아이콘
    static wxIcon icon(wxICON(scoreboard));
    SetIcon(icon);

    // 파일 메뉴
    wxMenu *game = new wxMenu;
    game->Append(new wxMenuItem(game, ID_NEW_GAME, wxT("New &Game\tCtrl+G")));
    game->Append(new wxMenuItem(game, ID_NEW_PERIOD,
                                wxT("New &Period\tCtrl+P")));
    game->AppendSeparator();
    game->Append(new wxMenuItem(game, wxID_SETUP, wxT("&Options...")));
    game->AppendSeparator();
    game->Append(new wxMenuItem(game, wxID_EXIT, wxT("&Quit\tCtrl+W")));

    // 도움말 메뉴
    wxMenu *help = new wxMenu;
    help->Append(wxID_ABOUT);

    // 메뉴 생성
    wxMenuBar *menubar = new wxMenuBar;
    menubar->Append(game, wxT("&Game"));
    menubar->Append(help, wxT("&Help"));
    SetMenuBar(menubar);

    // 백그라운드 패널과 박스 생성
    wxPanel *bgPan = new wxPanel(this, wxID_ANY);
    wxBoxSizer *bgBox = new wxBoxSizer(wxHORIZONTAL);

    // 팀 정보 패널 생성
    m_leftPan = new wxLeftTeamPanel(bgPan, wxT("Home"));
    m_rightPan = new wxRightTeamPanel(bgPan, wxT("Visitor"));

    // 게임 정보 패널과 제어 패널 생성
    wxBoxSizer *midBox = new wxBoxSizer(wxVERTICAL);
    m_gamePan = new wxGamePanel(bgPan);
    CtrlPanel *ctrlPan = new CtrlPanel(bgPan);

    // 게임 정보 패널과 제어 패널 배치
    midBox->Add(m_gamePan, 2, wxEXPAND | wxTOP, 10);
    midBox->Add(-1, 10);
    midBox->Add(ctrlPan, 1, wxEXPAND | wxBOTTOM, 10);

    // 팀 정보와 게임 정보 패널 배치
    bgBox->Add(m_leftPan, 1, wxEXPAND | wxTOP | wxBOTTOM | wxLEFT, 10);
    bgBox->Add(10, -1);
    bgBox->Add(midBox, 2, wxEXPAND);
    bgBox->Add(10, -1);
    bgBox->Add(m_rightPan, 1, wxEXPAND | wxTOP | wxBOTTOM | wxRIGHT, 10);

    bgPan->SetSizer(bgBox);

    // 배경색 지정
    SetBackgroundColour(BG_COLOR);

    // Accelerator table
    wxAcceleratorEntry entries[6];
    entries[0].Set(wxACCEL_NORMAL, WXK_SPACE, ID_TOGGLE_TIME);
    entries[1].Set(wxACCEL_NORMAL, WXK_RETURN, ID_TOGGLE_SHOT_CLOCK);
    entries[2].Set(wxACCEL_CTRL, WXK_LEFT, ID_INC_LEFT_SCORE);
    entries[3].Set(wxACCEL_CTRL, WXK_RIGHT, ID_INC_RIGHT_SCORE);
    entries[4].Set(wxACCEL_ALT, WXK_LEFT, ID_INC_LEFT_FOUL);
    entries[5].Set(wxACCEL_ALT, WXK_RIGHT, ID_INC_RIGHT_FOUL);
    wxAcceleratorTable accel(N_ELEMENTS(entries), entries);
    SetAcceleratorTable(accel);

    // 이벤트 연결
    Connect(ID_NEW_GAME, wxEVT_COMMAND_MENU_SELECTED, 
            wxCommandEventHandler(wxBoardFrame::OnNewGame));
    Connect(ID_NEW_PERIOD, wxEVT_COMMAND_MENU_SELECTED, 
            wxCommandEventHandler(wxBoardFrame::OnNewPeriod));
    Connect(wxID_SETUP, wxEVT_COMMAND_MENU_SELECTED, 
            wxCommandEventHandler(wxBoardFrame::OnSetup));
    Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(wxBoardFrame::OnQuit));
    Connect(wxID_ABOUT, wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(wxBoardFrame::OnAbout));

    Connect(ID_NEW_GAME, wxEVT_COMMAND_BUTTON_CLICKED, 
            wxCommandEventHandler(wxBoardFrame::OnNewGame));
    Connect(ID_TOGGLE_TIME, wxEVT_COMMAND_MENU_SELECTED, 
            wxCommandEventHandler(wxBoardFrame::OnToggleTime));
    Connect(ID_START_TIME, wxEVT_COMMAND_BUTTON_CLICKED, 
            wxCommandEventHandler(wxBoardFrame::OnStartTime));
    Connect(ID_STOP_TIME, wxEVT_COMMAND_BUTTON_CLICKED, 
            wxCommandEventHandler(wxBoardFrame::OnStopTime));

    Connect(ID_TOGGLE_SHOT_CLOCK, wxEVT_COMMAND_MENU_SELECTED, 
            wxCommandEventHandler(wxBoardFrame::OnToggleShotClock));
    Connect(ID_START_SHOT_CLOCK, wxEVT_COMMAND_BUTTON_CLICKED, 
            wxCommandEventHandler(wxBoardFrame::OnStartShotClock));
    Connect(ID_RESET_SHOT_CLOCK, wxEVT_COMMAND_BUTTON_CLICKED, 
            wxCommandEventHandler(wxBoardFrame::OnResetShotClock));

    Connect(ID_INC_LEFT_SCORE, wxEVT_COMMAND_BUTTON_CLICKED, 
            wxCommandEventHandler(wxBoardFrame::OnIncLeftScore));
    Connect(ID_DEC_LEFT_SCORE, wxEVT_COMMAND_BUTTON_CLICKED, 
            wxCommandEventHandler(wxBoardFrame::OnDecLeftScore));

    Connect(ID_INC_RIGHT_SCORE, wxEVT_COMMAND_BUTTON_CLICKED, 
            wxCommandEventHandler(wxBoardFrame::OnIncRightScore));
    Connect(ID_DEC_RIGHT_SCORE, wxEVT_COMMAND_BUTTON_CLICKED, 
            wxCommandEventHandler(wxBoardFrame::OnDecRightScore));

    Connect(ID_INC_LEFT_FOUL, wxEVT_COMMAND_BUTTON_CLICKED, 
            wxCommandEventHandler(wxBoardFrame::OnIncLeftFoul));
    Connect(ID_DEC_LEFT_FOUL, wxEVT_COMMAND_BUTTON_CLICKED, 
            wxCommandEventHandler(wxBoardFrame::OnDecLeftFoul));

    Connect(ID_INC_RIGHT_FOUL, wxEVT_COMMAND_BUTTON_CLICKED, 
            wxCommandEventHandler(wxBoardFrame::OnIncRightFoul));
    Connect(ID_DEC_RIGHT_FOUL, wxEVT_COMMAND_BUTTON_CLICKED, 
            wxCommandEventHandler(wxBoardFrame::OnDecRightFoul));

    Connect(ID_NEW_PERIOD, wxEVT_COMMAND_BUTTON_CLICKED, 
            wxCommandEventHandler(wxBoardFrame::OnNewPeriod));
    Connect(ID_INC_PERIOD, wxEVT_COMMAND_BUTTON_CLICKED, 
            wxCommandEventHandler(wxBoardFrame::OnIncPeriod));
    Connect(ID_DEC_PERIOD, wxEVT_COMMAND_BUTTON_CLICKED, 
            wxCommandEventHandler(wxBoardFrame::OnDecPeriod));
}

#if defined(__WXGTK__)
// wxGTK의 자식 패널에 배경색이 상속이 되지 않는 버그가 있다.
// (관련 링크: http://trac.wxwidgets.org/ticket/10751)
// 이 버그가 수정될 때까지는, 자식 패널을 재귀적으로 구해서
// 패널의 배경색을 변경한다.
static
void
SetBackgroundColour(wxWindow *wnd, const wxColour& colour)
{
    wxWindowList & children = wnd->GetChildren();
    for (wxWindowList::Node *node = children.GetFirst(); node;
         node = node->GetNext()) {
        wxWindow *curr = (wxWindow *)node->GetData();
        if (curr->IsKindOf(CLASSINFO(wxPanel))) {
            curr->SetBackgroundColour(colour);
            ::SetBackgroundColour(curr, colour);
        }
    }
}
#endif

bool
wxBoardFrame::SetBackgroundColour(const wxColour& colour)
{
#if defined(__WXGTK__)
    ::SetBackgroundColour(this, colour);
#endif
    return wxFrame::SetBackgroundColour(colour);
}

void
wxBoardFrame::OnQuit(wxCommandEvent& WXUNUSED(evt))
{
    Close(true);
}

void
wxBoardFrame::OnAbout(wxCommandEvent& WXUNUSED(evt))
{
    wxAboutDialogInfo info;
    info.SetName(wxT(PACKAGE_NAME));
    info.SetVersion(wxT(PACKAGE_VERSION));
    info.SetDescription(wxT("Simple scoreboard application"));
    info.SetCopyright(wxT("Copyright (C) 2012 Daniel Jun"));
    info.SetWebSite(wxT(PACKAGE_URL));
    info.AddDeveloper(wxT("Daniel Jun"));

    ::wxAboutBox(info);
}

void
wxBoardFrame::OnSetup(wxCommandEvent& WXUNUSED(evt))
{
    m_gamePan->StopTime(); 
    static wxConfigDialog *configDlg
        = new wxConfigDialog(this, wxT("Option"));
    if (configDlg->ShowModal() == wxID_OK) {
        m_gamePan->InitTime();
    }
}

void
wxBoardFrame::OnNewGame(wxCommandEvent& WXUNUSED(evt))
{
    m_gamePan->ResetTime();
    m_gamePan->ResetPeriod();

    m_leftPan->ResetScore();
    m_leftPan->ResetFoul();

    m_rightPan->ResetScore();
    m_rightPan->ResetFoul();
}

void
wxBoardFrame::OnToggleTime(wxCommandEvent& WXUNUSED(evt))
{
    if (m_gamePan->IsStarted()) {
        m_gamePan->StopTime();
    }
    else {
        m_gamePan->StartTime();
    }
}

void
wxBoardFrame::OnStartTime(wxCommandEvent& WXUNUSED(evt))
{
    m_gamePan->StartTime();
}

void
wxBoardFrame::OnStopTime(wxCommandEvent& WXUNUSED(evt))
{
    m_gamePan->StopTime();
}

void
wxBoardFrame::OnToggleShotClock(wxCommandEvent& WXUNUSED(evt))
{
    if (m_gamePan->IsPlaying()) {
        m_gamePan->ResetShotClock();
    }
    else {
        m_gamePan->StartShotClock();
    }
}

void
wxBoardFrame::OnStartShotClock(wxCommandEvent& WXUNUSED(evt))
{
    m_gamePan->StartShotClock();
}

void
wxBoardFrame::OnResetShotClock(wxCommandEvent& WXUNUSED(evt))
{
    m_gamePan->ResetShotClock();
}

void
wxBoardFrame::OnIncLeftScore(wxCommandEvent& WXUNUSED(evt))
{
    m_leftPan->IncScore();
}

void
wxBoardFrame::OnDecLeftScore(wxCommandEvent& WXUNUSED(evt))
{
    m_leftPan->DecScore();
}

void
wxBoardFrame::OnIncRightScore(wxCommandEvent& WXUNUSED(evt))
{
    m_rightPan->IncScore();
}

void
wxBoardFrame::OnDecRightScore(wxCommandEvent& WXUNUSED(evt))
{
    m_rightPan->DecScore();
}

void
wxBoardFrame::OnIncLeftFoul(wxCommandEvent& WXUNUSED(evt))
{
    m_leftPan->IncFoul();
}

void
wxBoardFrame::OnDecLeftFoul(wxCommandEvent& WXUNUSED(evt))
{
    m_leftPan->DecFoul();
}

void
wxBoardFrame::OnIncRightFoul(wxCommandEvent& WXUNUSED(evt))
{
    m_rightPan->IncFoul();
}

void
wxBoardFrame::OnDecRightFoul(wxCommandEvent& WXUNUSED(evt))
{
    m_rightPan->DecFoul();
}

void
wxBoardFrame::OnNewPeriod(wxCommandEvent& WXUNUSED(evt))
{
    m_gamePan->ResetTime();
    m_gamePan->IncPeriod();

    m_leftPan->ResetFoul();
    m_rightPan->ResetFoul();
}

void
wxBoardFrame::OnIncPeriod(wxCommandEvent& WXUNUSED(evt))
{
    m_gamePan->IncPeriod();
}

void
wxBoardFrame::OnDecPeriod(wxCommandEvent& WXUNUSED(evt))
{
    m_gamePan->DecPeriod();
}
