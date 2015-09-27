#include "view/Renderer.h"
#include <QTextStream>
#include <QOpenGLBuffer>
#include <cmath>

Renderer::Renderer(QWidget *parent)
    : QOpenGLWidget(parent)
{
}

Renderer::~Renderer()
{
}

// called once by Qt GUI system, to allow initialization for OpenGL requirements
void Renderer::initializeGL()
{
    // Qt support for inline GL function calls
	initializeOpenGLFunctions();

    // sets the background clour
    glClearColor(0.7f, 0.7f, 1.0f, 1.0f);

    // links to and compiles the shaders, used for drawing simple objects
    program_ = new QOpenGLShaderProgram(this);
    program_->addShaderFromSourceFile(QOpenGLShader::Vertex, "per-fragment-phong.vs.glsl");
    program_->addShaderFromSourceFile(QOpenGLShader::Fragment, "per-fragment-phong.fs.glsl");
    program_->link();
    posAttr_ = program_->attributeLocation("position_attr");
    colAttr_ = program_->attributeLocation("colour_attr");
    norAttr_ = program_->attributeLocation("normal_attr");
    PMatrixUniform_ = program_->uniformLocation("proj_matrix");
    VMatrixUniform_ = program_->uniformLocation("viewMatrix");
    MMatrixUniform_ = program_->uniformLocation("model_matrix");
    programID_ = program_->programId();
}

// called by the Qt GUI system, to allow OpenGL drawing commands
void Renderer::paintGL()
{
    // Clear the screen buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set the current shader program
    glUseProgram(programID_);

    // Modify the current projection matrix so that we move the
    // camera away from the origin.  We'll draw the game at the
    // origin, and we need to back up to see it.
    QMatrix4x4 viewMatrix;
    viewMatrix.translate(0.0f, 0.0f, -40.0f);
    glUniformMatrix4fv(VMatrixUniform_, 1, false, viewMatrix.data());

    // Not implemented: set up lighting (if necessary)
    // Not implemented: scale and rotate the scene

    QMatrix4x4 model_matrix;

    // You'll be drawing unit cubes, so the game will have width
    // 10 and height 24 (game = 20, stripe = 4).  Let's translate
    // the game so that we can draw it starting at (0,0) but have
    // it appear centered in the window.

    model_matrix.translate(-5.0f, -12.0f, 0.0f);
    glUniformMatrix4fv(MMatrixUniform_, 1, false, model_matrix.data());

    // Not implemented: actually draw the current game state.
    // Here's some test code that draws red triangles at the
    // corners of the game board.
    generateBorderTriangles();

    // draw border
    if (triVertices.size() > 0)
    {
        // pass in the list of vertices and their associated colours
        // 3 coordinates per vertex, or per colour
        glVertexAttribPointer(posAttr_, 3, GL_FLOAT, GL_FALSE, 0, &triVertices[0]);
        glVertexAttribPointer(colAttr_, 3, GL_FLOAT, GL_FALSE, 0, &triColours[0]);
        glVertexAttribPointer(norAttr_, 3, GL_FLOAT, GL_FALSE, 0, &triNormals[0]);

        glEnableVertexAttribArray(posAttr_);
        glEnableVertexAttribArray(colAttr_);
        glEnableVertexAttribArray(norAttr_);

        // draw triangles
        glDrawArrays(GL_TRIANGLES, 0, triVertices.size()/3); // 3 coordinates per vertex

        glDisableVertexAttribArray(norAttr_);
        glDisableVertexAttribArray(colAttr_);
        glDisableVertexAttribArray(posAttr_);
    }

    // deactivate the program
    program_->release();
}

// called by the Qt GUI system, to allow OpenGL to respond to widget resizing
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
    glUniformMatrix4fv(PMatrixUniform_, 1, false, projectionMatrix.data());

    glViewport(0, 0, width(), height());

}

// computes the vertices and corresponding colours-per-vertex for a quadrilateral
// drawn from (x1, y1) to (x2, y2)
// Note: the magic numbers in the vector insert commands should be better documented
void Renderer::generateBorderTriangles()
{
    // make sure array lists are clear to start with
    triVertices.clear();
    triColours.clear();

    // add vertices to rectangle list
    float vectList [] = {
        0.0, 0.0, 0.0,  // bottom left triangle
        1.0, 0.0, 0.0,
        0.0, 1.0, 0.0,

        9.0, 0.0, 0.0,  // bottom right triangle
        10.0, 0.0, 0.0,
        10.0, 1.0, 0.0,

        0.0, 19.0, 0.0, // top left triangle
        1.0, 20.0, 0.0,
        0.0, 20.0, 0.0,

        10.0, 19.0, 0.0,    // top right triangle
        10.0, 20.0, 0.0,
        9.0, 20.0, 0.0 };
    triVertices.insert(triVertices.end(), vectList, vectList + 3*4*3); // 36 items in array

    // shader supports per-vertex colour; add colour for each vertex add colours to colour list - use current colour
    QColor borderColour = Qt::red;
    float colourList[] = { (float)borderColour.redF(), (float)borderColour.greenF(), (float)borderColour.blueF() };
    float normalList[] = { 0.0f, 0.0f, 1.0f }; // facing viewer
    for (int v = 0; v < 4 * 3; v++)
    {
        triColours.insert(triColours.end(), colourList, colourList + 3); // 3 coordinates per vertex
        triNormals.insert(triNormals.end(), normalList, normalList + 3); // 3 coordinates per vertex
    }
}

// override mouse press event
void Renderer::mousePressEvent(QMouseEvent * event)
{
    QTextStream cout(stdout);
    cout << "Stub: Button " << event->button() << " pressed.\n";
}

// override mouse release event
void Renderer::mouseReleaseEvent(QMouseEvent * event)
{
    QTextStream cout(stdout);
    cout << "Stub: Button " << event->button() << " pressed.\n";
}

// override mouse move event
void Renderer::mouseMoveEvent(QMouseEvent * event)
{
    QTextStream cout(stdout);
    cout << "Stub: Motion at " << event->x() << ", " << event->y() << ".\n";
}
