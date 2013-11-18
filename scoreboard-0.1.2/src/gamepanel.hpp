#ifndef __GAMEPANEL_H__
#define __GAMEPANEL_H__

#include "common.hpp"
#include <wx/stopwatch.h>

class wxGamePanel : public wxPanel
{
public:
    wxGamePanel(wxWindow* parent);

    void InitTime();
    void StartTime();
    void StopTime();
    void ResetTime();
    bool IsStarted() {
        return m_started;
    }

    void StartShotClock();
    void StopShotClock();
    void ResetShotClock(bool update = true);
    bool IsPlaying() {
        return m_playing;
    }

    void IncPeriod();
    void DecPeriod();
    void ResetPeriod();

private:
    void UpdateTime();
    void UpdatePeriod();

    void OnTimer(wxTimerEvent& event);
    void OnBuzzerTimer(wxTimerEvent& event);

    void StartBuzzer();
    void StopBuzzer();

private:
    wxTimer m_timer;
    bool m_started;

    wxLCDWindow* m_timeCtrl;
    wxStopWatch m_elapseTime;
    long m_periLen;             // 단위: ms

    wxLCDWindow *m_shotClockCtrl;
    wxStopWatch m_attackTime;
    long m_shotClock;           // 단위 ms
    bool m_playing;

    wxLCDWindow *m_periodCtrl;
    int m_period;

    wxTimer m_buzzerTimer;
    bool m_buzzing;

};

#endif  // __GAMEPANEL_H__
