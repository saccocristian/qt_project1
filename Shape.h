#pragma once

class Shape {
    public:
    virtual ~Shape();

    virtual void set_angles_number() = 0;
    int get_angles_number() const;

    virtual void set_sides_number() = 0;
    int get_sides_number() const;

    protected:
        int m_angles_number;
        int m_sides_number;

};