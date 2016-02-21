#include "GuiSettingsTab.h"

GuiSettingsTab::GuiSettingsTab(QWidget *parent) : QWidget(parent)
{
  QFont label_font("Futura");
  //label_font.setPointSize(20);
  label_font.setPointSize(20);

  messaging_btn = new GuiMenuButton("messaging", Settings_Messaging, this);
  messaging_btn->setDefaultPixmap(":/img/img/messaging_0.png");
  messaging_btn->setHoveredPixmap(":/img/img/messaging_1.png");

  profile_btn = new GuiMenuButton("profile", Settings_Profile, this);
  profile_btn->setDefaultPixmap(":/img/img/profile_0.png");
  profile_btn->setHoveredPixmap(":/img/img/profile_1.png");

  style_btn = new GuiMenuButton("style", Settings_Style, this);
  style_btn->setDefaultPixmap(":/img/img/style_0.png");
  style_btn->setHoveredPixmap(":/img/img/style_1.png");

  ////main layout
  main_layout = new QVBoxLayout(this);
  main_layout->setContentsMargins(30,20,20,0);
  main_layout->setSpacing(20);
  main_layout->setAlignment(Qt::AlignTop);
  main_layout->addWidget(messaging_btn);
  main_layout->addWidget(profile_btn);
  main_layout->addWidget(style_btn);

  this->setParent(parent);

}

GuiSettingsTab::~GuiSettingsTab()
{

}
