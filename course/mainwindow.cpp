#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    update = true;

    shared_ptr<Camera> cam = make_shared<Camera>(Camera(Point_3d(300,300,-100)));
    shared_ptr<Position> pos = make_shared<Position>(Position(Point_3d(300,300,-100)));
    facade.get_scene_container().add_object(cam);
    facade.get_scene_container().add_position(pos);
    facade.get_scene_container().set_current_camera(cam);

    ui->setupUi(this);
    ui->pushButton_10->setStyleSheet("border-image:url(../../../../course/img/down.png);");
    ui->pushButton_11->setStyleSheet("border-image:url(../../../../course/img/up.png);");
    ui->pushButton_8->setStyleSheet("border-image:url(../../../../course/img/right.png);");
    ui->pushButton_9->setStyleSheet("border-image:url(../../../../course/img/left.png);");
    ui->pushButton_6->setStyleSheet("border-image:url(../../../../course/img/plus.png);");
    ui->pushButton_7->setStyleSheet("border-image:url(../../../../course/img/minus.png);");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    if (!update) return;
    QPainter p(this);
    p.setPen(QPen(Qt::white));
    p.setBrush(QBrush(Qt::white));
    p.setClipRect(0, 0, width() - 180, height());
    p.drawRect(0, 0, width() - 180, height());

    Object *cam = facade.get_scene_container().get_current_camera()->get();
    if (facade.get_scene_container().get_objects().size() > 0) {
        DrawQt drawer(p, *(Camera*)cam);
        Draw_command command(drawer, facade.get_scene_container().get_begin_object(), facade.get_scene_container().get_end_object());
        command.call(facade);
    }
    update = false;
}

void MainWindow::on_pushButton_clicked()
{
    update = true;
    QString str = ui->spinBox->text();
    bool correct = 0;
    str.toInt(&correct);
    if (0 == correct) {
        QMessageBox::critical(this,"ошибка","Неверно введены данные");
        return;
    }
    double dx = str.toInt();

    str = ui->spinBox_2->text();
    str.toInt(&correct);
    if (0 == correct) {
        QMessageBox::critical(this,"ошибка","Неверно введены данные");
        return;
    }
    double dy = str.toInt();

    str = ui->spinBox_3->text();
    str.toInt(&correct);
    if (0 == correct) {
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
    update = true;
    QString str = ui->doubleSpinBox->text();
    str.replace(',', '.');
    bool correct = 0;
    str.toDouble(&correct);
    if (0 == correct) {
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
    update = true;
    QString str = ui->spinBox_4->text();
    bool correct = 0;
    str.toInt(&correct);
    if (0 == correct) {
        QMessageBox::critical(this,"ошибка","Неверно введены данные");
        return;
    }
    double anx = str.toInt();

    Rotate_x_command command_x(anx, facade.get_scene_container().get_begin_object(), facade.get_scene_container().get_end_object(), facade.get_scene_container().get_begin_position());
    command_x.call(facade);

    str = ui->spinBox_5->text();
    str.toInt(&correct);
    if (0 == correct) {
        QMessageBox::critical(this,"ошибка","Неверно введены данные");
        return;
    }
    double any = str.toInt();

    Rotate_y_command command_y(any, facade.get_scene_container().get_begin_object(), facade.get_scene_container().get_end_object(), facade.get_scene_container().get_begin_position());
    command_y.call(facade);

    str = ui->spinBox_6->text();
    str.toInt(&correct);
    if (0 == correct) {
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
    update = true;
    QString filename = QFileDialog::getOpenFileName(nullptr, "Open Dialog", "", "*.txt");
    if (filename.isEmpty()) {
        QMessageBox::critical(this,"ошибка","Файл отсутствует, повторите ввод");
        return;
    }
    const char *f = filename.toStdString().c_str();

    File_loader file_loader(f);
    Model_builder builder;
    Load_command command(file_loader, builder);
    command.call(facade);
    update = true;
    repaint();
}

//clear
void MainWindow::on_pushButton_5_clicked()
{
    facade.get_scene_container().get_objects().clear();
    facade.get_scene_container().get_positions().clear();

    shared_ptr<Camera> cam = make_shared<Camera>(Camera(Point_3d(300,300,-100)));
    shared_ptr<Position> pos = make_shared<Position>(Position(Point_3d(300,300,-100)));
    facade.get_scene_container().add_object(cam);
    facade.get_scene_container().add_position(pos);
    facade.get_scene_container().set_current_camera(cam);

    update = true;
    repaint();
}

//+
void MainWindow::on_pushButton_6_clicked()
{
    Scale_camera_command command(2, facade.get_scene_container().get_current_camera());
    command.call(facade);
    update = true;
    repaint();
}
//-
void MainWindow::on_pushButton_7_clicked()
{
    Scale_camera_command command(0.5, facade.get_scene_container().get_current_camera());
    command.call(facade);
    update = true;
    repaint();
}
//right
void MainWindow::on_pushButton_9_clicked()
{
    Rotate_camera_command command(0, 5 * M_PI / 180, facade.get_scene_container().get_current_camera());
    command.call(facade);
    update = true;
    repaint();
}
//up
void MainWindow::on_pushButton_11_clicked()
{
    Rotate_camera_command command(-5 * M_PI / 180, 0, facade.get_scene_container().get_current_camera());
    command.call(facade);
    update = true;
    repaint();
}
//down
void MainWindow::on_pushButton_10_clicked()
{
    Rotate_camera_command command(5 * M_PI / 180, 0, facade.get_scene_container().get_current_camera());
    command.call(facade);
    update = true;
    repaint();
}
//right
void MainWindow::on_pushButton_8_clicked()
{
    Rotate_camera_command command(0, -5 * M_PI / 180, facade.get_scene_container().get_current_camera());
    command.call(facade);
    update = true;
    repaint();
}

void pause() {
    QApplication::processEvents(QEventLoop::AllEvents, 1);
}
// go
void MainWindow::on_pushButton_12_clicked()
{
    Point_3d speed(ui->horizontalSlider->value(), 0, 0);
    Explosion_command command(facade.get_scene_container().get_begin_object(), facade.get_scene_container().get_end_object(), speed);

    for (int i = 0; i < 500; i++) {
        command.call(facade);
        update = true;
        repaint();
        pause();
    }
}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    ui->label_7->setNum(position);
    ui->label_7->setGeometry(ui->label_2->x() + 10 * (position - 1), ui->label_2->y(), ui->label_2->width(), ui->label_2->height());
}
