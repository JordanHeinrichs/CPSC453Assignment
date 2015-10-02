/*
 * CPSC 453 - Introduction to Computer Graphics
 * Assignment 1
 *
 * Entry point for execution into the program
 */

#include <QScopedPointer>
#include "application/AssignmentApp.h"

int main(int argc, char *argv[])
{
    QScopedPointer<AssignmentApp> app;
    app.reset(new AssignmentApp(argc, argv));
    return app->exec();
}
