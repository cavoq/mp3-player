#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setIcons();
    connect(ui->loadPlaylistButton, SIGNAL(clicked()), SLOT(getSongs()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setIcons()
{
    ui->rewindButton->setIcon(QIcon(":/icons/rewind.png"));
    ui->fastForwardButton->setIcon(QIcon(":/icons/fastForward.png"));
    ui->lastSongButton->setIcon(QIcon(":/icons/last.png"));
    ui->nextSongButton->setIcon(QIcon(":/icons/next.png"));
    ui->muteButton->setIcon(QIcon(":/icons/mute.png"));
    ui->stopButton->setIcon(QIcon(":/icons/stop.png"));
    ui->playStopButton->setIcon(QIcon(":/icons/resumePlaying.png"));
}

QStringList MainWindow::getSongs()
{
    QStringList songs = QFileDialog::getOpenFileNames(this, tr("Wähle songs aus"), "/home", tr("MP3 Files (*.mp3)" ));
    std::cout << songs[0].toStdString() << std::endl;
    return songs;
}
