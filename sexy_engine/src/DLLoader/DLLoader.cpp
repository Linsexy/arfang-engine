//
// Created by mymy on 04/01/18.
//

#include <dlfcn.h>
#include <algorithm>
#include "DLLoader/DLLoader.hpp"
#include "DLLoader/DLErrors.hpp"

void    Sex::DLLoader::dlOpen(std::string const &fileName)
{
    void *dlHandle;

    dlHandle = dlopen(fileName.c_str(), RTLD_NOW);
    if (dlHandle == nullptr)
        throw DLErrors(dlerror());
    this->_dlHandles.emplace_back(std::make_pair(fileName, dlHandle));
}

void    Sex::DLLoader::dlClose(std::string const &fileName)
{
    auto dlHandle = std::find_if(_dlHandles.begin(), _dlHandles.end(),
                                 [fileName](const auto &elem){ return elem.first == fileName; });
    if (dlHandle != _dlHandles.end())
    {
        dlclose(dlHandle->second);
        std::remove_if(_dlHandles.begin(), _dlHandles.end(),
                       [fileName](const auto &elem) { return elem.first == fileName; });
    }
    else
        throw DLErrors("This dll was never opened.");
}

void    Sex::DLLoader::dlCloseAll() noexcept
{
    for (auto &dlHandle : _dlHandles)
    {
        dlclose(dlHandle.second);
    }
    _dlHandles.clear();
}

void    *Sex::DLLoader::dlSym(std::string const &fileName, std::string const &sym) const
{
    auto dlHandle = std::find_if(_dlHandles.begin(), _dlHandles.end(),
                                [fileName](const auto &elem) { return elem.first == fileName; });
    if (dlHandle != _dlHandles.end())
    {
        auto symAdr = (dlsym(dlHandle->second, sym.c_str()));
        if (symAdr == nullptr)
            throw DLErrors(dlerror());
        return (symAdr);
    }
    else
        throw DLErrors("This dll was never opened.");
}