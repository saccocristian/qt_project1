#include "Shape.h"

class Rectangle final : public Shape {
    public:
        explicit Rectangle();
        ~Rectangle();
        
    private:
        void set_angles_number() override;
        void set_sides_number() override;
};
