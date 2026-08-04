
#pragma once
#include <QDialog>

namespace Ui{
    class templates;
}

class templates: public QDialog {
    Q_OBJECT
    public:
        explicit templates(QWidget *parent = nullptr);
        ~templates();
    
    private:
        class templates_impl;
        std::unique_ptr<templates_impl> m_impl;
        std::unique_ptr<Ui::templates> m_ui;
    private slots:
        void create_template_obj();
};