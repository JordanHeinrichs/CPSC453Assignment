#pragma once
/*
* CPSC 453 - Introduction to Computer Graphics
* Assignment 1
*
* Renderer - OpenGL widget for drawing scene
*/

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_2_Core>
#include <QMatrix4x4>
#include <QKeyEvent>
#include <QOpenGLShaderProgram>
#include <QOpenGLShader>
#include <QMouseEvent>
#include <QVector>

#include "view/I_Renderer.h"

class Renderer : public QOpenGLWidget, protected QOpenGLFunctions_4_2_Core, public I_Renderer
{
    Q_OBJECT
public:
    Renderer(QWidget *parent = 0);
    virtual ~Renderer();

    // TODO
    void setViewMode(ViewMode /*viewMode*/) {}
    void renderGameBlocks() {}

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
    void setupBorderTriangleDrawing();
    void generateBorderTriangles();
    void drawBorderTriangles();
    void setupCube();
    void drawCube();

private:
    // member variables for shader manipulation
    GLuint programID_;
    GLuint positionAttribute_;
    GLuint colourAttribute_;
    GLuint normalAttribute_;
    GLuint MMatrixUniform_; // model matrix
    GLuint VMatrixUniform_; // view matrix
    GLuint PMatrixUniform_; // projection matrix

    QOpenGLShaderProgram *program_;

    GLuint boxVertexBufferObject_;
    GLuint boxVao_;
    GLuint triangleVertexBufferObject_;
    GLuint triangleVao_;

    QVector<GLfloat> triangleVertices_;
    QVector<GLfloat> triangleColours_;
    QVector<GLfloat> triangleNormals_;

    // helper function for loading shaders
    GLuint loadShader(GLenum type, const char *source);
};
