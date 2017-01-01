//
//  MonoClass.hpp
//  MonoReader
//
//  Created by Istvan Fehervari on 22/12/2016.
//  Copyright © 2016 com.ifehervari. All rights reserved.
//

#ifndef MonoClass_hpp
#define MonoClass_hpp

#include <string>
#include <vector>

#include "../memhelper.h"
#include "MonoType.hpp"
#include "MonoClassField.hpp"

namespace hearthmirror {

    class MonoClass {
    public:
        MonoClass();
        MonoClass(HANDLE task, uint32_t pClass);
        MonoClass(const MonoClass* other);
        ~MonoClass();
        
        std::string getName();
        std::string getNameSpace();
        std::string getFullName();
        
        MonoClass* getNestedIn();
        uint32_t getVTable();
        
        bool isValueType();
        bool isEnum();
        uint32_t size();
        
        MonoClass* getParent();
        MonoType* byValArg();
        
        uint32_t getNumFields();
        std::vector<MonoClassField*> getFields();
        
        MonoValue operator[](const std::string& key);
        
    private:
		HANDLE _task;
        uint32_t _pClass;
    };

} // HSReader namespace

#endif /* MonoClass_hpp */
