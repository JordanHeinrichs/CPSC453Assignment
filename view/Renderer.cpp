#include "view/Renderer.h"
#include <QTextStream>
#include <QOpenGLBuffer>
#include <cmath>

namespace
{
    const int WIDTH_OF_GAME_SCREEN = 10;
    const int HEIGHT_OF_GAME_SCREEN = 24;
    const int REFRESH_PERIOD = 33;
    const int GAME_SPACE_EMPTY = -1;

    const QVector<GLfloat> CUBE_VERTICES = {
        0.0, 0.0, 0.0,   0.0, 0.0, 1.0,   0.0, 1.0, 0.0,
        0.0, 1.0, 0.0,   0.0, 0.0, 1.0,   0.0, 1.0, 1.0,
        0.0, 0.0, 0.0,   0.0, 1.0, 0.0,   1.0, 1.0, 0.0,
        1.0, 0.0, 0.0,   0.0, 0.0, 0.0,   1.0, 1.0, 0.0,
        0.0, 0.0, 0.0,   1.0, 0.0, 0.0,   1.0, 0.0, 1.0,
        0.0, 0.0, 0.0,   1.0, 0.0, 1.0,   0.0, 0.0, 1.0,
        0.0, 0.0, 1.0,   1.0, 0.0, 1.0,   0.0, 1.0, 1.0,
        0.0, 1.0, 1.0,   1.0, 0.0, 1.0,   1.0, 1.0, 1.0,
        0.0, 1.0, 0.0,   0.0, 1.0, 1.0,   1.0, 1.0, 0.0,
        0.0, 1.0, 1.0,   1.0, 1.0, 1.0,   1.0, 1.0, 0.0,
        1.0, 0.0, 0.0,   1.0, 1.0, 0.0,   1.0, 1.0, 1.0,
        1.0, 0.0, 0.0,   1.0, 1.0, 1.0,   1.0, 0.0, 1.0};

    const QVector<GLfloat> CUBE_NORMALS = {
        -1.0, 0.0, 0.0,  -1.0, 0.0, 0.0,  -1.0, 0.0, 0.0,
        -1.0, 0.0, 0.0,  -1.0, 0.0, 0.0,  -1.0, 0.0, 0.0,
        0.0, 0.0, -1.0,  0.0, 0.0, -1.0,  0.0, 0.0, -1.0,
        0.0, 0.0, -1.0,  0.0, 0.0, -1.0,  0.0, 0.0, -1.0,
        0.0, -1.0, 0.0,  0.0, -1.0, 0.0,  0.0, -1.0, 0.0,
        0.0, -1.0, 0.0,  0.0, -1.0, 0.0,  0.0, -1.0, 0.0,
        0.0, 0.0, 1.0,   0.0, 0.0, 1.0,   0.0, 0.0, 1.0,
        0.0, 0.0, 1.0,   0.0, 0.0, 1.0,   0.0, 0.0, 1.0,
        0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0,
        0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0,
        1.0, 0.0, 0.0,   1.0, 0.0, 0.0,   1.0, 0.0, 0.0,
        1.0, 0.0, 0.0,   1.0, 0.0, 0.0,   1.0, 0.0, 0.0};

    const QVector<GLfloat> CUBE_COLOUR_GREEN = {
        0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0,
        0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0,
        0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0,
        0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0,
        0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0,
        0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0,
        0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0,
        0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0,
        0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0,
        0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0,
        0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0,
        0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0};
}

Renderer::Renderer(const I_Game& game, QWidget *parent)
: QOpenGLWidget(parent)
, game_(game)
, refreshTimer_()
, viewMode_(MultiColoured)
{
}

Renderer::~Renderer()
{
}

void Renderer::setViewMode(ViewMode viewMode)
{
    viewMode_ = viewMode;
}

#include <stdio.h>
void Renderer::initializeGL()
{
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);

    // sets the background clour
    glClearColor(0.7f, 0.7f, 1.0f, 1.0f);

    program_ = new QOpenGLShaderProgram(this);
    program_->addShaderFromSourceFile(QOpenGLShader::Vertex, "per-fragment-phong.vs.glsl");
    program_->addShaderFromSourceFile(QOpenGLShader::Fragment, "per-fragment-phong.fs.glsl");
    program_->link();
    positionAttribute_ = program_->attributeLocation("position_attr");
    colourAttribute_ = program_->attributeLocation("colour_attr");
    normalAttribute_ = program_->attributeLocation("normal_attr");
    projectionMatrixUniform_ = program_->uniformLocation("proj_matrix");
    viewMatrixUniform_ = program_->uniformLocation("view_matrix");
    modelMatrixUniform_ = program_->uniformLocation("model_matrix");
    programID_ = program_->programId();

    setupBorderTriangleDrawing();
    setupCube();

    setupAndStartRefreshTimer();
}

