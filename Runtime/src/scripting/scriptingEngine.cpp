//
// Created by allos on 5/5/2024.
//

#include <iostream>
#include <fstream>
#include <cassert>
#include "scripting/scriptingEngine.h"
#include "mono/metadata/assembly.h"
#include "mono/metadata/attrdefs.h"



char *catos::ScriptingEngine::read_bytes(const std::string &filepath, uint32_t *outSize) {
    std::ifstream stream(filepath, std::ios::binary | std::ios::ate);

    if (!stream)
    {
        std::cerr << "Could not load file: " << filepath << "\n";
        return nullptr;
    }

    std::streampos end = stream.tellg();
    stream.seekg(0, std::ios::beg);
    uint32_t size = end - stream.tellg();

    if (size == 0)
    {
        std::cerr << "File size is 0 >:( \n";
        return nullptr;
    }

    char* buffer = new char[size];
    stream.read((char*)buffer, size);
    stream.close();

    *outSize = size;
    return buffer;
}


MonoAssembly *catos::ScriptingEngine::load_assembly(const std::string &assemblyPath) {
    uint32_t fileSize = 0;
    char* fileData = read_bytes(assemblyPath, &fileSize);

    // NOTE: We can't use this image for anything other than loading the assembly because this image doesn't have a reference to the assembly
    MonoImageOpenStatus status;
    MonoImage* image = mono_image_open_from_data_full(fileData, fileSize, 1, &status, 0);

    if (status != MONO_IMAGE_OK)
    {
        const char* errorMessage = mono_image_strerror(status);
        // Log some error message using the errorMessage data
        std::cerr << " ERR| " << errorMessage << "\n";
        return nullptr;
    }

    MonoAssembly* assembly = mono_assembly_load_from_full(image, assemblyPath.c_str(), &status, 0);
    mono_image_close(image);

    // Don't forget to free the file data
    delete[] fileData;

    return assembly;
}

void catos::ScriptingEngine::print_assembly_types(MonoAssembly *assembly) {
    MonoImage* image = mono_assembly_get_image(assembly);
    const MonoTableInfo* typeDefinitionsTable = mono_image_get_table_info(image, MONO_TABLE_TYPEDEF);
    int32_t numTypes = mono_table_info_get_rows(typeDefinitionsTable);

    for (int32_t i = 0; i < numTypes; i++)
    {
        uint32_t cols[MONO_TYPEDEF_SIZE];
        mono_metadata_decode_row(typeDefinitionsTable, i, cols, MONO_TYPEDEF_SIZE);

        const char* nameSpace = mono_metadata_string_heap(image, cols[MONO_TYPEDEF_NAMESPACE]);
        const char* name = mono_metadata_string_heap(image, cols[MONO_TYPEDEF_NAME]);

        printf("%s.%s\n", nameSpace, name);
    }
}




void catos::ScriptingEngine::init() {

    _context = new ScriptContext;


    init_mono();
}

void catos::ScriptingEngine::clean_up() {

    mono_jit_cleanup(_context->_rootDomain);
    delete _context;
}

