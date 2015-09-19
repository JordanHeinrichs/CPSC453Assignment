#pragma once

#include <QObject>
class I_Game;
class I_WindowUi;
class I_Renderer;

class WindowView : public QObject
{
    Q_OBJECT
public:
    WindowView(I_Game& game, I_WindowUi& windowUi, I_Renderer& renderer);
    virtual ~WindowView();

private slots:
    void setViewModeWireframe();
    void setViewModeFace();
    void setViewModeMulticoloured();

private:
    void setupKeyboardControls();
    void setupGameOptions();

private:
    I_Game& game_;
    I_WindowUi& windowUi_;
    I_Renderer& renderer_;
};