void Renderer::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(programID_);
    glDepthFunc(GL_LESS);

    // Modify the current projection matrix so that we move the
    // camera away from the origin.  We'll draw the game at the
    // origin, and we need to back up to see it.
    QMatrix4x4 viewMatrix;
    viewMatrix.translate(0.0f, 0.0f, -40.0f);
    glUniformMatrix4fv(viewMatrixUniform_, 1, false, viewMatrix.data());

    // Not implemented: set up lighting (if necessary)
    // Not implemented: scale and rotate the scene


    // You'll be drawing unit cubes, so the game will have width
    // 10 and height 24 (game = 20, stripe = 4).  Let's translate
    // the game so that we can draw it starting at (0,0) but have
    // it appear centered in the window.

    QMatrix4x4 modelMatrix;
    modelMatrix.translate(-5.0f, -12.0f, 0.0f);
    glUniformMatrix4fv(modelMatrixUniform_, 1, false, modelMatrix.data());

    activateViewMode();
    drawBorderTriangles();
    drawGameSpaceWell();
    drawGamePieces();

    // Always set view mode back to GL_FILL for everything else.
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    program_->release();

    update();
}

void Renderer::resizeGL(int w, int h)
{
    // width and height are better variables to use
    Q_UNUSED(w); Q_UNUSED(h);

    // update viewing projections
    glUseProgram(programID_);

    // Set up perspective projection, using current size and aspect
    // ratio of display
    QMatrix4x4 projectionMatrix;
    projectionMatrix.perspective(40.0f, (GLfloat)width() / (GLfloat)height(),
                                  0.1f, 1000.0f);
    glUniformMatrix4fv(projectionMatrixUniform_, 1, false, projectionMatrix.data());

    glViewport(0, 0, width(), height());
}

void Renderer::setupBorderTriangleDrawing()
{
    generateBorderTriangles();
    const int vertexBufferSize = triangleVertices_.size() * sizeof(GLfloat);
    const int coloursBufferSize = triangleColours_.size() * sizeof(GLfloat);
    const int normalsBufferSize = triangleNormals_.size() * sizeof(GLfloat);
    const int totalBufferSize = vertexBufferSize + coloursBufferSize + normalsBufferSize;

    // Initialize VBOs
    glGenVertexArrays(1, &triangleVao_);
    glBindVertexArray(triangleVao_);
    glGenBuffers(1, &triangleVertexBufferObject_);
    glBindBuffer(GL_ARRAY_BUFFER, triangleVertexBufferObject_);

    glBufferData(GL_ARRAY_BUFFER, totalBufferSize,
        NULL, GL_STATIC_DRAW);

    // Upload the data to the GPU
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertexBufferSize, triangleVertices_.data());
    glBufferSubData(GL_ARRAY_BUFFER, vertexBufferSize, coloursBufferSize, triangleColours_.data());
    glBufferSubData(GL_ARRAY_BUFFER, vertexBufferSize + coloursBufferSize, normalsBufferSize, triangleNormals_.data());

    glEnableVertexAttribArray(positionAttribute_);
    glEnableVertexAttribArray(colourAttribute_);
    glEnableVertexAttribArray(normalAttribute_);

    // Specifiy where those are in the VBO
    glVertexAttribPointer(positionAttribute_, 3, GL_FLOAT, 0, GL_FALSE,
        reinterpret_cast<const GLvoid*>(0));
    glVertexAttribPointer(colourAttribute_, 3, GL_FLOAT, 0, GL_FALSE,
        reinterpret_cast<const GLvoid*>(vertexBufferSize));
    glVertexAttribPointer(normalAttribute_, 3, GL_FLOAT, 0, GL_FALSE,
        reinterpret_cast<const GLvoid*>(vertexBufferSize + coloursBufferSize));
}

void Renderer::generateBorderTriangles()
{
    triangleVertices_ = {
        0.0, 0.0, 0.0,  // bottom left triangle
        1.0, 0.0, 0.0,
        0.0, 1.0, 0.0,

        9.0, 0.0, 0.0,  // bottom right triangle
        10.0, 0.0, 0.0,
        10.0, 1.0, 0.0,

        0.0, 19.0, 0.0, // top left triangle
        1.0, 20.0, 0.0,
        0.0, 20.0, 0.0,

        10.0, 19.0, 0.0, // top right triangle
        10.0, 20.0, 0.0,
        9.0, 20.0, 0.0};

    triangleColours_.clear();
    triangleNormals_.clear();
    QColor borderColour = Qt::red;
    for (int vertex = 0; vertex < 4 * 3; vertex++)
    {
        triangleColours_ << QVector<GLfloat>(
            {static_cast<GLfloat>(borderColour.redF()),
            static_cast<GLfloat>(borderColour.greenF()),
            static_cast<GLfloat>(borderColour.blueF())});
        triangleNormals_ << QVector<GLfloat>({ 0.0f, 0.0f, 1.0f });
    }
}

