#pragma once
/*
 * CPSC 453 - Introduction to Computer Graphics
 * Assignment 1
 *
 * Window - Fundamental GUI for interacting within the scene
 */

#include <QMainWindow>
#include <QApplication>
#include <QMenuBar>
#include <QAction>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QActionGroup>

class Renderer;

class Window : public QMainWindow
{
    Q_OBJECT
public:
    Window(QWidget *parent = 0);
    virtual ~Window();

private slots:


private:
    Renderer* renderer_;

    // Menu items and actions
    QMenu* fileMenu_;
    QAction* quitAction_;

    // helper function for creating actions
    void createActions();
};
