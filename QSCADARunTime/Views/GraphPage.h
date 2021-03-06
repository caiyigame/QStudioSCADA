﻿#ifndef GRAPHPAGE_H
#define GRAPHPAGE_H

#include <QWidget>
#include <QMimeData>
#include <QMenu>
#include <QDataStream>
#include <QMessageBox>
#include <QClipboard>
#include <QApplication>
#include "IDrawGraphPage.h"
#include "Element.h"
#include <QFile>

class GraphPage : public QWidget
{
    Q_OBJECT

public:
    GraphPage(const QRectF &rect, QWidget *parent = 0);

    void setGraphPageId(const QString &);
    QString getGraphPageId() const;

    void setGraphPageBackground(const QColor &);
    QColor getGraphPageBackground() const;

    void setGraphPageWidth(int);
    int getGraphPageWidth() const;

    void setGraphPageHeight(int);
    int getGraphPageHeight() const;

    void setActive(bool);
    bool active();

    QString getFileName() const;
    void setFileName(const QString &);

    QString getProjectPath() const;
    void setProjectPath(const QString &);

    void loadAsXML(const QString &filename);
    void loadAsBinary(const QString &filename);
    void readItems(QDataStream &in,int offset,bool select);

    void addElementEvent();

    friend QDataStream &operator>>(QDataStream &in, GraphPage &GraphPage);

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

private:
    void createItems(const QString &, QPointF);
    void createContextMenuActions();
    void populateCoordinates(const Qt::Alignment &,
                             QVector<double> *,
                             const QList <QGraphicsItem*> &);
    //XML LOAD
    void readGraphPageConfig(QFile &file);
    void readGraphPageTag(QXmlStreamReader &xml);
    void setGraphPageAttributes(QXmlStreamReader &xml);
    Element *createElement(const QString &internalType);

    void loadLibrary(QByteArray &data);
    void readLibraryConfig(QFile &file);
    void readLibraryTag(QXmlStreamReader &xml);

signals:
    void newElementAdded();
    void changeGraphPageName();
    void elementsDeleted();
    void elementIdChanged();
    void signalShowAddProperties();

private:
    QString projpath_;
    Element *currentItem;
    QString graphPageId;
    QString graphPagePriority;
    QString filename;
    QColor graphPageBackground;
    int graphPageWidth;
    int graphPageHeight;
    bool onActive;
    QList <Element *> copyList;
    QList <Element *> elementList_;
};

// 注册元素对象创建函数
extern void registerCreateObjectFunc();

#endif // GRAPHPAGE_H
