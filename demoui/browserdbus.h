#ifndef BROWSERDBUS_H
#define BROWSERDBUS_H

#include <QObject>

#include "ibookmarkmanager_interface.h"
#include "iuserinput_interface.h"
#include "iwebpagewindow_interface.h"
#include "ibrowser_interface.h"

class browserdbus : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString _title READ title WRITE setTitle)
    Q_PROPERTY(QString _url READ url WRITE setUrl)
public:
    explicit browserdbus(QObject *parent = 0);
    
    Q_INVOKABLE void goBack();
    Q_INVOKABLE void goForward();
    Q_INVOKABLE void reload();
    Q_INVOKABLE void loadurl(QString url);
    Q_INVOKABLE void getBookmarks();
    Q_INVOKABLE void addBookmark(QString url, QString title);
    Q_INVOKABLE void getCurrentUrlAndTitle();

    QString title() { return _title; }
    void setTitle(QString bookmark) { _title = bookmark; }

    QString url() const { return _url; }
    void setUrl(const QString &n)  { _url = n; }

signals:
    
public slots:

private:
    conn::brw::IBookmarkManager *bookmark;
    conn::brw::IUserInput *userinput;
    conn::brw::IWebPageWindow *webpagewindow;
    conn::brw::IBrowser *browser;

    QString _title;
    QString _url;
    
};

#include <QString>

class DataObject : public QObject
 {
     Q_OBJECT

     Q_PROPERTY(QString name READ getName WRITE setName)
     Q_PROPERTY(QString url READ getUrl WRITE setUrl)

public:
    DataObject(QString aname, QString aurl) { name = aname; url = aurl;}

    QString getName() { return name; }
    QString getUrl() { return url; }

    void setName(QString name1) { name = name1; }
    void setUrl(QString url1) { url= url1; }

private:
    QString name;
    QString url;
 };


#endif // BROWSERDBUS_H
