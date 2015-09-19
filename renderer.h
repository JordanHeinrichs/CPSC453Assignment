#pragma once
/*
* CPSC 453 - Introduction to Computer Graphics
* Assignment 1
*
* Renderer - OpenGL widget for drawing scene
*/

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QKeyEvent.h>
#include <QOpenGLShaderProgram>
#include <QOpenGLShader>
#include <QMouseEvent>

using namespace std;

class Renderer : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    Renderer(QWidget *parent = 0);
    virtual ~Renderer();

protected:
    // Called when OpenGL is first initialized
    void initializeGL();

    // Called when the window is resized
    void resizeGL(int w, int h);

    // Called when the window needs to be redrawn
    void paintGL();

    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);

private:
    // member variables for shader manipulation
    GLuint programID_;
    GLuint posAttr_;
    GLuint colAttr_;
    GLuint norAttr_;
    GLuint MMatrixUniform_; // model matrix
    GLuint VMatrixUniform_; // view matrix
    GLuint PMatrixUniform_; // projection matrix

    QOpenGLShaderProgram *program_;

    // for storing triangle vertices and colours
    vector<GLfloat> triVertices;
    vector<GLfloat> triColours;
    vector<GLfloat> triNormals;

    // helper function for loading shaders
    GLuint loadShader(GLenum type, const char *source);

    void generateBorderTriangles();
};