void catos::ScriptingEngine::init_mono() {
    mono_set_assemblies_path("../../Thirdparty/Mono/lib/");

    MonoDomain* rootDomain = mono_jit_init("CatosSharpRuntime");
    if (rootDomain == nullptr) {
        std::cerr << "Could not initialize CatosSharpRuntime.\n";
        return;
    }

    _context->_rootDomain = rootDomain;

    //Create an App domain;                                         /// Mono is a little cry baby so we have to use strdup here.
    _context->_appDomain = mono_domain_create_appdomain(strdup("MyAppDomain"), nullptr);
    mono_domain_set(_context->_appDomain, true);

    uint32_t size;

    _context->_mainAssembly = load_assembly(R"(C:\Users\allos\source\Catos\Resources\Catos\CatosRuntime\bin\Debug\net8.0\CatosRuntime.dll)");

    print_assembly_types(_context->_mainAssembly);

    MonoClass* testingClass = get_class_in_assembly(_context->_mainAssembly, "", "CSharpTesting");

    if (testingClass != nullptr) {
        std::cout << "Successfully got class from assembly\n";
    } else  {
        return;
    }

    //New instance of the test class
    MonoObject* testInstance = instantiate_class("", "CSharpTesting");

    MonoClassField* floatField = mono_class_get_field_from_name(testingClass, "MyPublicFloatVar");
    uint8_t floatFieldAccessibility = get_field_accessibility(floatField);

    if (floatFieldAccessibility & (uint8_t)FieldAccessibility::Public)
    {
        std::cout << "We good its public :) \n";

        float value;
        mono_field_get_value(testInstance, floatField, &value);

        value += 10.0f;
        mono_field_set_value(testInstance, floatField, &value);
    }

    MonoProperty* nameProperty = mono_class_get_property_from_name(testingClass, "Name");

    uint8_t namePropertyAccessibility = get_property_accessbility(nameProperty);

    if (namePropertyAccessibility & (uint8_t)FieldAccessibility::Public)
    {
        std::cout << "We good its public :) \n";
        MonoString* nameValue = (MonoString*)mono_property_get_value(nameProperty, testInstance, nullptr, nullptr);
        std::string nameStr = mono_string_to_string(nameValue);

    // Modify and assign the value back to the property by invoking the setter method
        nameStr += ", World!";
        nameValue = mono_string_new(_context->_appDomain, nameStr.c_str());
        mono_property_set_value(nameProperty, testInstance, (void**)&nameValue, nullptr);

    }


    call_print_method(testInstance);
}

MonoClass *catos::ScriptingEngine::get_class_in_assembly(MonoAssembly *assembly, const char *namespaceName,
                                                         const char *className) {

    MonoImage* image = mono_assembly_get_image(assembly);
    MonoClass* klass = mono_class_from_name(image, namespaceName, className);

    if (klass == nullptr) {
        std::cerr << "Error: Could not find class: " << className << " In namespace:  " << namespaceName << "\n";
        return nullptr;
    }

    return klass;
}

void catos::ScriptingEngine::call_print_method(MonoObject *objectInstance) {
    MonoClass* instanceClass = mono_object_get_class(objectInstance);


    //get a ref to the method.
    MonoMethod* method = mono_class_get_method_from_name(instanceClass, "PrintFloatVar", 0);

    if (method == nullptr) {
        std::cerr << "INVALID METHOD\n";
        return;
    }

    MonoObject* exception = nullptr;

    mono_runtime_invoke(method, objectInstance, nullptr, &exception);

    if (exception != nullptr) {
        std::cerr << "Exception when running method!\n";
    }

}

MonoObject *catos::ScriptingEngine::instantiate_class(const char *namespaceName, const char *className) {
    MonoClass* testingClass = get_class_in_assembly(_context->_mainAssembly, namespaceName, className);

    MonoObject* classInstance = mono_object_new(_context->_appDomain, testingClass);

    if (classInstance == nullptr) {

        std::cerr << "Could not create instance of " << className << "\n";

        return nullptr;
    }

    mono_runtime_object_init(classInstance);

    return classInstance;
}

