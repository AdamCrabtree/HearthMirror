//
//  MonoStruct.hpp
//  MonoReader
//
//  Created by Istvan Fehervari on 23/12/2016.
//  Copyright © 2016 com.ifehervari. All rights reserved.
//

#ifndef MonoStruct_hpp
#define MonoStruct_hpp

#include "machhelper.h"
#include <map>
#include <string>
#include "MonoType.hpp"

namespace hearthmirror {
    
    class MonoClass;
    
    class MonoStruct {
    public:
        MonoStruct();
        MonoStruct(mach_port_t task, MonoClass* mClass, uint32_t pStruct);
        ~MonoStruct();
        
        uint32_t pStruct;
        MonoClass* monoClass;
        
        std::map<std::string, MonoValue> getFields();
        MonoValue operator[](const std::string& key);
        
    private:
        mach_port_t _task;
        
    };
    
} // end namespace

#endif /* MonoStruct_hpp */
