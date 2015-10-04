#pragma once
/*
* CPSC 453 - Introduction to Computer Graphics
* Assignment 1
*
* Renderer - OpenGL widget for drawing scene
*/

#include <QElapsedTimer>
#include <QHash>
#include <QKeyEvent>
#include <QMatrix4x4>
#include <QMouseEvent>
#include <QOpenGLFunctions_4_2_Core>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QOpenGLWidget>
#include <QPoint>
#include <QTimer>
#include <QVector>
#include <QWidget>

#include "view/I_Renderer.h"
#include "businessLogic/I_Game.h"

class Renderer : public QOpenGLWidget, protected QOpenGLFunctions_4_2_Core, public I_Renderer
{
    Q_OBJECT
public:
    Renderer(const I_Game& game, QWidget *parent = 0);
    virtual ~Renderer();

    void setViewMode(ViewMode viewMode);

public slots:
    void resetView();

protected:
    // Called when OpenGL is first initialized
    void initializeGL();

    // Called when the window is resized
    void resizeGL(int w, int h);

    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);

private slots:
    // Called when the window needs to be redrawn
    void paintGL();
    void recalculateRotationRates();

private:
    enum PieceId
    {
        Piece0 = 0,
        Piece1,
        Piece2,
        Piece3,
        Piece4,
        Piece5,
        Piece6,
        Piece0MultiColored,
        Piece1MultiColored,
        Piece2MultiColored,
        Piece3MultiColored,
        Piece4MultiColored,
        Piece5MultiColored,
        Piece6MultiColored,
        Border,
        NumberOfColors
    };

    void setupBorderTriangleDrawing();
    void generateBorderTriangles();
    void drawBorderTriangles();

    void setupCube();
    void populateCubeColors();
    void drawCube(int row, int column, PieceId pieceId);
    void drawGameSpaceWell();
    void drawGamePieces();

    PieceId pieceIdForViewMode(int pieceState) const;
    void setupAndStartRefreshTimer();

    void activateViewMode();
    void zeroAxisRotationRateIfWithinDeadZone(double& rotationRate) const;
    int calculateDifferenceBetweenMousePoints(const QPoint& point1, const QPoint& point2) const;

private:
    const I_Game& game_;
    QTimer refreshTimer_;
    ViewMode viewMode_;

    // member variables for shader manipulation
    GLuint programID_;
    GLuint positionAttribute_;
    GLuint colorAttribute_;
    GLuint normalAttribute_;
    GLuint projectionMatrixUniform_;
    GLuint viewMatrixUniform_;
    GLuint modelMatrixUniform_;

    QOpenGLShaderProgram* program_;

    GLuint boxVertexBufferObjects_[NumberOfColors];
    GLuint boxVertexArrayObjects_[NumberOfColors];
    GLuint triangleVertexBufferObject_;
    GLuint triangleVao_;

    QVector<GLfloat> triangleVertices_;
    QVector<GLfloat> triangleColors_;
    QVector<GLfloat> triangleNormals_;

    QVector<QVector<GLfloat> > cubeColors_;

    // helper function for loading shaders
    GLuint loadShader(GLenum type, const char *source);


    double xAxisRotationRate_;
    double yAxisRotationRate_;
    double zAxisRotationRate_;

    double xAxisRotation_;
    double yAxisRotation_;
    double zAxisRotation_;
    double scaling_;

    QPoint lastMousePosition_;

    QElapsedTimer timeBetweenMouseMoveX_;
    QElapsedTimer timeBetweenMouseMoveY_;
    QElapsedTimer timeBetweenMouseMoveZ_;
    QElapsedTimer timeBetweenMouseMoveScaling_;
};
