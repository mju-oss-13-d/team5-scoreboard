#ifndef __STATICTITLE_H__
#define __STATICTITLE_H__

#include <wx/wx.h>
 
class wxStaticTitle : public wxPanel
{
private:
    wxString m_title;

public:
    wxStaticTitle(wxWindow* parent, wxString title);

    void Paint();
    void Render(wxDC& dc);

    void OnPaint(wxPaintEvent& evt);
    void OnSize(wxSizeEvent& event);
};
 
#endif  // __STATICTITLE_H__
