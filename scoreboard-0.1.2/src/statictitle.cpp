#include "statictitle.hpp"

wxStaticTitle::wxStaticTitle(wxWindow* parent, wxString title)
    : wxPanel(parent)
    , m_title(title)
{
    Connect(wxEVT_PAINT, wxPaintEventHandler(wxStaticTitle::OnPaint));
    Connect(wxEVT_SIZE, wxSizeEventHandler(wxStaticTitle::OnSize));
}
 
/*
 * Called by the system of by wxWidgets when the panel needs
 * to be redrawn. You can also trigger this call by
 * calling Refresh()/Update().
 */
 
void
wxStaticTitle::OnPaint(wxPaintEvent& evt)
{
    // depending on your system you may need to look at double-buffered dcs
    wxPaintDC dc(this);
    Render(dc);
}
 
/*
 * Alternatively, you can use a clientDC to paint on the panel
 * at any time. Using this generally does not free you from
 * catching paint events, since it is possible that e.g. the window
 * manager throws away your drawing when the window comes to the
 * background, and expects you will redraw it when the window comes
 * back (by sending a paint event).
 */
void
wxStaticTitle::Paint()
{
    // depending on your system you may need to look at double-buffered dcs
    wxClientDC dc(this);
    Render(dc);
}
 
/*
 * Here we do the actual rendering. I put it in a separate
 * method so that it can work no matter what type of DC
 * (e.g. wxPaintDC or wxClientDC) is used.
 */
void
wxStaticTitle::Render(wxDC& dc)
{
    // Set font, background mode for drawing text, and text color
    wxFont font(dc.GetFont());
    font.SetPointSize(30);
    dc.SetFont(font);
    dc.SetBackgroundMode(wxTRANSPARENT);
    dc.SetTextForeground(*wxWHITE);

    // Get window and text dimensions
    wxSize sz = GetClientSize();
    wxCoord w, h;
    dc.GetTextExtent(m_title, &w, &h);

    // Center the text on the window, but never draw at a negative position.
    int x = wxMax(0, (sz.x - w)/2);
    int y = wxMax(0, (sz.y - h)/2);

    dc.DrawText(m_title, x, y);
}
 
/*
 * Here we call refresh to tell the panel to draw itself again.
 * So when the user resizes the image panel the image should be resized too.
 */
void
wxStaticTitle::OnSize(wxSizeEvent& event){
    Refresh();
    //skip the event.
    event.Skip();
}
