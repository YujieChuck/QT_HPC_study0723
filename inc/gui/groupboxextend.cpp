#include "groupboxextend.h"

GroupBoxExtend::GroupBoxExtend(QWidget *parent /*= nullptr*/, State state /*= STATE_NORMAL*/)
    : QGroupBox(parent)
{
    setObjectName("GroupBoxExtend");
    setCheckable(true);
    state_ = state;
    if (state_ == STATE_NORMAL)
    {
        //隐藏垂直边框
        setFlat(true);
        setChecked(false);
    }
    connect(this, SIGNAL(clicked(bool)), this, SLOT(onChecked(bool)));
}

GroupBoxExtend::GroupBoxExtend(const QString &title, QWidget *parent, GroupBoxExtend::State state)
{
    setObjectName("GroupBoxExtend");
    setCheckable(true);
    state_ = state;
    if (state_ == STATE_NORMAL)
    {
        //隐藏垂直边框
        setFlat(true);
        setChecked(false);
    }
    connect(this, SIGNAL(clicked(bool)), this, SLOT(onChecked(bool)));
}

void GroupBoxExtend::UpdateState(bool checked)
{
    onChecked(checked);
}

void GroupBoxExtend::onChecked(bool checked)
{
//    if (checked){
//        //显示垂直边框
//        //setFlat(false);
////        setStyleSheet("border:1px solid #242424;border-radius:5px;");
//        for (auto iter = children_.begin(); iter != children_.end(); ++iter)
//        {
//            (*iter)->setVisible(true);
//        }
//        state_ = STATE_EXPAND;
//    }
//    else
//    {
//        //隐藏垂直边框
//        setFlat(true);
////        setStyleSheet("border:none;");
//        for (auto iter = children_.begin(); iter != children_.end(); ++iter)
//        {
//            (*iter)->setVisible(false);
//        }
//        state_ = STATE_NORMAL;
//    }
}

void GroupBoxExtend::addWidget(QWidget *widget)
{
    if (widget != NULL){
        if (state_ == STATE_NORMAL)
        {
            widget->setVisible(false);
        }
        children_.push_back(widget);
    }

//    if (state_ == STATE_NORMAL)
//    {
//        widget->setVisible(false);
//    }
//    children_.push_back(widget);
}

GroupBoxExtend::State GroupBoxExtend::getState() const
{
    return state_;
}



