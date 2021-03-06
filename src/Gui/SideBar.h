#ifndef GUITABBLOCK_H
#define GUITABBLOCK_H

#include "Gui/Frameworks/Widgets/Button.h"
#include "Gui/Frameworks/Widgets/SearchBar.h"

#include "ContactsTab.h"
#include "HomeTab.h"
#include "SettingsTab.h"

#include <QStackedWidget>
#include <QLineEdit>
#include <QIcon>


class SideBar : public QWidget
{
  Q_OBJECT

public:
  explicit SideBar(QWidget *parent = nullptr);
  ~SideBar();

  void displaySettings(const bool &b);
  void displayHome();
  void displayChat();

  HomeTab *home_tab;
  ContactsTab *contacts_tab;
  SettingsTab *settings_tab;

private:
  QStackedWidget *tab_stacked_widget;
  SearchBar *search_bar;
};

#endif // GUITABBLOCK_H
