#include "Shape.h"

class Rectangle final : public Shape {
    public:
        explicit Rectangle(double base, double height);
        ~Rectangle();
        double get_base(){
            return _base;
        }
        double get_height(){
            return _height;
        }
        double get_area() override;
    private:
        void set_angles_number() override;
        void set_sides_number() override;

        double _base{0};
        double _height{0};
};
