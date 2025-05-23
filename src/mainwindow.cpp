#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "timerdial.h"
#include "iconhelper.h"
#include <QGraphicsView>
#include <QTimer>
#include <QTime>
#include <QDebug>
#include <QTransform>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_scene(nullptr),
    m_timerDial(nullptr)
{
    ui->setupUi(this);
    this->setWindowTitle("Visual Timer");
    
    m_scene = new QGraphicsScene(this);
    ui->timerView->setScene(m_scene);
    ui->timerView->setRenderHint(QPainter::Antialiasing);

    m_timerDial = new TimerDial();
    m_scene->addItem(m_timerDial);
    m_timerDial->setPos(0, 0);
    
    // Set up scene rect to match the dial size exactly
    // Using DIAL_SIZE from TimerDial (180)
    m_scene->setSceneRect(-90, -90, 180, 180);

    // Icon stuff
    QIcon startIcon(IconHelper::createPlayIcon());
    QIcon pauseIcon(IconHelper::createPauseIcon());
    QIcon resetIcon(IconHelper::createResetIcon());
    ui->startButton->setIcon(startIcon);
    ui->resetButton->setIcon(resetIcon);
    m_playIcon = startIcon;
    m_pauseIcon = pauseIcon;
    m_resetIcon = resetIcon;
    ui->startButton->setIconSize(QSize(40, 40));
    ui->resetButton->setIconSize(QSize(40, 40));
    ui->startButton->setFixedSize(60, 60);
    ui->resetButton->setFixedSize(60, 60);
    
    QString buttonStyle = "QPushButton { padding: 2px; }";
    ui->startButton->setStyleSheet(buttonStyle);
    ui->resetButton->setStyleSheet(buttonStyle);
    
    connect(m_timerDial, &TimerDial::timeUpdated, this, &MainWindow::updateTimeDisplay);
    connect(m_timerDial, &TimerDial::timerFinished, this, &MainWindow::timerFinished);
    
    // Initialize time display
    updateTimeDisplay(m_timerDial->getCurrentTime());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startButton_clicked()
{
    if (m_timerDial->isRunning()) {
        // If already running, act as pause
        m_timerDial->pauseTimer();
        ui->startButton->setIcon(m_playIcon);
        ui->startButton->setToolTip("Start Timer");
    } else {
        m_timerDial->startTimer();
        ui->startButton->setIcon(m_pauseIcon);
        ui->startButton->setToolTip("Pause Timer");
    }
    ui->resetButton->setEnabled(!m_timerDial->isRunning());
}


void MainWindow::on_resetButton_clicked()
{
    m_timerDial->resetTimer();
    ui->startButton->setIcon(m_playIcon);
    ui->startButton->setToolTip("Start Timer");
    ui->startButton->setEnabled(true);
    ui->resetButton->setEnabled(false);
}

void MainWindow::updateTimeDisplay(int seconds)
{
    formatTimeDisplay(seconds);
}

void MainWindow::timerFinished()
{
    ui->startButton->setEnabled(false);
    ui->resetButton->setEnabled(true);
    ui->startButton->setIcon(m_playIcon);
    ui->startButton->setToolTip("Start Timer");
    
    // Show Notification
    QMessageBox::information(this, "Timer Finished", "The timer has finished!");
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    
    if (m_scene && m_timerDial) {
        m_scene->setSceneRect(-95, -95, 190, 190);
        ui->timerView->setTransform(QTransform());
        ui->timerView->fitInView(m_scene->sceneRect(), Qt::KeepAspectRatio);
        ui->timerView->centerOn(0, 0);
    }
}

void MainWindow::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);
    
    // Fit the view once the window is shown
    if (m_scene) {
        m_scene->setSceneRect(-95, -95, 190, 190);
        ui->timerView->setTransform(QTransform());
        ui->timerView->fitInView(m_scene->sceneRect(), Qt::KeepAspectRatio);
        ui->timerView->centerOn(0, 0);
    }
}

void MainWindow::formatTimeDisplay(int seconds)
{
    int minutes = seconds / 60;
    int remainingSeconds = seconds % 60;
    minutes = minutes % 60;
    
    QString timeStr;
    
    if (minutes > 0) {
        // Format as "X min Y sec"
        timeStr = QString("%1m %2s").arg(minutes).arg(remainingSeconds);
    } else {
        // Format as "X seconds"
        timeStr = QString("%1s").arg(remainingSeconds);
    }
    
    ui->timeLabel->setText(timeStr);
}