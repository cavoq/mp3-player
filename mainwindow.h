#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "playlisttablemodel.h"
#include <QMainWindow>
#include <QMediaPlayer>
#include <QMediaPlaylist>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void loadPlaylist();
    void onMediaStatusChanged(QMediaPlayer::MediaStatus status);
    void onMetaDataChanged();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    PlaylistTableModel *playlistTableModel;
    QMediaPlayer *player;
    void setIcons();
    QList<QUrl> getSongUrlsFromDialog();
    void setMetaData(QList<AudioMedia> &songs);
};

#endif // MAINWINDOW_H
