#ifndef WIDGET_H
#define WIDGET_H

#include <QMainWindow>
#include <QWidget>

#include <QDebug>
#include <QString>

#include "json.h"

#include <QFile>
#include "vk_auth.h"
#include "vk_get.h"
#include "vk_audiopop.h"
#include "vk_friend.h"
#include "vk_group.h"
#include "download.h"
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QtWidgets>
#include "auther.h"
#include <QtMultimedia>
#include <QShortcut>
#include <QMenuBar>
#include "create_thread.h"
#include <QImage>
#include "vk_lyrics.h"
#include "lyrics_out.h"
#include "vk_add.h"
#include "vk_albums.h"
#include "updateversion.h"
#include "QProcess"
#include "vk_post_status.h"
#include "vk_send_attachment.h"
#include "audioedit.h"
#include "qtwin.h"
#include "osdpretty.h"
#include "connecttoserver.h"
#include "widgetparent.h"
#include "settings.h"
#include "labelnew.h"
#include "threadplayer.h"
#include "runline.h"
#include <QtWinExtras/QWinThumbnailToolButton>
#include <QtWinExtras/QWinThumbnailToolBar>


namespace Ui {
    class Widget;
}


class Widget : public WidgetParent
{
    Q_OBJECT

public:
    explicit Widget(WidgetParent *parent = 0);
    ~Widget();

public slots:  //обработка музыки
    void CreatePlayer(QMediaPlayer *obj);
    void PlaylingSong(QString flag, int RowDoubleClick);
    void ProcessingSong(int tmpRow);
    void selectedItem(QTableWidgetItem* item);
    void mediaStatusChange(QMediaPlayer::MediaStatus status);
    void ActivationTray(QSystemTrayIcon::ActivationReason);
    void mark_Song();

public slots:   //Печать (вывод) информации
    void print_audioTable(QList< QPair<QString, QString> > Artist_Title, QList<QPair<QString, QString> > Id_Url, QList< QPair<QString, QString> > Duration_Genre, QList< QPair<QString, QString> > OwnerId_lyricsId);
    void print_duration(qint64 ab);   
    void print_time_song(qint64 ab);    
    void print_nameFriend_andPhoto( QPair<QString, QString> NamePhoto);
    void print_nameGroup_andPhoto(QString Id_Group);
    void print_newAlbumTab();
    void print_MyPhoto(QString photo);
    void displayMenu(const QPoint &pos);
    void printNewVersion(bool val);
    void print_enable_status();
    void print_friend(QList< QPair<QString, QString> > users);
    void print_group(QList< QPair<QString, QString> > groups);
    void print_albums(QList<QPair<QString, QString> > albums);
    void print_Default_Search_Line();
    void print_Warning(QString str);
    void metaDataChanged(QString key, QVariant value);
    void print_edit_song(QString, QString, QString);
    void print_popular_genre();
    void process_pop_genre(QString genre);
    void selected_album(QString album);
    void print_Error_Player(QMediaPlayer::Error);
    void print_Image_Player_State(QMediaPlayer::State);
    void AudioAvailable(bool);
    void audioBuffer(QAudioBuffer buffer);
    void Create_Thumb_Button();

protected:
    bool eventFilter(QObject* watched, QEvent* event);

public slots:
    void ApplyNew();
    void CloseToUpdate();
    void CreateUpdater();
    void initialization_Tray();
    void initialization_SignalSlot();
    void generation_Id_Program();
    void DrawGUI();
    void MenuChooseDirectory(QString Dir);
    void transparency(int value);
    void getTokenAndUsID(QString token, QString Id, QString photo);
    void changedPlaylist(QUrl current, int flag, int Friend_or_Group, QString flag_genre_pop);
    void SearchMusic(QString tmp);
    void position();
    void positionTWO(int value);
    void positionREVERS(qint64 value);
    void positionTHREE();
    void Friends_music(QString tmp);
    void Groups_music(QString tmp);
    void print_volume_icon(int value_volume);
    void Complete_D();
    void setColor_R(int r);
    void setColor_G(int g);
    void setColor_B(int b);
    void standatColor();
    void download_settings();
    void changePlaylist(int index);
    void Myplaylist();
    void Popularplaylist();
    void RecomPlaylist();
    void exit_Account();
    void Download_fuction(int flag, QString artist, QString title, QString url);
    void install_status();
    void post_attachment(QString FrName);
    void delete_file();
    void seekable(bool);
    void metadata();
    void metadataAvailable(bool);
    void change_show_notif(bool);
    void change_hide_to_tray(bool);
    void register_inregister_hotkey(int Id_Register_HotKey, int id_One_Key, int id_Two_Key);
    void download_ad();
    void run_adGuard();
    void start_group_VK();
    void get_User_Group();
    void get_User_Friend();
    void get_User_Albums();
    void get_Start_Playlist();
    void post_User_trackVisitor();

public slots:
    void AnimationNextButton();
    void AnimationPreviousButton();

signals:
    void succ(QUrl r);
    void succBTN();
    void PlaySong(QString flag, int RowDoubleClick);
    void complete_Editing();
    void complete_Install_status();
    void complete_Download_Song();
    void complete_Download_ad();
    void click_download_music();

private slots: //Нажатие клавиш
    void on_PlayButton_clicked();
    void on_NextButton_clicked();    
    void on_PreviosButton_clicked();
    void on_StopButton_clicked();
    void on_MuteButton_clicked();
    void on_DownloadButton_clicked();  
    void on_hideApp_clicked();
    void on_Search_BTN_clicked();    
    void on_mix_BTN_clicked();
    void on_repeat_BTN_clicked();
    void on_Set_BTN_clicked();
    void on_Close_BTN_clicked();
    void on_clear_search_BTN_clicked();
    void on_Lyrics_BTN_clicked();
    void on_post_Status_clicked();
    void on_pushButton_clicked();
    void on_Genre_Button_clicked();
    void click_next_300();
    void click_previous_300();

