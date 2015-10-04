#pragma once

#include <QObject>
#include "gmock/gmock.h"
#include "view/I_Renderer.h"

class MockRenderer : public QObject, public I_Renderer
{
    Q_OBJECT
public:
    MockRenderer();
    virtual ~MockRenderer();

    MOCK_METHOD1(setViewMode, void(ViewMode viewmode));

    MOCK_METHOD0(resetViewSlot, void());

public slots:
    void resetView();
};
