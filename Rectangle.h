#include "Shape.h"

class Rectangle : public Shape {
    public:
        Rectangle();
        ~ Rectangle();
    private:
        void setNumeroAngoli() override;
        void setNumeroLati() override;
};