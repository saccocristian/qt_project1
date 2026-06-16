#include "FooClass.h"

class FooClass::FooClassImpl {
    public:
        void printCounter(){
            qDebug() << "Hello PIMPL!";
        }
};

FooClass::FooClass() : fooClassImpl(std::make_unique<FooClassImpl>()) {}

FooClass::~FooClass() = default;