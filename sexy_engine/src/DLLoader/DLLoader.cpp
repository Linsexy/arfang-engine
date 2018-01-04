//
// Created by mymy on 04/01/18.
//

#include "DLLoader/DLLoader.hpp"
#include <dlfcn.h>

void    Sex::DLLoader::dlOpen(std::string const &fileName)
{
    void *dlHandle;

    dlHandle = dlopen(fileName.c_str(), RTLD_NOW);

}
