#include "Shape.h"

class Triangle final : public Shape {
    public:
        explicit Triangle(double base, double height);
        ~Triangle();
        double get_area();
        double get_base(){
            return _base;
        }
        double get_height(){
            return _height;
        }
    private:
        void set_angles_number() override;
        void set_sides_number() override;
        double _base{0};
        double _height{0};
        
};