#include "widgets.h"
#include "../ui/ui_widgets.h"

class widgets::widgets_impl{
    public:

    private:
        
};

widgets::widgets(QWidget * parent) : QDialog(parent),m_impl(std::make_unique<widgets_impl>()) {
    m_ui = std::make_unique<Ui::widgets>();
    m_ui->setupUi(this);
    
    connect(m_ui->buttonBox,&QDialogButtonBox::accepted,this,[this](){
        Widget_data data;

        data.line_edit = m_ui->lineEdit->text();

        if(m_ui->checkBox_A->isChecked()) {
            data.checkbox_list.append("Checkbox A - ");
        }
        if(m_ui->checkBox_B->isChecked()) {
            data.checkbox_list.append("Checkbox B -");
        }
        if(m_ui->checkBox_C->isChecked()) {
            data.checkbox_list.append("Checkbox C -");
        }

        if(m_ui->radioButton_1->isChecked()){
            data.radio_button = "radioButton1";
        }
        if(m_ui->radioButton_2->isChecked()){
            data.radio_button = "radioButton2";
        }
        data.combobox = m_ui->comboBox->currentText();
        emit send_data(data);
    });
}; // costruttore

widgets::~widgets(){

}