/****************************************************************************
**
** Year    		: 2018/07/02
** User  		: YujieChuck
** E-Mail  		: caeunion@163.com
** Description	: 本控件来自与网络，本人收藏而来。
**                具体出处如下：
**                https://www.cnblogs.com/jiangbin/p/6752957.html
**                非常感谢############   binbinneu   ############的分享
**                该类实现Qt自定义控件之可伸缩组合框（GroupBox）控件
** If you have any questions , please contact me
****************************************************************************/
#ifndef GROUPBOXEXTEND_H
#define GROUPBOXEXTEND_H

#include <QGroupBox>
#include <QVector>

class GroupBoxExtend : public QGroupBox
{
    Q_OBJECT

    public:
        enum State{
            STATE_NORMAL,
            STATE_EXPAND
        };

    public:
        GroupBoxExtend(QWidget *parent = NULL, State state = STATE_NORMAL);
        GroupBoxExtend(const QString &title, QWidget *parent = NULL, State state = STATE_NORMAL);
        void UpdateState(bool checked);

    private Q_SLOTS:
        void onChecked(bool checked);

    public:
        void addWidget(QWidget *widget);
        State getState() const;

    private:
        QVector<QWidget*> children_;
        State state_;
};



#endif // GROUPBOXEXTEND_H
