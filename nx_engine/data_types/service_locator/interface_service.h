#pragma once
namespace service
{
    /**
     * \brief Interface for a service class to be used with the service locator
     */
    class interface_service
    {
    public:
        virtual ~interface_service() = default;
    protected:
        friend class locator;
        virtual void on_create(const locator* locator) {}
    };
}
