#include "config.hpp"
#include "gamepanel.hpp"
#include "lcdwindow.hpp"
#include "statictitle.hpp"
#include <SDL.h>

//     1     :    1     :      1
// +---------------------------------+
// | +-----------------------------+ |
// | |    +--+ +--+   +--+ +--+    | |
// | |    |  | |  | o |  | |  |    | |
// | |    +--+ +--+   +--+ +--+    | | 3
// | |    |  | |  | o |  | |  |    | |
// | |    +--+ +--+   +--+ +--+    | |
// | +-----------------------------+ | :
// |                                 |
// |  shot clock             period  | 1
// | +-----------+          +------+ |
// | | +--+ +--+ |     \    | +--+ | | :
// | | |  | |  | |   ---\   | |  | | |
// | | +--+ +--+ |   ---/   | +--+ | |
// | | |  | |  | |     /    | |  | | | 2
// | | +--+ +--+ |          | +--+ | |
// | +-----------+          +------+ |
// +---------------------------------+
// 
wxGamePanel::wxGamePanel(wxWindow* parent)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize,
              wxBORDER_RAISED)
    , m_timer(this, ID_CLOCK_TIMER)
    , m_playing(false)
    , m_buzzerTimer(this, ID_BUZZER_TIMER)
    , m_buzzing(false)
{
    wxBoxSizer *bgBox = new wxBoxSizer(wxVERTICAL);

    // 게임 시간 추가
    m_timeCtrl = new wxLCDWindow(this, wxDefaultPosition, wxDefaultSize);
    m_timeCtrl->SetNumberDigits(5);
    m_timeCtrl->SetValue(wxT("12:25"));
    bgBox->Add(m_timeCtrl, 3, wxEXPAND | wxTOP | wxLEFT | wxRIGHT, 10);

    bgBox->Add(-1, 10);

    // 슛클락, 공격방향, 페리오드 추가
    wxFlexGridSizer *etcGrid = new wxFlexGridSizer(2, 3, 10, 10);
    etcGrid->Add(new wxStaticTitle(this, wxT("Shot Clock")), 1, wxEXPAND);
    etcGrid->Add(new wxStaticText(this, -1, wxT("")), 1, wxEXPAND);
    etcGrid->Add(new wxStaticTitle(this, wxT("Period")), 1, wxEXPAND);
    m_shotClockCtrl = new wxLCDWindow(this, wxDefaultPosition, wxDefaultSize);
    m_shotClockCtrl->SetNumberDigits(2);
    wxStaticText *attackDir = new wxStaticText(this, wxID_ANY, wxT(""));
    m_periodCtrl = new wxLCDWindow(this, wxDefaultPosition, wxDefaultSize);
    m_periodCtrl->SetNumberDigits(1);
    etcGrid->Add(m_shotClockCtrl, 1, wxEXPAND);
    etcGrid->Add(attackDir, 1, wxEXPAND);
    etcGrid->Add(m_periodCtrl, 1, wxEXPAND);
    etcGrid->AddGrowableCol(0, 1);
    etcGrid->AddGrowableCol(1, 1);
    etcGrid->AddGrowableCol(2, 1);
    etcGrid->AddGrowableRow(0, 1);
    etcGrid->AddGrowableRow(1, 2);
    bgBox->Add(etcGrid, 3, wxEXPAND | wxBOTTOM | wxLEFT | wxRIGHT, 10);

    SetSizer(bgBox);

    // 이벤트 연결
    Connect(ID_CLOCK_TIMER, wxEVT_TIMER,
            wxTimerEventHandler(wxGamePanel::OnTimer));
    Connect(ID_BUZZER_TIMER, wxEVT_TIMER,
            wxTimerEventHandler(wxGamePanel::OnBuzzerTimer));

    InitTime();
    ResetPeriod();
}

void
wxGamePanel::OnTimer(wxTimerEvent& event)
{
    UpdateTime();
}

/* Buffer fill-upper */
static
void
CreateTone(void *userdata, Uint8 *stream, int len)
{
    static double angle = 0.0 ;
    int i = 0 ;
    fprintf( stderr, "Filling %d\n", len ) ;
    for(i=0;i<len;i++) {
        *stream++ = 255*cos(angle) ; // I think that this should be
                                     // 128 * cos(angle) as cos is (-1,1)
        angle += 3.14159/100 ;       // and a Uint8 is only 8 bits (256 values)
        if( angle > 2.0*3.14159 ) {
            angle -= 2.0*3.14159 ;
        }
    }
}

