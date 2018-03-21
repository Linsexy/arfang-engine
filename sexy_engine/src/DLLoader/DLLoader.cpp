//
// Created by mymy on 04/01/18.
//

#ifdef WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif

#include <algorithm>
#include "DLLoader/DLLoader.hpp"
#include "DLLoader/DLErrors.hpp"

void    utils::DLLoader::dlOpen(std::string const &fileName)
{
#ifdef WIN32
    HINSTANCE dlHandle;
    dlHandle = LoadLibrary(fileName.c_str());
    if (dlHandle == nullptr)
        throw DLErrors("This dll does not exist.");
#else
    void *dlHandle;
    dlHandle = dlopen(fileName.c_str(), RTLD_NOW);
    if (dlHandle == nullptr)
        throw DLErrors(dlerror());
#endif
    this->_dlHandles.emplace_back(std::make_pair(fileName, dlHandle));
}

void    utils::DLLoader::dlClose(std::string const &fileName)
{
    auto dlHandle = std::find_if(_dlHandles.begin(), _dlHandles.end(),
                                 [fileName](const auto &elem){ return elem.first == fileName; });
    if (dlHandle != _dlHandles.end())
    {
#ifdef WIN32
        FreeLibrary(dlHandle->second);
#else
        dlclose(dlHandle->second);
#endif
        std::remove_if(_dlHandles.begin(), _dlHandles.end(),
                       [fileName](const auto &elem) { return elem.first == fileName; });
    }
    else
        throw DLErrors("This dll was never opened.");
}

void    utils::DLLoader::dlCloseAll() noexcept
{
    for (auto &dlHandle : _dlHandles)
    {
#ifdef WIN32
        FreeLibrary(dlHandle.second);
#else
        dlclose(dlHandle.second);
#endif
    }
    _dlHandles.clear();
}

void    *utils::DLLoader::dlSym(std::string const &fileName, std::string const &sym) const
{
    auto dlHandle = std::find_if(_dlHandles.begin(), _dlHandles.end(),
                                [fileName](const auto &elem) { return elem.first == fileName; });
    if (dlHandle != _dlHandles.end())
    {
#ifdef WIN32
        auto symAdr = GetProcAddress(dlHandle->second, sym.c_str());
        if (symAdr == nullptr)
            throw DLErrors("Symbol does not exists.");
#else
        auto symAdr = (dlsym(dlHandle->second, sym.c_str()));
        if (symAdr == nullptr)
            throw DLErrors(dlerror());
#endif
        return (symAdr);
    }
    else
        throw DLErrors("This dll was never opened.");
}
