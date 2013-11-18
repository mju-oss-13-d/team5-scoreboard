#include "common.hpp"

class wxConfigDialog : public wxDialog
{
public:
    wxConfigDialog(wxWindow *parent, const wxString& title);

    int ShowModal();

private:
    void OnOK(wxCommandEvent& evt);
    void OnCancel(wxCommandEvent& evt);
    void OnPeriodLengthText(wxCommandEvent& evt);
    void OnShotClockText(wxCommandEvent& evt);

    void UpdateNumberText(wxTextCtrl* textCtrl);

private:
    wxTextCtrl* m_periLenText;
    wxString m_oldPeriLen;

    wxTextCtrl* m_shotClockText;
    wxString m_oldShotClock;
};
