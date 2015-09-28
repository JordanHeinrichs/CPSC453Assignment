#include <QAction>
#include <QActionGroup>
#include <QApplication>
#include <QKeyEvent>
#include <QMenu>
#include <QMenuBar>

#include "WindowUi.h"

namespace
{
    const QString PAUSE_TEXT = "&Pause";
}

WindowUi::WindowUi(QWidget* mainWidget)
{
    createFileMenu();
    createDrawMenu();
    createGameMenu();

    setWindowTitle("CPSC453: Tetromino Apocalypse");

    mainWidget->setMinimumSize(300, 600);
    setCentralWidget(mainWidget);

    setupKeyboardHandling();
    show();
}

WindowUi::~WindowUi()
{
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

void WindowUi::pauseActionPressed()
{
    if (pauseAction_->text() == PAUSE_TEXT)
    {
        pauseAction_->setText("un&pause");
        emit pauseGameRequested();
    }
    else
    {
        pauseAction_->setText(PAUSE_TEXT);
        emit unpauseGameRequested();
    }
}

bool WindowUi::eventFilter(QObject* object, QEvent* event)
{
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        switch(keyEvent->key())
        {
        case Qt::Key_Right:
            emit movePieceRightRequested();
            break;
        case Qt::Key_Left:
            emit movePieceLeftRequested();
            break;
        case Qt::Key_Up:
            emit rotatePieceCounterClockwiseRequested();
            break;
        case Qt::Key_Down:
            emit rotatePieceClockwiseRequested();
            break;
        case Qt::Key_Space:
            emit dropPieceRequested();
            break;
        }
    }
    return QObject::eventFilter(object, event);
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
    QAction* pauseAction_ = new QAction(PAUSE_TEXT, this);
    pauseAction_->setShortcut(QKeySequence(Qt::Key_P));
    pauseAction_->setStatusTip("Pause the game.");
    connect(pauseAction_, SIGNAL(triggered()), this, SLOT(pauseActionPressed()));

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
    gameMenu->addAction(pauseAction_);
    gameMenu->addAction(speedUpAction);
    gameMenu->addAction(slowDownAction);
    gameMenu->addAction(autoIncreaseSpeedAction);
}

void WindowUi::setupKeyboardHandling()
{
    qApp->installEventFilter(this);
}
