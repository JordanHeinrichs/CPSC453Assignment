/*
 * CPSC 453 - Introduction to Computer Graphics
 * Assignment 1
 *
 * Entry point for execution into the program
 */

#include "application/AssignmentApp.h"

int main(int argc, char *argv[])
{
    AssignmentApp app(argc, argv);
    return app.exec();
}
