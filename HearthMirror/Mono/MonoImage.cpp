//
//  MonoImage.cpp
//  MonoReader
//
//  Created by Istvan Fehervari on 22/12/2016.
//  Copyright © 2016 com.ifehervari. All rights reserved.
//

#include "MonoImage.hpp"
#include "offsets.h"

namespace hearthmirror {
    
    MonoImage::MonoImage(mach_port_t task, uint32_t pImage) : _task(task), _pImage(pImage) {
    
        this->LoadClasses();
    }

    MonoImage::~MonoImage() {
        // free all classes
        for (auto it = _classes.begin(); it != _classes.end(); it++) {
            delete it->second;
        }
    }

    MonoClass* MonoImage::operator[](const std::string& key) {
        return this->_classes.at(key);
    }

    void MonoImage::LoadClasses() {
    
        uint32_t ht = _pImage + kMonoImageClassCache;
        uint32_t size = ReadInt32(_task, ht + kMonoInternalHashTableSize);
        //uint32_t entries = ReadInt32(_task, ht + kMonoInternalHashTableNum_entries);
        uint32_t table = ReadUInt32(_task, ht + kMonoInternalHashTableTable);

        for(uint32_t i = 0; i < size; i++) {
            uint32_t pClass = ReadUInt32(_task, table + 4*i);
            while (pClass != 0) {
                MonoClass* klass = new MonoClass(_task, pClass);
                std::string cfname = klass->getFullName();
                //printf("%s\n",cfname.c_str());
                _classes[cfname] = klass;

                pClass = ReadUInt32(_task, pClass + kMonoClassNextClassCache);
            }
        }
    
    }

} // namespace HSReader
