#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setIcons();
    connect(ui->loadPlayListButton, SIGNAL(click()), SLOT(readSongs()));
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

void MainWindow::readSongs()
{
    QStringList songPaths = QFileDialog::getOpenFileNames(this, tr("Wähle songs aus"), "/home", tr("MP3 Files (*.mp3)" ));
}
