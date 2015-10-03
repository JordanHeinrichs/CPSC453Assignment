#include <QAction>
#include <QActionGroup>
#include <QApplication>
#include <QKeyEvent>
#include <QMenu>
#include <QMenuBar>
#include <QVBoxLayout>

#include "WindowUi.h"

#include <QDebug>

namespace
{
    const QString PAUSE_TEXT = "&Pause";
}

WindowUi::WindowUi(QWidget* renderer, QWidget* parent)
: QMainWindow(parent)
{
    createFileMenu();
    createDrawMenu();
    createGameMenu();

    setWindowTitle("CPSC453: Tetromino Apocalypse");

    // Setup the application's widget collection
    QVBoxLayout * layout = new QVBoxLayout();

    // Add renderer
    layout->addWidget(renderer);
    renderer->setMinimumSize(300, 600);

    QWidget * mainWidget = new QWidget();
    mainWidget->setLayout(layout);
    setCentralWidget(mainWidget);

    setupKeyboardHandling();
    setDefaultViewMode();
}

WindowUi::~WindowUi()
{
}

QAction& WindowUi::pauseAction() const
{
    return *pauseAction_;
}

void WindowUi::setDrawMode(QAction* action)
{
    if (action == wireframeModeAction_)
    {
        emit wireframeViewModeRequested();
    }
    else if (action == faceModeAction_)
    {
        emit faceViewModeRequested();
    }
    else
    {
        emit multicolouredViewModeRequested();
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
            return true;
        case Qt::Key_Left:
            emit movePieceLeftRequested();
            return true;
        case Qt::Key_Up:
            emit rotatePieceCounterClockwiseRequested();
            return true;
        case Qt::Key_Down:
            emit rotatePieceClockwiseRequested();
            return true;
        case Qt::Key_Space:
            emit dropPieceRequested();
            return true;
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

    faceModeAction_ = new QAction("&Face", this);
    faceModeAction_->setShortcut(QKeySequence(Qt::Key_F));
    faceModeAction_->setStatusTip("Draws the game with faces.");
    faceModeAction_->setCheckable(true);
    drawModeGroup->addAction(faceModeAction_);

    multicolouredModeAction_ = new QAction("&Multicoloured", this);
    multicolouredModeAction_->setShortcut(QKeySequence(Qt::Key_M));
    multicolouredModeAction_->setStatusTip("Draws the game with each face a different colour.");
    multicolouredModeAction_->setCheckable(true);
    drawModeGroup->addAction(multicolouredModeAction_);

    QMenu* drawMenu = menuBar()->addMenu("&Draw");
    drawMenu->addAction(wireframeModeAction_);
    drawMenu->addAction(faceModeAction_);
    drawMenu->addAction(multicolouredModeAction_);
}

void WindowUi::createGameMenu()
{
    pauseAction_ = new QAction(PAUSE_TEXT, this);
    pauseAction_->setShortcut(QKeySequence(Qt::Key_P));
    pauseAction_->setStatusTip("Pause the game.");

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

void WindowUi::setDefaultViewMode()
{
    multicolouredModeAction_->trigger();
}
