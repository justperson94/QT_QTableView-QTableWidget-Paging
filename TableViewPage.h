/**************************************************************************
** Copyright (C) 2013 Southgis Co.,Ltd. Written by Young Yori, All rights reserved.
**--------------------------------------------------------------------------------
**   Filename:LinearList.h
**   Author: Young Yori
**   Data: Administrator 2013/12/25 2013
**   Description:
**          This file is part of the Data Development Department Project and shall
**      only be used, modified, and distributed under the terms of the Data
**      Development Department this Source.
**
**      Included in the build system of the FreeType library.
**--------------------------------------------------------------------------------
**                      www.newdebug.com, 12319597@qq.com
**************************************************************************/

#ifndef TABLEVIEWPAGE_H
#define TABLEVIEWPAGE_H
#include "GlobalConstances.h"

#include <QSqlTableModel>
#include <QTableView>
#include <QEvent>
#include <QThread>
#include <QSqlRecord>
#include <QPainter>
#include <QStyledItemDelegate>
#include <QItemDelegate>
#include <QApplication>
#include <QMouseEvent>
#include <QHeaderView>
#include <QComboBox>

#include <QDebug>

class QSqlDatabase;

class SqlTableModel : public QSqlTableModel
{
    Q_OBJECT
public:
        explicit SqlTableModel(QWidget *parent = 0, QSqlDatabase db = QSqlDatabase()):
        QSqlTableModel(parent, db)
    {
    }

    bool setData( const QModelIndex &index, const QVariant &value, int role = Qt::EditRole )
    {
        if(!index.isValid())
            return false;

        return QSqlTableModel::setData(index, value, Qt::EditRole);
    }

    QVariant data( const QModelIndex &index, int role = Qt::DisplayRole ) const
    {
        if(!index.isValid())
            return QVariant();

        return QSqlTableModel::data(index, role);
    }
};

class TableViewPage : public QTableView
{
    Q_OBJECT
public:
    explicit TableViewPage(QWidget *parent = 0);
    ~TableViewPage();

    // 为了获取被隐藏的列数据，直接从当前tableview的model是无法
    // 获取被隐藏列的数据的，只能通过数据库的model取得数据
    QSqlTableModel* sqlModel() { return m_sqlModel; }

    QList<QVariant> currentRowInfo() const;
    int currentPage() const { return m_nCurPage; }
    int totalSize() const { return m_nTotal; }
    int lastPageSize() const { return m_nLastPageSize; }

signals:
    void insertAct();
    void removeAct();

public slots:
    void insert(const QList<QVariant> &valueList);
    void remove();

    void previousPage();
    void nextPage();
    void gotoPage(int index);
    int  totalPage();
    void updateModel();

protected:
    void contextMenuEvent(QContextMenuEvent *event);  // TableWidgetPage right click event

private:
    int lastPageSize();

private:
    SqlTableModel*      m_sqlModel;
    QThread             m_thread;

    int                 m_nStartId;
    int                 m_nPageSize;
    int                 m_nCurPageSize;
    int                 m_nLastPageSize;
    int                 m_nTotal;

    int                 m_nCurPage;
    int                 m_nTotalPage;
    bool                m_enableModify;
};


// Set table text, background style here
class BackgroundItemDelegate: public QItemDelegate
{
    Q_OBJECT
public:
    explicit BackgroundItemDelegate(QWidget* parent):QItemDelegate(parent){}

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
                           const QModelIndex &index ) const
    {
        // 得到index的文本，以便后面绘制
        QString text = (index.data(Qt::DisplayRole)).toString();
        QStyleOptionViewItem opt = setOptions(index, option);

        // // restrict resize column
        // qobject_cast<TableViewPage*>(parent())->horizontalHeader()->resizeSection(MMSI, 20);

        painter->save();

        // // change table text color
        // QPen pen;
        // pen.setColor(QColor(QColor(255, 0, 0)));
        // painter->setPen(pen);

        painter->drawText(opt.rect, opt.displayAlignment, text);
        painter->restore();
    }

};

#endif // TABLEVIEWPAGE_H
