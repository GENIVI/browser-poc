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

    Q_PROPERTY(QString _bookmarktitle READ bookmarktitle WRITE setBookmarkTitle)
    Q_PROPERTY(QString name READ name WRITE setName)
public:
    explicit browserdbus(QObject *parent = 0);
    
    Q_INVOKABLE void goBack();
    Q_INVOKABLE void goForward();
    Q_INVOKABLE void reload();
    Q_INVOKABLE void loadurl(QString url);
    Q_INVOKABLE void getBookmarks();
    Q_INVOKABLE void addBookmark(QString bookmarkurl, QString bookmarktitle);
    Q_INVOKABLE void test();

    QString bookmarktitle() { return _bookmarktitle; }
    void setBookmarkTitle(QString bookmark) { _bookmarktitle = bookmark; }

    QString name() const { return m_name; }
    void setName(const QString &n)  { m_name = n; }

signals:
    
public slots:

private:
    conn::brw::IBookmarkManager *bookmark;
    conn::brw::IUserInput *userinput;
    conn::brw::IWebPageWindow *webpagewindow;
    conn::brw::IBrowser *browser;

    QString _bookmarktitle;
    QString m_name;
    
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
