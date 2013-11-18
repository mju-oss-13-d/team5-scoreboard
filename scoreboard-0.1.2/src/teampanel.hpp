#ifndef __TEAMPANEL_H__
#define __TEAMPANEL_H__

#include "common.hpp"

class wxTeamPanel : public wxPanel
{
public:
    wxTeamPanel(wxWindow* parent, const wxString& name);

    void IncScore();
    void DecScore();
    void ResetScore();

    void IncFoul();
    void DecFoul();
    void ResetFoul();

protected:
    void Init();
    void UpdateScore();
    void UpdateFoul();

protected:
    wxSizer *m_sizer;

    wxLCDWindow *m_scoreCtrl;
    int m_score;

    wxLCDWindow *m_foulCtrl;
    int m_foul;
};

class wxLeftTeamPanel : public wxTeamPanel
{
public:
    wxLeftTeamPanel(wxWindow* parent, const wxString& name);
};

class wxRightTeamPanel : public wxTeamPanel
{
public:
    wxRightTeamPanel(wxWindow* parent, const wxString& name);
};

#endif  // __TEAMPANEL_H__
