#include "view/Renderer.h"
#include <QTextStream>
#include <QOpenGLBuffer>
#include <cmath>
#include <cstdlib>
#include <QTime>

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
}

Renderer::Renderer(const I_Game& game, QWidget *parent)
: QOpenGLWidget(parent)
, game_(game)
, refreshTimer_()
, viewMode_(MultiColored)
{
}

Renderer::~Renderer()
{
}

void Renderer::setViewMode(ViewMode viewMode)
{
    viewMode_ = viewMode;
}

#include <stdio.h> // TODO
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
    colorAttribute_ = program_->attributeLocation("color_attr");
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
    const int colorsBufferSize = triangleColors_.size() * sizeof(GLfloat);
    const int normalsBufferSize = triangleNormals_.size() * sizeof(GLfloat);
    const int totalBufferSize = vertexBufferSize + colorsBufferSize + normalsBufferSize;

    // Initialize VBOs
    glGenVertexArrays(1, &triangleVao_);
    glBindVertexArray(triangleVao_);
    glGenBuffers(1, &triangleVertexBufferObject_);
    glBindBuffer(GL_ARRAY_BUFFER, triangleVertexBufferObject_);

    glBufferData(GL_ARRAY_BUFFER, totalBufferSize,
        NULL, GL_STATIC_DRAW);

    // Upload the data to the GPU
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertexBufferSize, triangleVertices_.data());
    glBufferSubData(GL_ARRAY_BUFFER, vertexBufferSize, colorsBufferSize, triangleColors_.data());
    glBufferSubData(GL_ARRAY_BUFFER, vertexBufferSize + colorsBufferSize, normalsBufferSize, triangleNormals_.data());

    glEnableVertexAttribArray(positionAttribute_);
    glEnableVertexAttribArray(colorAttribute_);
    glEnableVertexAttribArray(normalAttribute_);

    // Specifiy where those are in the VBO
    glVertexAttribPointer(positionAttribute_, 3, GL_FLOAT, 0, GL_FALSE,
        reinterpret_cast<const GLvoid*>(0));
    glVertexAttribPointer(colorAttribute_, 3, GL_FLOAT, 0, GL_FALSE,
        reinterpret_cast<const GLvoid*>(vertexBufferSize));
    glVertexAttribPointer(normalAttribute_, 3, GL_FLOAT, 0, GL_FALSE,
        reinterpret_cast<const GLvoid*>(vertexBufferSize + colorsBufferSize));
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

    triangleColors_.clear();
    triangleNormals_.clear();
    QColor borderColor = Qt::red;
    for (int vertex = 0; vertex < 4 * 3; vertex++)
    {
        triangleColors_ << QVector<GLfloat>(
            {static_cast<GLfloat>(borderColor.redF()),
            static_cast<GLfloat>(borderColor.greenF()),
            static_cast<GLfloat>(borderColor.blueF())});
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
    populateCubeColors();
    const int vertexBufferSize = CUBE_VERTICES.size() * sizeof(GLfloat);
    const int colorsBufferSize = cubeColors_.at(0).size() * sizeof(GLfloat);
    const int normalsBufferSize = CUBE_NORMALS.size() * sizeof(GLfloat);
    const int totalBufferSize = vertexBufferSize + colorsBufferSize + normalsBufferSize;

    for (int i = 0; i < NumberOfColors; ++i)
    {
        glGenVertexArrays(1, &boxVertexArrayObjects_[i]);
        glBindVertexArray(boxVertexArrayObjects_[i]);
        glGenBuffers(1, &boxVertexBufferObjects_[i]);
        glBindBuffer(GL_ARRAY_BUFFER, boxVertexBufferObjects_[i]);

        glBufferData(GL_ARRAY_BUFFER, totalBufferSize,
            NULL, GL_STATIC_DRAW);

        glBufferSubData(GL_ARRAY_BUFFER, 0, vertexBufferSize, CUBE_VERTICES.data());
        printf("Setting buffer subData to be %f, %f, %f\n", cubeColors_.at(i).at(0), cubeColors_.at(i).at(1), cubeColors_.at(i).at(2));
        glBufferSubData(GL_ARRAY_BUFFER, vertexBufferSize, colorsBufferSize, cubeColors_.at(i).data());
        glBufferSubData(GL_ARRAY_BUFFER, vertexBufferSize + colorsBufferSize, normalsBufferSize, CUBE_NORMALS.data());

        glEnableVertexAttribArray(positionAttribute_);
        glEnableVertexAttribArray(colorAttribute_);
        glEnableVertexAttribArray(normalAttribute_);

        glVertexAttribPointer(positionAttribute_, 3, GL_FLOAT, 0, GL_FALSE,
            reinterpret_cast<const void*>(0));
        glVertexAttribPointer(colorAttribute_, 3, GL_FLOAT, 0, GL_FALSE,
            reinterpret_cast<const void*>(vertexBufferSize));
        glVertexAttribPointer(normalAttribute_, 3, GL_FLOAT, 0, GL_FALSE,
            reinterpret_cast<const void*>(vertexBufferSize + colorsBufferSize));
    }
}

