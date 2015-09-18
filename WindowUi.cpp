#include <QAction>
#include <QActionGroup>
#include <QApplication>
#include <QMenu>
#include <QMenuBar>

#include "WindowUi.h"

WindowUi::WindowUi(QWidget* mainWidget)
{
    createFileMenu();
    createDrawMenu();
    createGameMenu();

    setWindowTitle("CPSC453: Tetromino Apocalypse");

    mainWidget->setMinimumSize(300, 600);
    setCentralWidget(mainWidget);
}

WindowUi::~WindowUi()
{
}

void WindowUi::createFileMenu()
{
    QAction* newGameAction = new QAction("&New Game", this);
    newGameAction->setShortcut(QKeySequence(Qt::Key_N));
    newGameAction->setStatusTip("Creates new game");
    connect(newGameAction, SIGNAL(triggered()), this, SIGNAL(newGameRequested()));

    QAction* resetAction = new QAction("&Reset", this);
    resetAction->setShortcut(QKeySequence(Qt::Key_R));
    resetAction->setStatusTip("Resets the view");
    connect(resetAction, SIGNAL(triggered()), this, SIGNAL(resetRequested()));

    QAction* quitAction = new QAction("&Quit", this);
    quitAction->setShortcut(QKeySequence(Qt::Key_Q));
    quitAction->setStatusTip("Quits the application");
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    QMenu* fileMenu = menuBar()->addMenu("&File");
    fileMenu->addAction(newGameAction);
    fileMenu->addAction(resetAction);
    fileMenu->addAction(quitAction);
}

void WindowUi::createDrawMenu()
{
    QActionGroup* drawModeGroup = new QActionGroup(this);
    connect(drawModeGroup, SIGNAL(triggered(QAction*)), this, SLOT(setDrawMode(QAction*)));
    drawModeGroup->setExclusive(true);

    wireframeModeAction_ = new QAction("&Wireframe", this);
    wireframeModeAction_->setShortcut(QKeySequence(Qt::Key_W));
    wireframeModeAction_->setStatusTip("Draws the game using wireframes.");
    wireframeModeAction_->setCheckable(true);
    drawModeGroup->addAction(wireframeModeAction_);

    frameModeAction_ = new QAction("&Face", this);
    frameModeAction_->setShortcut(QKeySequence(Qt::Key_F));
    frameModeAction_->setStatusTip("Draws the game with faces.");
    frameModeAction_->setCheckable(true);
    drawModeGroup->addAction(frameModeAction_);

    multicolouredModeAction_ = new QAction("&Multicoloured", this);
    multicolouredModeAction_->setShortcut(QKeySequence(Qt::Key_M));
    multicolouredModeAction_->setStatusTip("Draws the game with each face a different colour.");
    multicolouredModeAction_->setCheckable(true);
    drawModeGroup->addAction(multicolouredModeAction_);

    QMenu* drawMenu = menuBar()->addMenu("&Draw");
    drawMenu->addAction(wireframeModeAction_);
    drawMenu->addAction(frameModeAction_);
    drawMenu->addAction(multicolouredModeAction_);
}

void WindowUi::createGameMenu()
{
    QAction* pauseAction = new QAction("&Pause", this);
    pauseAction->setShortcut(QKeySequence(Qt::Key_P));
    pauseAction->setStatusTip("Pause the game.");
    connect(pauseAction, SIGNAL(triggered()), this, SIGNAL(pauseGameRequested()));

    QAction* speedUpAction = new QAction("Speed up", this);
    speedUpAction->setShortcut(QKeySequence(Qt::Key_PageUp));
    speedUpAction->setStatusTip("Speeds up the game.");
    connect(speedUpAction, SIGNAL(triggered()), this, SIGNAL(speedUpGameRequested()));

    QAction* slowDownAction = new QAction("Slow down", this);
    slowDownAction->setShortcut(QKeySequence(Qt::Key_PageDown));
    slowDownAction->setStatusTip("Slows down the game.");
    connect(slowDownAction, SIGNAL(triggered()), this, SIGNAL(slowDownGameRequested()));

    QAction* autoIncreaseSpeedAction = new QAction("Slow down", this);
    autoIncreaseSpeedAction->setShortcut(QKeySequence(Qt::Key_A));
    autoIncreaseSpeedAction->setStatusTip("Will slowly increase the game speed over time.");
    connect(autoIncreaseSpeedAction, SIGNAL(triggered()), this, SIGNAL(autoIncreaseGameSpeedRequested()));

    QMenu* gameMenu = menuBar()->addMenu("&Game");
    gameMenu->addAction(pauseAction);
    gameMenu->addAction(speedUpAction);
    gameMenu->addAction(slowDownAction);
    gameMenu->addAction(autoIncreaseSpeedAction);
}

void WindowUi::setDrawMode(QAction* action)
{
    if (action == wireframeModeAction_)
    {
        emit wireframeViewModeRequested();
    }
    else if (action == frameModeAction_)
    {
        emit faceViewModeRequested();
    }
    else
    {
        emit multicolouredViewModeRequested();
    }
}
