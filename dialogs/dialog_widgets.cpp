#include "dialog_widgets.h"
#include "ui_d_widgets.h"

class dialog_widgets::dialog_widgets_impl{
    public:

    private:
        
};

dialog_widgets::dialog_widgets(QWidget * parent) : QDialog(parent),m_widgets_impl(std::make_unique<dialog_widgets_impl>()) {
    m_widgets_ui = std::make_unique<Ui::d_widgets>();
    m_widgets_ui->setupUi(this);
    
    connect(m_widgets_ui->buttonBox,&QDialogButtonBox::accepted,this,[this](){
        Widget_dialog_data data;

        data.line_edit = m_widgets_ui->lineEdit->text();

        if(m_widgets_ui->checkBox_A->isChecked()) {
            data.checkbox_list.append("Checkbox A - ");
        }
        if(m_widgets_ui->checkBox_B->isChecked()) {
            data.checkbox_list.append("Checkbox B -");
        }
        if(m_widgets_ui->checkBox_C->isChecked()) {
            data.checkbox_list.append("Checkbox C -");
        }

        if(m_widgets_ui->radioButton_1->isChecked()){
            data.radio_button = "radioButton1";
        }
        if(m_widgets_ui->radioButton_2->isChecked()){
            data.radio_button = "radioButton2";
        }
        data.combobox = m_widgets_ui->comboBox->currentText();
        emit send_data(data);
    });
}; // costruttore

dialog_widgets::~dialog_widgets(){

}