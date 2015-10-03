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
        MultiColoured
    };

    virtual void setViewMode(ViewMode viewMode) = 0;
};
