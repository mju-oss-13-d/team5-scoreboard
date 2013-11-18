#include "confdlg.hpp"
#include "config.hpp"

wxConfigDialog::wxConfigDialog(wxWindow *parent, const wxString& title)
    : wxDialog(parent, wxID_ANY, title, wxDefaultPosition, wxSize(240, 150),
               wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)
{
    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);

    // 설정 패널
    wxPanel *panel = new wxPanel(this, wxID_ANY);
    wxFlexGridSizer *grid = new wxFlexGridSizer(2, 2, 4, 4);
    grid->Add(new wxStaticText(panel, wxID_ANY, wxT("Period Length (min)")),
              0, wxALIGN_RIGHT);
    m_periLenText = new wxTextCtrl(panel, ID_PERIOD_LENGTH_TEXT, wxT(""),
                                   wxDefaultPosition, wxDefaultSize);
    m_periLenText->SetMaxLength(2); // 0 ~ 99
    grid->Add(m_periLenText, 1, wxEXPAND);
    grid->Add(new wxStaticText(panel, wxID_ANY, wxT("Shot Clock (sec)")),
              0, wxALIGN_RIGHT);
    m_shotClockText = new wxTextCtrl(panel, ID_SHOT_CLOCK_TEXT, wxT(""),
                                wxDefaultPosition, wxDefaultSize);
    m_shotClockText->SetMaxLength(2); // 0 ~ 99
    grid->Add(m_shotClockText, 1, wxEXPAND);
    grid->AddGrowableCol(1, 1);
    panel->SetSizer(grid);

    vbox->Add(panel, 1, wxEXPAND | wxTOP | wxLEFT | wxRIGHT, 10);

    // 다이얼로그 버튼
    wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
    hbox->Add(new wxButton(this, wxID_OK, wxT("OK"), 
                           wxDefaultPosition, wxSize(70, 30)), 1);
    hbox->Add(new wxButton(this, wxID_CANCEL, wxT("Close"), 
                           wxDefaultPosition, wxSize(70, 30)), 1, wxLEFT, 5);

    vbox->Add(hbox, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);

    SetSizer(vbox);

    // 이벤트 연결
    Connect(wxID_OK, wxEVT_COMMAND_BUTTON_CLICKED, 
            wxCommandEventHandler(wxConfigDialog::OnOK));
    Connect(wxID_CANCEL, wxEVT_COMMAND_BUTTON_CLICKED, 
            wxCommandEventHandler(wxConfigDialog::OnCancel));

    Connect(ID_PERIOD_LENGTH_TEXT, wxEVT_COMMAND_TEXT_UPDATED, 
            wxCommandEventHandler(wxConfigDialog::OnPeriodLengthText));
    Connect(ID_SHOT_CLOCK_TEXT, wxEVT_COMMAND_TEXT_UPDATED, 
            wxCommandEventHandler(wxConfigDialog::OnShotClockText));
}

int
wxConfigDialog::ShowModal()
{
    m_oldPeriLen.Empty();
    m_oldShotClock.Empty();

    m_oldPeriLen << Config::Instance().GetPeriodLength();
    m_oldShotClock << Config::Instance().GetShotClock();

    m_periLenText->SetValue(m_oldPeriLen);
    m_shotClockText->SetValue(m_oldShotClock);

    return wxDialog::ShowModal();
}

void
wxConfigDialog::OnOK(wxCommandEvent& evt)
{
    int periLen = wxAtoi(m_periLenText->GetValue());
    if (! Config::IsValidPeriodLength(periLen)) {
        wxMessageDialog *dlg
            = new wxMessageDialog(NULL, 
                                  wxT("Invalid Peroid Length"), 
                                  wxT("Error"),
                                  wxOK | wxICON_ERROR);
        dlg->ShowModal();

        m_periLenText->SetValue(m_oldPeriLen);
        m_periLenText->SetFocus();
        return;
    }
    int shotClock = wxAtoi(m_shotClockText->GetValue());
    if (! Config::IsValidShotClock(shotClock)) {
        wxMessageDialog *dlg
            = new wxMessageDialog(NULL, 
                                  wxT("Invalid Shot Clock"), 
                                  wxT("Error"),
                                  wxOK | wxICON_ERROR);
        dlg->ShowModal();

        m_shotClockText->SetValue(m_oldShotClock);
        m_shotClockText->SetFocus();
        return;
    }

    Config::Instance().SetPeriodLength(periLen);
    Config::Instance().SetShotClock(shotClock);

    EndModal(wxID_OK);
}

void
wxConfigDialog::OnCancel(wxCommandEvent& evt)
{
    EndModal(wxID_CANCEL);
}

void
wxConfigDialog::UpdateNumberText(wxTextCtrl* textCtrl)
{
    if (!textCtrl->IsModified())
        return;

    wxString val = textCtrl->GetValue();
    if (! val.IsNumber()) {
        long insPnt = textCtrl->GetInsertionPoint();
        textCtrl->Remove(insPnt - 1, insPnt);
    }
}

void
wxConfigDialog::OnPeriodLengthText(wxCommandEvent& evt)
{
    UpdateNumberText(m_periLenText);
}

void
wxConfigDialog::OnShotClockText(wxCommandEvent& evt)
{
    UpdateNumberText(m_shotClockText);
}
