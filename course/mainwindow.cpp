#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "draw.h"
#include "commands.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    shared_ptr<Camera> cam = make_shared<Camera>(Camera(Point_3d(300,300,-100)));
    shared_ptr<Position> pos = make_shared<Position>(Position(Point_3d(300,300,-100)));
    facade.get_scene_container().add_object(cam);
    facade.get_scene_container().add_position(pos);
    facade.get_scene_container().set_current_camera(cam);

    shared_ptr<Ground> ground = make_shared<Ground>(Ground(Point_3d(-300,200,0),Point_3d(500,200,0),Point_3d(500,200,600),Point_3d(-300,200,600)));
    pos = make_shared<Position>(Position(Point_3d(300,200,300)));
    facade.get_scene_container().add_object(ground);
    facade.get_scene_container().add_position(pos);
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setClipRect(0, 0, width() - 320, height());
    for (int i = 0; i < 1000; i++) {

    }
    Object *cam = facade.get_scene_container().get_current_camera()->get();
    if (facade.get_scene_container().get_objects().size() > 0) {
        DrawQt drawer(p, *(Camera*)cam);
        Draw_command command(drawer, facade.get_scene_container().get_begin_object(), facade.get_scene_container().get_end_object());
        command.call(facade);
    }
}

void MainWindow::on_pushButton_clicked()
{
    QString str = ui->lineEdit_2->text();
    if (str.toInt() == 0 && QString::compare(str, "0") != 0) {
        QMessageBox::critical(this,"ошибка","Неверно введены данные");
        return;
    }
    double dx = str.toInt();

    str = ui->lineEdit->text();
    if (str.toInt() == 0 && QString::compare(str, "0") != 0) {
        QMessageBox::critical(this,"ошибка","Неверно введены данные");
        return;
    }
    double dy = str.toInt();

    str = ui->lineEdit_10->text();
    if (str.toInt() == 0 && QString::compare(str, "0") != 0) {
        QMessageBox::critical(this,"ошибка","Неверно введены данные");
        return;
    }
    double dz = str.toInt();

    Offset_command command(dx, dy, dz, facade.get_scene_container().get_begin_object(), facade.get_scene_container().get_end_object(), facade.get_scene_container().get_begin_position());
    command.call(facade);
    repaint();
}

void MainWindow::on_pushButton_2_clicked()
{
    QString str = ui->lineEdit_11->text();
    if (fabs(str.toDouble()) < 0.00001 && QString::compare(str, "0") != 0) {
        QMessageBox::critical(this,"ошибка","Неверно введены данные");
        return;
    }
    double k = str.toDouble();

    Scale_command command(k, facade.get_scene_container().get_begin_object(), facade.get_scene_container().get_end_object(), facade.get_scene_container().get_begin_position());
    command.call(facade);
    repaint();
}

void MainWindow::on_pushButton_3_clicked()
{
    QString str = ui->lineEdit_7->text();
    if (str.toInt() == 0 && QString::compare(str, "0") != 0) {
        QMessageBox::critical(this,"ошибка","Неверно введены данные");
        return;
    }
    double anx = str.toInt();

    Rotate_x_command command_x(anx, facade.get_scene_container().get_begin_object(), facade.get_scene_container().get_end_object(), facade.get_scene_container().get_begin_position());
    command_x.call(facade);

    str = ui->lineEdit_8->text();
    if (str.toInt() == 0 && QString::compare(str, "0") != 0) {
        QMessageBox::critical(this,"ошибка","Неверно введены данные");
        return;
    }
    double any = str.toInt();

    Rotate_y_command command_y(any, facade.get_scene_container().get_begin_object(), facade.get_scene_container().get_end_object(), facade.get_scene_container().get_begin_position());
    command_y.call(facade);

    str = ui->lineEdit_9->text();
    if (str.toInt() == 0 && QString::compare(str, "0") != 0) {
        QMessageBox::critical(this,"ошибка","Неверно введены данные");
        return;
    }
    double anz = str.toInt();

    Rotate_z_command command_z(anz, facade.get_scene_container().get_begin_object(), facade.get_scene_container().get_end_object(), facade.get_scene_container().get_begin_position());
    command_z.call(facade);

    repaint();
}

void MainWindow::on_pushButton_4_clicked()
{
    QString filename = QFileDialog::getOpenFileName(nullptr, "Open Dialog", "", "*.txt");
    const char *f = filename.toStdString().c_str();

    File_loader file_loader(f);
    Model_builder builder;
    Load_command command(file_loader, builder);
    command.call(facade);

    repaint();
}
//go
void MainWindow::on_pushButton_5_clicked()
{
}

//+
void MainWindow::on_pushButton_6_clicked()
{
    Scale_camera_command command(2, facade.get_scene_container().get_current_camera());
    command.call(facade);

    repaint();
}
//-
void MainWindow::on_pushButton_7_clicked()
{
    Scale_camera_command command(0.5, facade.get_scene_container().get_current_camera());
    command.call(facade);

    repaint();
}
//right
void MainWindow::on_pushButton_9_clicked()
{
    Rotate_camera_command command(0, 10 * M_PI / 180, facade.get_scene_container().get_current_camera());
    command.call(facade);

    repaint();
}
//up
void MainWindow::on_pushButton_11_clicked()
{
    Rotate_camera_command command(-10 * M_PI / 180, 0, facade.get_scene_container().get_current_camera());
    command.call(facade);

    repaint();
}
//down
void MainWindow::on_pushButton_10_clicked()
{
    Rotate_camera_command command(10 * M_PI / 180, 0, facade.get_scene_container().get_current_camera());
    command.call(facade);

    repaint();
}
//right
void MainWindow::on_pushButton_8_clicked()
{
    Rotate_camera_command command(0, -10 * M_PI / 180, facade.get_scene_container().get_current_camera());
    command.call(facade);

    repaint();
}
