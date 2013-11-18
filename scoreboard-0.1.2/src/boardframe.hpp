#ifndef __BOARDFRAME_H__
#define __BOARDFRAME_H__

#include "common.hpp"

class wxBoardFrame : public wxFrame
{
public:
    static wxSize MIN_SIZE;
    static wxColour BG_COLOR;

public:
    wxBoardFrame(const wxString& title);

    bool SetBackgroundColour(const wxColour& colour);

private:
    void OnQuit(wxCommandEvent& evt);
    void OnAbout(wxCommandEvent& evt);
    void OnSetup(wxCommandEvent& evt);

    void OnNewGame(wxCommandEvent& evt);
    void OnToggleTime(wxCommandEvent& evt);
    void OnStartTime(wxCommandEvent& evt);
    void OnStopTime(wxCommandEvent& evt);
    void OnToggleShotClock(wxCommandEvent& evt);
    void OnStartShotClock(wxCommandEvent& evt);
    void OnResetShotClock(wxCommandEvent& evt);

    void OnIncLeftScore(wxCommandEvent& evt);
    void OnDecLeftScore(wxCommandEvent& evt);

    void OnIncRightScore(wxCommandEvent& evt);
    void OnDecRightScore(wxCommandEvent& evt);

    void OnIncLeftFoul(wxCommandEvent& evt);
    void OnDecLeftFoul(wxCommandEvent& evt);

    void OnIncRightFoul(wxCommandEvent& evt);
    void OnDecRightFoul(wxCommandEvent& evt);

    void OnNewPeriod(wxCommandEvent& evt);
    void OnIncPeriod(wxCommandEvent& evt);
    void OnDecPeriod(wxCommandEvent& evt);

private:
    wxGamePanel* m_gamePan;

    wxTeamPanel* m_leftPan;
    wxTeamPanel* m_rightPan;
};

#endif  // __BOARDFRAME_H__
