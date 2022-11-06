#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "playlisttablemodel.h"
#include "qlabel.h"
#include "qtoolbutton.h"
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
    void switchPlaying(bool playing);
    void switchMute(bool muted);
    void onDurationChanged(qint64 duration);
    void onPositionChanged(qint64 position);
    void onVolumeChanged(int volume);
    void onCurrentMediaChanged(QMediaContent currentMedia);
    void fastForward();
    void rewind();
    void nextSong();
    void previousSong();
    void onSongSliderReleased();
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
    void setTimeLabel(QLabel *label, qint64 timeInMs);
    void setPosition(qint64 position);
    void switchButton(QToolButton *button, QIcon icon, QString tooltip);
    QList<QUrl> getSongUrlsFromDialog();
    QVariantList getMetaData(QUrl song);
};

#endif // MAINWINDOW_H