/* Open the audio device to what we want */
void
wxGamePanel::StartBuzzer()
{
    if (! m_buzzing) {
        SDL_AudioSpec as;

        /* Fill out what we want */
        as.freq = 44100;
        as.format = AUDIO_S16SYS;
        as.channels = 2;
        as.samples = 1024;
        as.callback = CreateTone;

        /* Get it */
        SDL_OpenAudio(&as, NULL);
 
        /* Go! */
        SDL_PauseAudio(0);

        m_buzzerTimer.Start(1000, true); // 1 sec

        m_buzzing = true;
    }
}

/* Clean up things and close devices */
void
wxGamePanel::StopBuzzer()
{
    if (m_buzzing) {
        /* Close */
        SDL_CloseAudio();

        m_buzzerTimer.Stop();

        m_buzzing = false;
    }
}

void
wxGamePanel::OnBuzzerTimer(wxTimerEvent& event)
{
    StopBuzzer();
}

void
wxGamePanel::InitTime()
{
    m_periLen = Config::Instance().GetPeriodLength() * 60 * 1000;
    m_shotClock = Config::Instance().GetShotClock() * 1000;

    ResetTime();
}

void
wxGamePanel::UpdateTime()
{
    // 경기 시간 갱신
    wxString timeStr(wxT("00:00"));
    long remainTime = m_periLen - m_elapseTime.Time();
    if (remainTime > 0) {
        timeStr = wxTimeSpan::Milliseconds(remainTime).Format(wxT("%M:%S"));
    }
    else {
        StartBuzzer();
        StopTime();
    }
    m_timeCtrl->SetValue(timeStr);

    // 공격 시간 갱신
    wxString shotClockStr(wxT("00"));
    long remainShotClock = m_shotClock - m_attackTime.Time();
    if (remainShotClock > 0) {
        shotClockStr
            = wxTimeSpan::Milliseconds(remainShotClock).Format(wxT("%S"));
    }
    else {
        if (m_playing) {
            StartBuzzer();

            // 무한 재귀 호출을 막기 위해서, false를 인자로 전달한다.
            ResetShotClock(false);
        }
    }
    m_shotClockCtrl->SetValue(shotClockStr);
}

void
wxGamePanel::StartTime()
{
    if (! m_started) {
        m_elapseTime.Resume();
        StartShotClock();

        m_started = true;
    }

    if (!m_timer.IsRunning())
        m_timer.Start(10);         // 10 milli-seconds interval
}

void
wxGamePanel::StopTime()
{
    if (m_started) {
        m_elapseTime.Pause();
        StopShotClock();

        m_started = false;
    }

    if (m_timer.IsRunning())
        m_timer.Stop();
}

void
wxGamePanel::ResetTime()
{
    m_elapseTime.Start();
    m_elapseTime.Pause();
    m_started = false;

    if (m_timer.IsRunning())
        m_timer.Stop();

    ResetShotClock();
}

void
wxGamePanel::StartShotClock()
{
    if (! m_playing) {
        m_attackTime.Resume();
        m_playing = true;
    }
}

void
wxGamePanel::StopShotClock()
{
    if (m_playing) {
        m_attackTime.Pause();
        m_playing = false;
    }
}

void
wxGamePanel::ResetShotClock(bool update)
{
    m_attackTime.Start();
    m_attackTime.Pause();
    m_playing = false;

    if (update)
        UpdateTime();
}

void
wxGamePanel::IncPeriod()
{
    m_period = (++m_period > 9) ? 9 : m_period;
    UpdatePeriod();
}

void
wxGamePanel::DecPeriod()
{
    m_period = (--m_period < 0) ? 0 : m_period;
    UpdatePeriod();
}

void
wxGamePanel::ResetPeriod()
{
    m_period = 0;
    UpdatePeriod();
}

void
wxGamePanel::UpdatePeriod()
{
    wxString str;
    str << m_period;
    m_periodCtrl->SetValue(str);
}
