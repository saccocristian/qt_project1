#include "MainWindow.h"

#include "ui/ui_MainWindow.h"

#include "dialogs/dialog_initial.h"
#include "dialogs/dialog_inheritance.h"
#include "dialogs/dialog_misc.h"
#include "dialogs/dialog_multithreading.h"
#include "dialogs/dialog_widgets.h"
// -----------------

#include <QDebug>
#include <QWidget>
#include <QThread>
#include <QPointer>
#include <QMessageBox>
#include <QFileDialog>
#include <QImage>

#include "threading/MyThread.h"
#include "threading/Worker.h"

#include "shapes/Rectangle.h"
#include "shapes/Triangle.h"

#include "qt_classes/MyBtn.h"
#include "qt_classes/MyDialog.h"

// Struttura file: impl - costruttore - distruttore - funzioni

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

    connect(m_ui->btn1,&QPushButton::clicked,this,[this](){
        std::unique_ptr<dialog_initial> dialog = std::make_unique<dialog_initial>(this);
        dialog->exec();
    });

    connect(m_ui->btn2,&QPushButton::clicked,this,[this](){
        std::unique_ptr<dialog_widgets> dialog = std::make_unique<dialog_widgets>(this);
        connect(dialog.get(),&dialog_widgets::send_data,this,&MainWindow::receive_data);

        dialog->exec();
    });

    connect(m_ui->btn3,&QPushButton::clicked,this,[this](){
        std::unique_ptr<dialog_multithreading> dialog = std::make_unique<dialog_multithreading>(this);
        dialog->exec();
    });
    connect(m_ui->btn4,&QPushButton::clicked,this,[this](){
        std::unique_ptr<dialog_inheritance> dialog = std::make_unique<dialog_inheritance>(this);
        dialog->exec();
    });
    
    connect(m_ui->btn5,&QPushButton::clicked,this,[this](){
        std::unique_ptr<dialog_misc> dialog = std::make_unique<dialog_misc>(this);
        dialog->exec();
    });


    connect(m_ui->closeBtn,&QPushButton::clicked,this,&QWidget::close);
    connect(m_ui->actionQuit,&QAction::triggered,this,&QWidget::close);
} // costruttore

// Distruttore
MainWindow::~MainWindow() {
    qDebug() << "~ QWidget : MainWindow";
    emit cleanup();
}

void MainWindow::receive_data(const Widget_dialog_data &data){
    m_ui->lineEditValueLabel->setText(data.line_edit);
    m_ui->checkboxesValueLabel->setText(data.checkbox_list);
    m_ui->radioButtonValueLabel->setText(data.radio_button);
    m_ui->comboboxValueLabel->setText(data.combobox);
}