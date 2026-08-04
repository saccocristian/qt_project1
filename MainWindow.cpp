#include "MainWindow.h"
#include "ui/ui_MainWindow.h"

#include "dialogs/initial.h"
#include "dialogs/inheritance.h"
#include "dialogs/misc.h"
#include "dialogs/multithreading.h"
#include "dialogs/widgets.h"
#include "dialogs/templates.h"

#include "threading/MyThread.h"
#include "threading/Worker.h"

#include "shapes/Rectangle.h"
#include "shapes/Triangle.h"

#include "qt_classes/MyBtn.h"
#include "qt_classes/MyDialog.h"

#include <QDebug>
#include <QWidget>
#include <QThread>
#include <QPointer>
#include <QMessageBox>
#include <QFileDialog>
#include <QImage>

class MainWindow::MainWindowImpl {

    public:
        QPointer<MyThread> thread;
        QPointer<Worker> worker;

        QPointer<MyThread> counterThread1;
        QPointer<MyThread> counterThread2;
        QPointer<MyThread> counterThread3;

        QPointer<Worker> counterWorker1;
        QPointer<Worker> counterWorker2;
        QPointer<Worker> counterWorker3;

        std::unique_ptr<BaseClass> derivedClassObj;

        std::unique_ptr<Shape> shapeObj;
    private:
        int m_threadCounter1{0};
        int m_threadCounter2{0};
        int m_threadCounter3{0};
};

// Costruttore
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), impl(std::make_unique<MainWindowImpl>()) {

    m_ui = std::make_unique<Ui::MainWindow>();
    m_ui->setupUi(this);

    setWindowTitle("Qt Test Dashboard");
    // resize(800,300);

    connect(m_ui->btn1,&QPushButton::clicked,this,&MainWindow::open_initial_dialog);
    connect(m_ui->btn2,&QPushButton::clicked,this,&MainWindow::open_widgets_dialog);
    connect(m_ui->btn3,&QPushButton::clicked,this,&MainWindow::open_multithreading_dialog);
    connect(m_ui->btn4,&QPushButton::clicked,this,&MainWindow::open_inheritance_dialog);
    connect(m_ui->btn5,&QPushButton::clicked,this,&MainWindow::open_misc_dialog);
    connect(m_ui->templates_button, &QPushButton::clicked, this, &MainWindow::open_template_dialog);

    connect(m_ui->closeBtn,&QPushButton::clicked,this,&QWidget::close);
    connect(m_ui->actionQuit,&QAction::triggered,this,&QWidget::close);
} // costruttore

// Distruttore
MainWindow::~MainWindow() {
    qDebug() << "~ QWidget : MainWindow";
}

void MainWindow::receive_data(const Widget_data &data){
    m_ui->lineEditValueLabel->setText(data.line_edit);
    m_ui->checkboxesValueLabel->setText(data.checkbox_list);
    m_ui->radioButtonValueLabel->setText(data.radio_button);
    m_ui->comboboxValueLabel->setText(data.combobox);
}

void MainWindow::open_template_dialog(){
    std::unique_ptr<templates> dialog = std::make_unique<templates>();
    dialog->exec();
}

void MainWindow::open_initial_dialog(){
    std::unique_ptr<initial> dialog = std::make_unique<initial>(this);
    dialog->exec();
}
void MainWindow::open_multithreading_dialog(){
    std::unique_ptr<multithreading> dialog = std::make_unique<multithreading>(this);
    dialog->exec();
}
void MainWindow::open_widgets_dialog(){
    std::unique_ptr<widgets> dialog = std::make_unique<widgets>(this);
    connect(dialog.get(),&widgets::send_data,this,&MainWindow::receive_data);

    dialog->exec();
}
void MainWindow::open_misc_dialog(){
    std::unique_ptr<misc> dialog = std::make_unique<misc>(this);
    dialog->exec();
}

void MainWindow::open_inheritance_dialog(){
    std::unique_ptr<inheritance> dialog = std::make_unique<inheritance>(this);
    dialog->exec();
}