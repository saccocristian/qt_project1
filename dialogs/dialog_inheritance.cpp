#include "dialog_inheritance.h"
#include "ui_d_inheritance.h"
#include "shapes/Shape.h"

class dialog_inheritance::dialog_inheritance_impl{

    public:
        int getCounter() const {
            return m_counter;
        }
        void setCounter(const int counter){
            m_counter = counter;
        }
        void incrementCounter(){
            m_counter +=1;
        }

        std::unique_ptr<DerivedClass> derivedClassObj;
        std::unique_ptr<Shape> shapeObj;
    private:
        int m_counter{0};


};

dialog_inheritance::dialog_inheritance(QWidget * parent) : QDialog(parent),m_impl(std::make_unique<dialog_inheritance_impl>()) {

        m_ui = std::make_unique<Ui::d_inheritance>();
        m_ui->setupUi(this);

        m_impl->derivedClassObj = std::make_unique<DerivedClass>();

        connect(m_ui->btn1,&QPushButton::clicked,this,[this](){
            m_impl->derivedClassObj->stampaPopup();
        });
        connect(m_ui->btn2,&QPushButton::clicked,this,[this](){
            m_impl->derivedClassObj->stampaPopup(m_impl->getCounter());
        });
        
        connect(m_ui->btn3,&QPushButton::clicked,this,[this](){
            m_impl->derivedClassObj->stampaPopup("Hello World");
        });
        connect(m_ui->btn4,&QPushButton::clicked,this,[this](){
            m_impl->derivedClassObj->stampaPopupNonVirtual();
        });
    //     connect(m_ui->shapeOkBtn,&QPushButton::clicked,this,[this](){

    //     // Rectangle - Triangle
    //     // static_cast e dynamic_cast

    //     QString s = this->m_ui->shapeComboBox->currentText();
    //     if(s == "Rectangle"){
    //             this->impl->shapeObj = std::make_unique<Rectangle>();
    //     } else if (s == "Triangle") {
    //             this->impl->shapeObj = std::make_unique<Triangle>();
    //     }

    //     // dynamic_cast: uno dei due puntatori appena realizzati sara' nullptr perche' non sara' in grado di fare il cast
    //     Rectangle* rectangle_dynamic = dynamic_cast<Rectangle*>(this->impl->shapeObj.get());
    //     Triangle * triangle_dynamic = dynamic_cast<Triangle*>(this->impl->shapeObj.get());

    //     Rectangle * rectangle_static = static_cast<Rectangle*>(this->impl->shapeObj.get());
    //     Triangle * triangle_static = static_cast<Triangle*>(this->impl->shapeObj.get());

    //     // dynamic check behaviour: controlla effettivamente se la risorsa a cui punta coincida con lo stesso tipo; altrimenti da' un nullptr
    //     if (rectangle_dynamic != nullptr) {
    //         qDebug() << "rectDynamic e' un ptr valido a un oggetto Rectangle.";
    //         qDebug() << "Rectangle::get_angles_number() -> " << rectangle_dynamic->get_angles_number();
    //     } else {
    //         qDebug() << "rectDynamic NON e' un ptr valido a un oggetto Rectangle.";
    //     }

    //     if (triangle_dynamic != nullptr) {
    //         qDebug() << "triangleDynamic e' un ptr valido a un oggetto Triangle.";
    //         qDebug() << "Triangle::get_angles_number() -> " << triangle_dynamic->get_angles_number();
    //     } else {
    //         qDebug() << "triangleDynamic NON e' un ptr valido a un oggetto Triangle.";
    //     }
    //     qDebug() << "-- static_cast: Comportamento anomalo a seguire, a puro scopo didattico";
    //     // static check behaviour -> i puntatori non sono nulli in caso di errato assegnamento, ma se provassi a chiamare un metodo
    //     // che non appartiene alla classe a cui pensa di puntare da' errore!
    //     if (rectangle_static != nullptr) {
    //         qDebug() << "rectangleStatic e' un ptr valido a un oggetto Rectangle.";
    //     } else {
    //         qDebug() << "rectangleStatic NON e' un ptr valido a un oggetto Rectangle.";
    //     }

    //     if (triangle_static != nullptr) {
    //         qDebug() << "triangle_static e' un ptr valido a un oggetto Triangle.";
    //     } else {
    //         qDebug() << "triangleStatic NON e' un ptr valido a un oggetto Triangle.";
    //     }

    //     qDebug() << "--- --- ---";
    // });
}

dialog_inheritance::~dialog_inheritance(){
    
}