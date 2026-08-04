#include "templates.h"
#include "../ui/ui_templates.h"

#include "templates/template_class.h"
#include "templates/template_a.h"
#include "templates/template_b.h"

#include <iostream>

class templates::templates_impl{
    
};

templates::templates(QWidget* parent) : QDialog(parent) {
    m_ui = std::make_unique<Ui::templates>();
    m_ui->setupUi(this);
    connect(m_ui->create_obj_button, &QPushButton::clicked, this,&templates::create_template_obj);
}
templates::~templates(){

}
void templates::create_template_obj(){
    template_a t_a;
    template_class<template_a>::print_example(t_a);
    template_b t_b;
    template_class<template_b>::print_example(t_b);
    // template_class<template_a>::print_example(t_b);
    // riga sopra fatta per prova, errore a compile time

}
