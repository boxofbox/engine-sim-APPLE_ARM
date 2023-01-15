#pragma once

#include "yds_window.h"
#include <SDL.h>
#include <SDL_video.h>

class ysSdlWindowSystem;
class ysOpenGLSdlContext;

class ysSdlWindow : public ysWindow {
    friend ysSdlWindowSystem;
    friend ysOpenGLSdlContext;

public:
    ysSdlWindow();
    ~ysSdlWindow();

    // Overrides
    virtual ysError InitializeWindow(ysWindow *parent, std::string title, WindowStyle style, int x, int y, int width, int height, ysMonitor *monitor) override;
    virtual void SetState(WindowState state) override;
    virtual void SetTitle(std::string title) override;
    SDL_Renderer* GetRenderer() const {return m_renderer;}

protected:

    SDL_Window *m_window;
    SDL_Renderer *m_renderer;

    WindowState m_appliedState = WindowState::Unknown;
};
