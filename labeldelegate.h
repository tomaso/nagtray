#ifndef LABELDELEGATE_H
#define LABELDELEGATE_H

#include <QStyledItemDelegate>

class LabelDelegate : public QStyledItemDelegate {

protected:
    void paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
    QSize sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const;
};

#endif // LABELDELEGATE_H