void Renderer::populateCubeColors()
{
    QList<QColor> colorsToAdd = {Qt::yellow, Qt::red, Qt::blue, Qt::cyan, Qt::magenta,
        Qt::green, Qt::gray, Qt::darkGray};

    for (int colorIndex = 0; colorIndex < Piece0MultiColored; ++colorIndex)
    {
        QVector<GLfloat> cubeColor;
        for (int i = 0; i < CUBE_VERTICES.size() / 3; ++i)
        {
            cubeColor << QVector<GLfloat>(
                {static_cast<GLfloat>(colorsToAdd.at(colorIndex).redF()),
                static_cast<GLfloat>(colorsToAdd.at(colorIndex).greenF()),
                static_cast<GLfloat>(colorsToAdd.at(colorIndex).blueF())});
        }
        cubeColors_ << cubeColor;
    }

    // Randomize the colors.
    qsrand(QTime().msecsSinceStartOfDay());
    for (int colorIndex = Piece0MultiColored; colorIndex <= Piece6MultiColored; ++colorIndex)
    {
        QVector<GLfloat> cubeColor;
        // Both triangles on the same face are to be the same color.
        for (int i = 0; i < CUBE_VERTICES.size() / (3 * 3 * 2); ++i)
        {
            QVector<GLfloat> faceColor =
                {static_cast<GLfloat>(qrand() / static_cast<float>(RAND_MAX)),
                static_cast<GLfloat>(qrand() / static_cast<float>(RAND_MAX)),
                static_cast<GLfloat>(qrand() / static_cast<float>(RAND_MAX))};
            cubeColor << faceColor << faceColor << faceColor << faceColor << faceColor << faceColor;
        }
        cubeColors_ << cubeColor;
    }
}

void Renderer::drawCube(int row, int column, PieceId pieceId)
{
    QMatrix4x4 modelMatrix;
    modelMatrix.translate(-5.0f, -12.0f, 0.0f);
    modelMatrix.translate(column, row, 0.0f);
    glUniformMatrix4fv(modelMatrixUniform_, 1, false, modelMatrix.data());

    // printf("Drawing cube with pieceId %d\n", pieceId);
    glBindVertexArray(boxVertexArrayObjects_[pieceId]);
    glDrawArrays(GL_TRIANGLES, 0, CUBE_VERTICES.size() / 3);
}

void Renderer::drawGameSpaceWell()
{
    for (int column = -1; column <= game_.getWidth(); column++)
    {
        drawCube(-1, column, Border);
    }

    for (int row = 0; row < game_.getHeight(); row++)
    {
        drawCube(row, -1, Border);
        drawCube(row, game_.getWidth(), Border);
    }
}

void Renderer::drawGamePieces()
{
    for (int row = 0; row < game_.getHeight() + 4; ++row)
    {
        for (int column = 0; column < game_.getWidth(); ++column)
        {
            const int pieceState = game_.get(row, column);
            if (pieceState != GAME_SPACE_EMPTY)
            {
                drawCube(row, column, pieceIdForViewMode(pieceState));
            }
        }
    }
}

Renderer::PieceId Renderer::pieceIdForViewMode(int pieceState) const
{
    if (viewMode_ == MultiColored)
    {
        return static_cast<PieceId>(pieceState + Piece0MultiColored);
    }
    else
    {
        return static_cast<PieceId>(pieceState);
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
