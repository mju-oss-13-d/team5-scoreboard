#include "ctrlpanel.hpp"
#include "gamepanel.hpp"

// +--------------+--------------+--------------+--------------+
// |              |              |              |              |
// |    Score     |     Time     |              |    Score     |
// |              |              |              |              |
// +--------------+--------------+--------------+--------------+
// |              |              |              |              |
// |    Fouls     |  Shot Clock  |    Period    |    Fouls     |
// |              |              |              |              |
// +--------------+--------------+--------------+--------------+

CtrlPanel::CtrlPanel(wxWindow* parent)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize,
              wxTAB_TRAVERSAL | wxBORDER_RAISED)
{
    wxGridSizer *bgGrid = new wxGridSizer(2, 4, 10, 10);

    // (0, 0)
    wxStaticBoxSizer *lScoreBox = new wxStaticBoxSizer(wxVERTICAL, this,
                                                       wxT("Score"));
    lScoreBox->Add(new wxButton(this, ID_INC_LEFT_SCORE, wxT("+")), 0,
                   wxALIGN_CENTER);
    lScoreBox->Add(new wxButton(this, ID_DEC_LEFT_SCORE, wxT("-")), 0,
                   wxALIGN_CENTER);
    bgGrid->Add(lScoreBox, 1, wxEXPAND | wxALIGN_TOP | wxALIGN_CENTER);

    // (1, 0)
    wxStaticBoxSizer *timeBox = new wxStaticBoxSizer(wxVERTICAL, this,
                                                     wxT("Game"));
    timeBox->Add(new wxButton(this, ID_NEW_GAME, wxT("New")), 0,
                 wxALIGN_CENTER);
    timeBox->Add(new wxButton(this, ID_START_TIME, wxT("Start")), 0,
                 wxALIGN_CENTER);
    timeBox->Add(new wxButton(this, ID_STOP_TIME, wxT("Stop")), 0,
                 wxALIGN_CENTER);
    bgGrid->Add(timeBox, 1, wxEXPAND | wxALIGN_TOP | wxALIGN_CENTER);

    // (2, 0)
    bgGrid->Add(new wxStaticText(this, wxID_ANY, wxT("")),
                1, wxEXPAND | wxALIGN_TOP | wxALIGN_CENTER);

    // (3, 0)
    wxStaticBoxSizer *rScoreBox = new wxStaticBoxSizer(wxVERTICAL, this,
                                                       wxT("Score"));
    rScoreBox->Add(new wxButton(this, ID_INC_RIGHT_SCORE, wxT("+")), 0,
                   wxALIGN_CENTER);
    rScoreBox->Add(new wxButton(this, ID_DEC_RIGHT_SCORE, wxT("-")), 0,
                   wxALIGN_CENTER);
    bgGrid->Add(rScoreBox, 1, wxEXPAND | wxALIGN_TOP | wxALIGN_CENTER);

    // (0, 1)
    wxStaticBoxSizer *lFoulBox = new wxStaticBoxSizer(wxVERTICAL, this,
                                                      wxT("Fouls"));
    lFoulBox->Add(new wxButton(this, ID_INC_LEFT_FOUL, wxT("+")), 0,
                  wxALIGN_CENTER);
    lFoulBox->Add(new wxButton(this, ID_DEC_LEFT_FOUL, wxT("-")), 0,
                  wxALIGN_CENTER);
    bgGrid->Add(lFoulBox, 1, wxEXPAND | wxALIGN_TOP | wxALIGN_CENTER);

    // (1, 1)
    wxStaticBoxSizer *shotClockBox = new wxStaticBoxSizer(wxVERTICAL, this,
                                                          wxT("Shot Clock"));
    shotClockBox->Add(new wxButton(this, ID_START_SHOT_CLOCK, wxT("Start")),
                      0, wxALIGN_CENTER);
    shotClockBox->Add(new wxButton(this, ID_RESET_SHOT_CLOCK, wxT("Reset")),
                      0, wxALIGN_CENTER);
    bgGrid->Add(shotClockBox, 1, wxEXPAND | wxALIGN_TOP | wxALIGN_CENTER);

    // (2, 1)
    wxStaticBoxSizer *periBox = new wxStaticBoxSizer(wxVERTICAL, this,
                                                     wxT("Period"));
    periBox->Add(new wxButton(this, ID_NEW_PERIOD, wxT("New")), 0,
                 wxALIGN_CENTER);
    periBox->Add(new wxButton(this, ID_INC_PERIOD, wxT("+")), 0,
                 wxALIGN_CENTER);
    periBox->Add(new wxButton(this, ID_DEC_PERIOD, wxT("-")), 0,
                 wxALIGN_CENTER);
    bgGrid->Add(periBox, 1, wxEXPAND | wxALIGN_TOP | wxALIGN_CENTER);

    // (3, 1)
    wxStaticBoxSizer *rFoulBox = new wxStaticBoxSizer(wxVERTICAL, this,
                                                      wxT("Fouls"));
    rFoulBox->Add(new wxButton(this, ID_INC_RIGHT_FOUL, wxT("+")), 0,
                  wxALIGN_CENTER);
    rFoulBox->Add(new wxButton(this, ID_DEC_RIGHT_FOUL, wxT("-")), 0,
                  wxALIGN_CENTER);
    bgGrid->Add(rFoulBox, 1, wxEXPAND | wxALIGN_TOP | wxALIGN_CENTER);

    SetSizer(bgGrid);
}
