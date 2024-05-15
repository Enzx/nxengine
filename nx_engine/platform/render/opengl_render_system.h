#pragma once
#include "../../render/render_system.h"

class opengl_render_system final : public render_system
{
public:
    ~opengl_render_system() override;

protected:
    void on_create(const service::locator* locator) override;
    void update() override;

public:
    
};
