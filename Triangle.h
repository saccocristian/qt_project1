#include "Shape.h"

class Triangle final : public Shape {
    public:
        explicit Triangle();
        ~Triangle();

    private:
        void set_angles_number() override;
        void set_sides_number() override;

};