#pragma once
/*
* CPSC 453 - Introduction to Computer Graphics
* Assignment 1
*/

class I_Renderer
{
public:
    virtual ~I_Renderer() {}

    enum ViewMode
    {
        Wireframe,
        Face,
        Multicoloured
    };

    void setViewMode(ViewMode viewMode);
    // some sort of way to pass the blocks in
    void renderGameBlocks();
};
