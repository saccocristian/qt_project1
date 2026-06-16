#pragma once

#include <memory>
#include <QDebug>

class FooClass {

    public:
        FooClass();
        ~FooClass();
        void printCounter();

    private:
        class FooClassImpl;
        std::unique_ptr <FooClassImpl> fooClassImpl;
};