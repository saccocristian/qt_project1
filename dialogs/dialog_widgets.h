#pragma once
#include <QDialog>
#include <QPointer>
#include <QCheckBox>
#include <QRadioButton>
#include <QVector>

struct Widget_dialog_data {
    QString line_edit;
    QString checkbox_list;
    QString radio_button;
    QString combobox;
};

namespace Ui{
    class d_widgets;
}

class dialog_widgets : public QDialog{
    Q_OBJECT

    signals:
        void send_data(const Widget_dialog_data &data);

    public:
        explicit dialog_widgets(QWidget * parent = nullptr);
        ~dialog_widgets();
    private:
        class dialog_widgets_impl;
        std::unique_ptr<dialog_widgets_impl> m_widgets_impl;
        std::unique_ptr<Ui::d_widgets> m_widgets_ui;
};