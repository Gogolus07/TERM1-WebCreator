#ifndef MODULEITEM_H
#define MODULEITEM_H

#include <QPushButton>

QT_BEGIN_NAMESPACE
class QMouseEvent;
class QPoint;
QT_END_NAMESPACE

class moduleItem : public QPushButton
{
    Q_OBJECT
    public:
        explicit moduleItem(QWidget *parent = nullptr);
        explicit moduleItem(QString name, QWidget *parent = nullptr);

    protected:
        void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
        void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
        void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
        void enterEvent( QEvent*event ) Q_DECL_OVERRIDE;

    private:
        QPoint dragStartPosition;
        QString name;
    //signals:

    //public slots:
};

#endif // MODULEITEM_H
