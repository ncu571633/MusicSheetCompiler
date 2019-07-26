#include "GlobalSetting.hpp"

GlobalSetting::GlobalSetting()
{
    instance = nullptr;
    uniquePtrInstance = nullptr;
}

GlobalSetting::getInstance()
{
    if (!this->instance)
    {
        this->instance = new GlobalSetting();
    }
    return this->instance;
}

GlobalSetting::getUniquePtrInstance()
{
    if (!this->instance)
    {
        this->uniquePtrInstance = std::unique_ptr<GlobalSetting>();
    }
    return this->uniquePtrInstance;
}
