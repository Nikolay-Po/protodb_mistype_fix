#include <QWidget>
#include <QLabel>
#include <QToolButton>
#include <QLineEdit>
#include <QSpinBox>
#include <QMenu>
#include "sequence.h"
#include "sequence_box.h"


SequenceBox::SequenceBox(const QPointer<Sequence>& aSq)
  : mSq(aSq)
{
  createGui();
}

SequenceBox::~SequenceBox()
{
  if (mIdxLabel) {
    mIdxLabel->deleteLater();
  }

  if (mToolButton) {
    mToolButton->deleteLater();
  }

  if (mNameWgt) {
    mNameWgt->deleteLater();
  }

  if (mTriggeredNameWgt) {
    mTriggeredNameWgt->deleteLater();
  }

  if (mRepeatTimeWgt) {
    mRepeatTimeWgt->deleteLater();
  }
}

int SequenceBox::count() const
{
  return 5;
}

QWidget* SequenceBox::get(int aWgtId)
{
  QWidget* wgt = nullptr;

  switch(aWgtId) {
    case 0: wgt = mIdxLabel;  break;
    case 1: wgt = mNameWgt;  break;
    case 2: wgt = mTriggeredNameWgt; break;
    case 3: wgt = mRepeatTimeWgt; break;
    case 4: wgt = mToolButton; break;
  }

  return wgt;
}

void SequenceBox::setIdx(int aIdx)
{
  mIdxLabel->setText(QString::number(aIdx));
}

void SequenceBox::onSendClicked()
{
  emit sSend(mSq);
}

void SequenceBox::onEditClicked()
{
  emit sEdit(mSq);
}

void SequenceBox::onRemoveClicked()
{
  //deleteLater();
  emit sRemoveMe(mSq);
}

void SequenceBox::createActions()
{
  mSendAct   = new QAction(QIcon(":/icons/arrow.svg"), tr("&Send"), this);
    connect(mSendAct, &QAction::triggered, this, &SequenceBox::onSendClicked);

  mEditAct   = new QAction(QIcon(":/icons/edit.svg") , tr("&Show in editor"), this);
    connect(mEditAct, &QAction::triggered, this, &SequenceBox::onEditClicked);

  mRemoveAct = new QAction(QIcon(":/icons/close.svg"), tr("&Remove"), this);
    connect(mRemoveAct, &QAction::triggered, this, &SequenceBox::onRemoveClicked);
}

void SequenceBox::createMenu()
{
  mToolMenu = new QMenu();
    mToolMenu->addAction(mSendAct);
    mToolMenu->addAction(mEditAct);
    mToolMenu->addSeparator();
    mToolMenu->addAction(mRemoveAct);
}

void SequenceBox::createGui()
{
  createActions();
  createMenu();

  mIdxLabel = new QLabel("N");
  mNameWgt = new QLineEdit(mSq->name());
    mNameWgt->setReadOnly(true);

  mTriggeredNameWgt = new QLineEdit(mSq->triggerName());

  mRepeatTimeWgt = new QSpinBox();
    mRepeatTimeWgt->setMaximum(10000);
    mRepeatTimeWgt->setSingleStep(100);
    mRepeatTimeWgt->setValue(0);
    mRepeatTimeWgt->setSuffix("ms");
    mRepeatTimeWgt->setSpecialValueText(QObject::tr("No Repeat"));

  mToolButton  = new QToolButton();
    mToolButton->setIcon(QIcon(":/icons/arrow.svg"));
    mToolButton->setMenu(mToolMenu);
    connect(mToolButton, &QToolButton::clicked, this, &SequenceBox::onSendClicked);
}

