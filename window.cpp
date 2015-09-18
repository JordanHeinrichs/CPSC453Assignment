#include "window.h"
#include "renderer.h"

Window::Window(QWidget* parent) :
    QMainWindow(parent)
{
    setWindowTitle("CPSC453: Tetromino Apocalypse");

    // Create the main drawing object
    renderer_ = new Renderer();
    createActions();

    // Create the menus
    // Setup the file menu
    fileMenu_ = menuBar()->addMenu("&File");
    fileMenu_->addAction(quitAction_);

    // Setup the application's widget collection
    QVBoxLayout* layout = new QVBoxLayout();

    layout->addWidget(renderer_);
    renderer_->setMinimumSize(300, 600);

    QWidget* mainWidget = new QWidget();
    mainWidget->setLayout(layout);
    setCentralWidget(mainWidget);
}

Window::~Window()
{
    delete renderer_;
}

void Window::createActions()
{
    quitAction_ = new QAction("&Quit", this);
    quitAction_->setShortcut(QKeySequence(Qt::Key_Q));
    quitAction_->setStatusTip("Quits the application");
    connect(quitAction_, SIGNAL(triggered()), qApp, SLOT(quit()));
}
