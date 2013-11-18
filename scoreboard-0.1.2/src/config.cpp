#include "config.hpp"
#include <wx/config.h>

static const wxChar *keyPeriodLength = wxT("PeriodLength");
static const long defaultPeriodLength = 20; // 20 min

static const wxChar *keyShotClock = wxT("ShotClock");
static const long defaultShotClock = 30;    // 30 sec

Config&
Config::Instance()
{
    static Config instance;
    return instance;
}

Config::Config()
    : m_periLen(defaultPeriodLength)
    , m_shotClock(defaultShotClock)
{
}

Config::Config(Config const&)
{
    // XXX
}

Config&
Config::operator=(Config const&)
{
    return Config::Instance();
}

void
Config::Validate()
{
    if (! IsValidPeriodLength()) {
        m_periLen = defaultPeriodLength;
    }
    if (! IsValidShotClock()) {
        m_shotClock = defaultShotClock;
    }
}

bool
Config::Read()
{
    wxConfig *config = new wxConfig(wxT(PACKAGE_NAME));
    config->Read(keyPeriodLength, &m_periLen, defaultPeriodLength);
    config->Read(keyShotClock, &m_shotClock, defaultShotClock);
    delete config;
    Validate();
    return true;
}

bool
Config::Write()
{
    Validate();
    wxConfig *config = new wxConfig(wxT(PACKAGE_NAME));
    config->Write(keyPeriodLength, m_periLen);
    config->Write(keyShotClock, m_shotClock);
    delete config;
    return true;
}
