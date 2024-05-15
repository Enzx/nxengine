#pragma once
#include "../data_types/service_locator/interface_service.h"

class render_system :  public service::interface_service
{
public:
    render_system(const render_system& other) = delete;
    render_system(render_system&& other) noexcept = delete;
    render_system& operator=(const render_system& other) = delete;
    render_system& operator=(render_system&& other) noexcept = delete;
    ~render_system() override;

protected:
    void on_create(const service::locator* locator) override;
    virtual void update() = 0;

    
};
