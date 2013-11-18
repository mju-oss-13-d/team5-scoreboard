#include <iostream>
#include "main.hpp"
#include "config.hpp"
#include "boardframe.hpp"

IMPLEMENT_APP(MyApp)

bool
MyApp::OnInit()
{
    if (!wxApp::OnInit())
        return false;

    // 영구 저장소에서 프로그램의 설정을 읽어온다.
    Config::Instance().Read();

    // 프로그램의 메임프레임 시작
    wxBoardFrame *boardFrame = new wxBoardFrame(wxT("ScoreBoard"));
    boardFrame->Centre();
    boardFrame->SetMinSize(wxBoardFrame::MIN_SIZE);
    boardFrame->Show(true);

    return true;
}

int
MyApp::OnRun()
{
    // initialize SDL
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cerr << "Unable to init SDL: " << SDL_GetError() << '\n';
        return -1;
    }

    // start the main loop
    return wxApp::OnRun();    
}

int
MyApp::OnExit()
{
    // cleanup SDL
    SDL_Quit();

    // 영구 저장소에 프로그램의 설정을 기록한다.
    Config::Instance().Write();
    
    // return the standard exit code
    return wxApp::OnExit();
}