uint8_t catos::ScriptingEngine::get_field_accessibility(MonoClassField *field) {
    uint8_t accessibility = (uint8_t)FieldAccessibility::None;
    uint32_t accessFlag = mono_field_get_flags(field) & MONO_FIELD_ATTR_FIELD_ACCESS_MASK;

    switch (accessFlag) {
        case MONO_FIELD_ATTR_PRIVATE:
        {
            accessibility = (uint8_t) FieldAccessibility::Private;
            break;
        }
        case MONO_FIELD_ATTR_FAM_AND_ASSEM:
        {
            accessibility |= (uint8_t)FieldAccessibility::Protected;
            accessibility |= (uint8_t)FieldAccessibility::Internal;
            break;
        }
        case MONO_FIELD_ATTR_ASSEMBLY:
        {
            accessibility = (uint8_t)FieldAccessibility::Internal;
            break;
        }
        case MONO_FIELD_ATTR_FAMILY:
        {
            accessibility = (uint8_t)FieldAccessibility::Protected;
            break;
        }
        case MONO_FIELD_ATTR_FAM_OR_ASSEM:
        {
            accessibility |= (uint8_t)FieldAccessibility::Private;
            accessibility |= (uint8_t)FieldAccessibility::Protected;
            break;
        }
        case MONO_FIELD_ATTR_PUBLIC:
        {
            accessibility = (uint8_t)FieldAccessibility::Public;
            break;
        }
    }

    return accessibility;
}

uint8_t catos::ScriptingEngine::get_property_accessbility(MonoProperty *property) {
    uint8_t  accessibility = (uint8_t)FieldAccessibility::None;

    MonoMethod * propertyGetter = mono_property_get_get_method(property);
    if (propertyGetter != nullptr) {
        uint32_t  accessFlag = mono_method_get_flags(propertyGetter, nullptr) & MONO_METHOD_ATTR_ACCESS_MASK;

        switch (accessFlag)
        {
            case MONO_FIELD_ATTR_PRIVATE:
            {
                accessibility = (uint8_t)FieldAccessibility::Private;
                break;
            }
            case MONO_FIELD_ATTR_FAM_AND_ASSEM:
            {
                accessibility |= (uint8_t)FieldAccessibility::Protected;
                accessibility |= (uint8_t)FieldAccessibility::Internal;
                break;
            }
            case MONO_FIELD_ATTR_ASSEMBLY:
            {
                accessibility = (uint8_t)FieldAccessibility::Internal;
                break;
            }
            case MONO_FIELD_ATTR_FAMILY:
            {
                accessibility = (uint8_t)FieldAccessibility::Protected;
                break;
            }
            case MONO_FIELD_ATTR_FAM_OR_ASSEM:
            {
                accessibility |= (uint8_t)FieldAccessibility::Private;
                accessibility |= (uint8_t)FieldAccessibility::Protected;
                break;
            }
            case MONO_FIELD_ATTR_PUBLIC:
            {
                accessibility = (uint8_t)FieldAccessibility::Public;
                break;
            }
        }
    }

    //Get a ref to the prop setter method
    MonoMethod* propertySetter = mono_property_get_set_method(property);
    if (propertySetter != nullptr)
    {
        // Extract the access flags from the setters flags
        uint32_t accessFlag = mono_method_get_flags(propertySetter, nullptr) & MONO_METHOD_ATTR_ACCESS_MASK;
        if (accessFlag != MONO_FIELD_ATTR_PUBLIC)
            accessibility = (uint8_t)FieldAccessibility::Private;
    }
    else
    {
        accessibility = (uint8_t)FieldAccessibility::Private;
    }

    return accessibility;
}

bool catos::ScriptingEngine::check_mono_error(MonoError &error) {
    bool hasError = !mono_error_ok(&error);
    if (hasError) {
        unsigned short errorCode = mono_error_get_error_code(&error);
        const char* errorMessage = mono_error_get_message(&error);

        std::cerr << "Mono Error: " << errorCode << "\n";
        std::cerr << "Message: " << errorMessage << "\n";
        mono_error_cleanup(&error);

    }// ruh roh

    return hasError;
}

std::string catos::ScriptingEngine::mono_string_to_string(MonoString *monoString) {
    if (monoString == nullptr || mono_string_length(monoString) == 0 ) {
        return "";
    }

    MonoError error;
    char* utf8 = mono_string_to_utf8_checked(monoString, &error);
    if (check_mono_error(error)) {
        return "";
    }
    std::string result(utf8);
    mono_free(utf8);

    return result;
}
