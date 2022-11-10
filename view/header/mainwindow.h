/**
 *  Declaration of the MainWindow class, controls logic in the Model-View architecture.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "model/header/playlisttablemodel.h"
#include "qlabel.h"
#include "qtoolbutton.h"
#include <QMainWindow>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QSortFilterProxyModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:

    /**
     * Loads the playlist into the application.
     */
    void loadPlaylist();

    /**
     * Switches the playing status of the {@link #player}.
     *
     * @param playing True if the song is currently playing.
     */
    void switchPlaying(bool playing);

    /**
     * Switches the mute status of the {@link #player}.
     *
     * @param muted True if the song is currently muted.
     */
    void switchMute(bool muted);

    /**
     * Updates the duration in the ui when the duration of the media in
     * {@link #player} changes.
     *
     * @param duration Duration of the current Media.
     */
    void onDurationChanged(qint64 duration);

    /**
     * Updates the position in the ui when the position of the media in
     * {@link #player} changes.
     *
     * @param position Position of the current Media.
     */
    void onPositionChanged(qint64 position);

    /**
     * Updates the volume in the ui when the volume of the media in
     * {@link #player} changes.
     *
     * @param volume Volume of the current Media.
     */
    void onVolumeChanged(int volume);

    /**
     * Updates the media of {@link #player} and the selection of the
     * {@link #playlistTableModel} when the index of playlist changes.
     *
     * @param index Index of the playlist in {@link #playlistTableModel}.
     */
    void onCurrentIndexChanged(int index);

    /**
     * Updates the media of {@link #player} when the selection in {@link #playlistTableModel}
     * changes.
     *
     * @param selection QModelIndex of the selection in {@link #playlistTableModel}.
     */
    void onCurrentSelectionChanged(const QModelIndex &selection);

    /**
     * If the current Media ends, the status changes and the index in {@link #playlistTableModel}
     * is updated.
     *
     * @param status Current media status in {@link #player}.
     */
    void onMediaStatusChanged(QMediaPlayer::MediaStatus status);

    /**
     * Fast forwards in the current song playing.
     */
    void fastForward();

    /**
     * Rewinds in the current song playing.
     */
    void rewind();

    /**
     * Stops the playing of the current song.
     */
    void stopSong();

    /**
     * Searches a song in the playlistTableView.
     *
     * @param titel Titel of the song.
     */
    void searchSong(QString titel);

    /**
     * Plays the next song in the playlist.
     */
    void nextSong();

    /**
     * Plays the previous song in the playlist.
     */
    void previousSong();

    /**
     * Plays a random song in the playlist.
     */
    void randomSong();

    /**
     * Skips to a current position when the song-slider is released.
     */
    void onSongSliderReleased();

public:

    /**
     * Constructs a MainWindow object.
     *
     * @param parent Parent object.
     */
    MainWindow(QWidget *parent = nullptr);

    /**
     * Destructs MainWindow object.
     */
    ~MainWindow();

private:

    /// User interface object of the MainWindow.
    Ui::MainWindow *ui;

    /// Instance of @see PlaylistTableModel.
    PlaylistTableModel *playlistTableModel;

    /// Instance of @see QMediaPlayer.
    QMediaPlayer *player;

    /**
     * Sets the icons in the user interface.
     */
    void setIcons();

    /**
     * Creates the signals and connects them to the slots.
     */
    void createSignals();

    /**
     * Creates the shortcuts and connects them to the slots.
     */
    void createShortcuts();

    /**
     * Sets the time in a label.
     *
     * @param label Label to set the time on.
     * @param timeInMs Time in milliseconds.
     */
    void setTimeLabel(QLabel *label, qint64 timeInMs);

    /**
     * Sets the position of a song.
     *
     * @param position Position to set the song to.
     */
    void setPosition(qint64 position);

    /**
     * Changes the icon and tooltip of a button.
     *
     * @param button Button to change.
     * @param icon Icon to be set.
     * @param tooltip Tooltip to be set.
     */
    void switchButton(QToolButton *button, QIcon icon, QString tooltip);

    /**
     * Get the urls of songs from a dialog.
     *
     * @return The song urls as a list.
     */
    QList<QUrl> getSongUrlsFromDialog();

    /**
     * Initialize a playlist with songs.
     *
     * @param playlist @see AudioPlaylist to be initialized.
     * @param songUrls Song urls to initialize the playlist with.
     */
    void initializePlaylist(AudioPlaylist *playlist, QList<QUrl> &songUrls);

    /**
     * Gets the meta data of a song.
     *
     * @param song Url of the song.
     * @return Meta data as a @see QVariantList.
     */
    QVariantList getMetaData(QUrl song);
};

#endif // MAINWINDOW_H