    void on_Open_Albums_clicked();

protected slots:
    bool nativeEvent(const QByteArray & eventType, void * message, long * result);

public:

private:
    Ui::Widget *ui;
    //ThreadPlayer *threadPlay;
    QMediaPlayer *player;
    QMap<QString, QString> friend_ids;
    QMap<QString, QString> group_ids;
    QMap<QString, QString> albums_ids;
    class VkAudiopop * audiopop;   
    QString add_Owner_Id;
    QString add_Audio_Id;
    QString tmpArtist;
    QString tmpTitle;
    QString tmpUrl;
    QString tmpGenre;
    int tmprow;
    QString Token;
    QString UsId;
    QString Url_song;
    QString Id_song;
    QString Owner_Id_song;
    QString Lyrics_Id_song;
    QString Artist_song;
    QString Title_song;
    QString Duration_song;
    QString Duration_song_Player;
    QString Genre_song;
    int row;
    QString PlayMusic;
    QString NameFRIEND;
    QString NameGROUP;
    QString NameAlbum;
    QString directory;
    QString temp_frId;
    QString temp_grId;
    QString temp_albumId;
    int R, G, B;
    qreal tran;
    QSystemTrayIcon *trIcon;
    QList< QPair<QString, QString> > tmpArtist_Title;
    QList< QPair<QString, QString> > popular_genre;
    QString sequence;
    bool flag_if_MyPlaylist_isPlaying;
    bool flag_if_RecomendationPlaylist;
    QString Id_PR;
    int status_enable;
    int attachment_wall_or_message;
    OSDPretty *osd;
    QLabel Loading;
    QString temp;
    int SpeedText;
    class RunLine * textsong;
    bool show_Notif, Hide_To_Tray;
    int flag_play;
    HWND hWnd;
    int offset;
    QString tmp_ID, tmp_FOUR;
    QUrl tmp_CURRENT;
    int tmp_SIX, tmp_MYFLAG;
    bool create_tab;
    class vk_post_status * Status;
    bool lock_Status;
};

#endif // WIDGET_H










