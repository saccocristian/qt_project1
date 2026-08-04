#pragma once

class Shape {
    public:
    virtual ~Shape();

    virtual void set_angles_number() = 0;
    int get_angles_number() const;
    virtual void set_sides_number() = 0;
    int get_sides_number() const;
    virtual double get_area() = 0;

    template <typename T1, typename T2> // sono tutti i tipi che usero' con la funzione
    static auto getLargerArea(T1 obj1, T2 obj2) {
        if(obj1->get_area() > obj2->get_area()){
            return obj1->get_area();
        } else {
            return obj2->get_area();
        }
    }
    protected:
        int m_angles_number{0};
        int m_sides_number{0};

};