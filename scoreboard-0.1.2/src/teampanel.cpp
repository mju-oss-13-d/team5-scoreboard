#include "teampanel.hpp"
#include "lcdwindow.hpp"
#include "statictitle.hpp"

// +--------------------+
// |                    |
// |       Home         |
// |                    |
// | +----------------+ |
// | | +--+ +--+ +--+ | |
// | | |  | |  | |  | | |
// | | +--+ +--+ +--+ | |
// | | |  | |  | |  | | |
// | | +--+ +--+ +--+ | |
// | +----------------+ |
// |                    |
// |  fouls             |
// | +-----------+      |
// | | +--+ +--+ |      |
// | | |  | |  | |      |
// | | +--+ +--+ |      |
// | | |  | |  | |      |
// | | +--+ +--+ |      |
// | +-----------+      |
// +--------------------+
// 

wxTeamPanel::wxTeamPanel(wxWindow* parent, const wxString& name)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize,
              wxBORDER_RAISED, name)
{
    m_sizer = new wxBoxSizer(wxVERTICAL);

    // 팀이름 추가
    m_sizer->Add(new wxStaticTitle(this, name),
               1, wxEXPAND | wxTOP | wxLEFT | wxRIGHT, 10);

    m_sizer->Add(-1, 10);

    // 점수 추가
    m_scoreCtrl = new wxLCDWindow(this, wxDefaultPosition, wxDefaultSize);
    m_scoreCtrl->SetNumberDigits(3);
    m_sizer->Add(m_scoreCtrl, 3, wxEXPAND | wxLEFT | wxRIGHT, 10);

    SetSizer(m_sizer);
}

void
wxTeamPanel::Init()
{
    ResetScore();
    ResetFoul();
}

void
wxTeamPanel::IncScore()
{
    m_score = (++m_score > 999) ? 999 : m_score;
    UpdateScore();
}

void
wxTeamPanel::DecScore()
{
    m_score = (--m_score < 0) ? 0 : m_score;
    UpdateScore();
}

void
wxTeamPanel::ResetScore()
{
    m_score = 0;
    UpdateScore();
}

void
wxTeamPanel::UpdateScore()
{
    wxString str;
    str << m_score;
    m_scoreCtrl->SetValue(str);
}

void
wxTeamPanel::IncFoul()
{
    m_foul = (++m_foul > 99) ? 99 : m_foul;
    UpdateFoul();
}

void
wxTeamPanel::DecFoul()
{
    m_foul = (--m_foul < 0) ? 0 : m_foul;
    UpdateFoul();
}

void
wxTeamPanel::ResetFoul()
{
    m_foul = 0;
    UpdateFoul();
}

void
wxTeamPanel::UpdateFoul()
{
    wxString str;
    str << m_foul;
    m_foulCtrl->SetValue(str);
}

wxLeftTeamPanel::wxLeftTeamPanel(wxWindow* parent, const wxString& name)
    : wxTeamPanel(parent, name)
{

    m_sizer->Add(-1, 10);

    // 파울수(와 기타) 추가
    wxFlexGridSizer *etcGrid = new wxFlexGridSizer(2, 2, 10, 10);
    etcGrid->Add(new wxStaticTitle(this, wxT("Fouls")), 1, wxEXPAND);
    etcGrid->Add(new wxStaticText(this, wxID_ANY, wxT("")), 1, wxEXPAND);
    m_foulCtrl = new wxLCDWindow(this, wxDefaultPosition, wxDefaultSize);
    m_foulCtrl->SetNumberDigits(2);
    etcGrid->Add(m_foulCtrl, 1, wxEXPAND);
    etcGrid->Add(new wxStaticText(this, wxID_ANY, wxT("")), 1, wxEXPAND);
    etcGrid->AddGrowableCol(0, 1);
    etcGrid->AddGrowableCol(1, 1);
    etcGrid->AddGrowableRow(0, 1);
    etcGrid->AddGrowableRow(1, 2);
    m_sizer->Add(etcGrid, 3, wxEXPAND | wxBOTTOM | wxLEFT | wxRIGHT, 10);

    Init();
}

wxRightTeamPanel::wxRightTeamPanel(wxWindow* parent, const wxString& name)
    : wxTeamPanel(parent, name)
{
    m_sizer->Add(-1, 10);

    // 파울수(와 기타) 추가
    wxFlexGridSizer *etcGrid = new wxFlexGridSizer(2, 2, 10, 10);
    etcGrid->Add(new wxStaticText(this, wxID_ANY, wxT("")), 1, wxEXPAND);
    etcGrid->Add(new wxStaticTitle(this, wxT("Fouls")), 1, wxEXPAND);
    m_foulCtrl = new wxLCDWindow(this, wxDefaultPosition, wxDefaultSize);
    m_foulCtrl->SetNumberDigits(2);
    etcGrid->Add(new wxStaticText(this, wxID_ANY, wxT("")), 1, wxEXPAND);
    etcGrid->Add(m_foulCtrl, 1, wxEXPAND);
    etcGrid->AddGrowableCol(0, 1);
    etcGrid->AddGrowableCol(1, 1);
    etcGrid->AddGrowableRow(0, 1);
    etcGrid->AddGrowableRow(1, 2);
    m_sizer->Add(etcGrid, 3, wxEXPAND | wxBOTTOM | wxLEFT | wxRIGHT, 10);

    Init();
}