void Renderer::drawBorderTriangles()
{
    glBindVertexArray(triangleVao_);
    glDrawArrays(GL_TRIANGLES, 0, triangleVertices_.size() / 3);
}

void Renderer::setupCube()
{
    const int vertexBufferSize = CUBE_VERTICES.size() * sizeof(GLfloat);
    const int coloursBufferSize = CUBE_COLOUR_GREEN.size() * sizeof(GLfloat);
    const int normalsBufferSize = CUBE_NORMALS.size() * sizeof(GLfloat);
    const int totalBufferSize = vertexBufferSize + coloursBufferSize + normalsBufferSize;

    glGenVertexArrays(1, &boxVao_);
    glBindVertexArray(boxVao_);
    glGenBuffers(1, &boxVertexBufferObject_);
    glBindBuffer(GL_ARRAY_BUFFER, boxVertexBufferObject_);

    glBufferData(GL_ARRAY_BUFFER, totalBufferSize,
        NULL, GL_STATIC_DRAW);

    glBufferSubData(GL_ARRAY_BUFFER, 0, vertexBufferSize, CUBE_VERTICES.data());
    glBufferSubData(GL_ARRAY_BUFFER, vertexBufferSize, coloursBufferSize, CUBE_COLOUR_GREEN.data());
    glBufferSubData(GL_ARRAY_BUFFER, vertexBufferSize + coloursBufferSize, normalsBufferSize, CUBE_NORMALS.data());

    glEnableVertexAttribArray(positionAttribute_);
    glEnableVertexAttribArray(colourAttribute_);
    glEnableVertexAttribArray(normalAttribute_);

    glVertexAttribPointer(positionAttribute_, 3, GL_FLOAT, 0, GL_FALSE,
        reinterpret_cast<const void*>(0));
    glVertexAttribPointer(colourAttribute_, 3, GL_FLOAT, 0, GL_FALSE,
        reinterpret_cast<const void*>(vertexBufferSize));
    glVertexAttribPointer(normalAttribute_, 3, GL_FLOAT, 0, GL_FALSE,
        reinterpret_cast<const void*>(vertexBufferSize + coloursBufferSize));
}

void Renderer::drawCube(int row, int column, QColor color)
{
    Q_UNUSED(color);
    QMatrix4x4 modelMatrix;
    modelMatrix.translate(-5.0f, -12.0f, 0.0f);
    modelMatrix.translate(column, row, 0.0f);
    glUniformMatrix4fv(modelMatrixUniform_, 1, false, modelMatrix.data());

    glDrawArrays(GL_TRIANGLES, 0, CUBE_VERTICES.size() / 3);
}

void Renderer::drawGameSpaceWell()
{
    glBindVertexArray(boxVao_);

    for (int column = -1; column <= game_.getWidth(); column++)
    {
        drawCube(-1, column, Qt::darkGray);
    }

    for (int row = 0; row < game_.getHeight(); row++)
    {
        drawCube(row, -1, Qt::darkGray);
        drawCube(row, game_.getWidth(), Qt::darkGray);
    }
}

void Renderer::drawGamePieces()
{
    glBindVertexArray(boxVao_);
    for (int row = 0; row < game_.getHeight() + 4; ++row)
    {
        for (int column = 0; column < game_.getWidth(); ++column)
        {
            const int pieceState = game_.get(row, column);
            if (pieceState != GAME_SPACE_EMPTY)
            {
                drawCube(row, column, colorForPieceId(pieceState));
            }
        }
    }
}

QColor Renderer::colorForPieceId(int pieceId) const
{
    switch(pieceId)
    {
    case 0:
        return Qt::red;
    case 1:
        return Qt::green;
    case 2:
        return Qt::blue;
    case 3:
        return Qt::cyan;
    case 4:
        return Qt::magenta;
    case 5:
        return Qt::yellow;
    default:
        return Qt::gray;
    }
}

void Renderer::setupAndStartRefreshTimer()
{
    refreshTimer_.setInterval(REFRESH_PERIOD);
    refreshTimer_.start();
    connect(&refreshTimer_, SIGNAL(timeout()), this, SLOT(paintGL()));
}

void Renderer::activateViewMode()
{
    if (viewMode_ == Wireframe)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
}

void Renderer::mousePressEvent(QMouseEvent * event)
{
    QTextStream cout(stdout);
    cout << "Stub: Button " << event->button() << " pressed.\n";
}

void Renderer::mouseReleaseEvent(QMouseEvent * event)
{
    QTextStream cout(stdout);
    cout << "Stub: Button " << event->button() << " pressed.\n";
}

void Renderer::mouseMoveEvent(QMouseEvent * event)
{
    QTextStream cout(stdout);
    cout << "Stub: Motion at " << event->x() << ", " << event->y() << ".\n";
}
