#pragma once
#include <QDialog>
#include <QPointer>
#include <QCheckBox>
#include <QRadioButton>
#include <QVector>

struct Widget_data {
    QString line_edit;
    QString checkbox_list;
    QString radio_button;
    QString combobox;
};

namespace Ui{
    class widgets;
}

class widgets : public QDialog{
    Q_OBJECT

    signals:
        void send_data(const Widget_data &data);

    public:
        explicit widgets(QWidget * parent = nullptr);
        ~widgets();
    private:
        class widgets_impl;
        std::unique_ptr<widgets_impl> m_impl;
        std::unique_ptr<Ui::widgets> m_ui;
};