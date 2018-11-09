#ifndef GuiLabelButton_H
#define GuiLabelButton_H

#include "Global.h"

#include <QLabel>
#include <QMouseEvent>
#include <QTimer>
#include <QDebug>

class LabelButton : public QLabel
{
  Q_OBJECT

public:
  explicit LabelButton(const int &hoverDelay = 0, QWidget *parent = nullptr);

  void setDefaultPixmap(const QString &path);
  void setHoveredPixmap(const QString &path);
  void setPressedPixmap(const QString &path);
  void setDefault();
  void setHovered();
  void setDisabled(const bool &dis) {disabled = dis;}

protected:
  void mousePressEvent(QMouseEvent *);
  void mouseReleaseEvent(QMouseEvent *);
  void enterEvent(QEvent *);
  void leaveEvent(QEvent *);

private:
  QPixmap default_pixmap;
  QPixmap hovered_pixmap;
  QPixmap pressed_pixmap;

  int hover_delay;
  int disabled = false;
  bool hover_signal_lock;

signals:
  void clicked();
  void entered();
  void left();
};

#endif // GuiLabelButton_H
