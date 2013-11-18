#ifndef __SB_CONFIG_HPP__
#define __SB_CONFIG_HPP__

#include "common.hpp"

class Config
{
public:
    static Config& Instance();

    bool Read();
    bool Write();

    void SetPeriodLength(int n) {
        if (IsValidPeriodLength())
            m_periLen = n;
    }
    int GetPeriodLength() {
        return m_periLen;
    }
    static bool IsValidPeriodLength(int n) {
        return (n > 0 && n < 100);
    }
    bool IsValidPeriodLength() {
        return IsValidPeriodLength(m_periLen);
    }

    void SetShotClock(int n) {
        if (IsValidShotClock())
            m_shotClock = n;
    }
    int GetShotClock() {
        return m_shotClock;
    }
    static bool IsValidShotClock(int n) {
        return (n > 0 && n < 100);
    }
    bool IsValidShotClock() {
        return IsValidShotClock(m_shotClock);
    }

private:
    Config();
    Config(Config const&);
    Config& operator=(Config const&);

    void Validate();

    int m_periLen;
    int m_shotClock;
};

#endif  // __SB_CONFIG_HPP__
