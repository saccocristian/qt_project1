#include "Shape.h"

class Triangle: public Shape {
    public:
        Triangle();
        ~Triangle();

    private:
        void setNumeroAngoli() override;
        void setNumeroLati() override;

};