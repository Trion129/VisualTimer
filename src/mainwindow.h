#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QIcon>
#include <QResizeEvent>
#include <QShowEvent>
#include "timerdial.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_startButton_clicked();
    void on_resetButton_clicked();
    void updateTimeDisplay(int seconds);
    void timerFinished();

protected:
    // Override resize events to keep dial properly sized and centered
    void resizeEvent(QResizeEvent *event) override;
    void showEvent(QShowEvent *event) override;

private:
    Ui::MainWindow *ui;
    QGraphicsScene *m_scene;
    TimerDial *m_timerDial;
    QIcon m_playIcon;
    QIcon m_pauseIcon;
    QIcon m_resetIcon;
    
    void formatTimeDisplay(int seconds);
};

#endif // MAINWINDOW_H