#include "MainWindow.hpp"

#include <QMenuBar>
#include <QHeaderView>
#include <QStackedWidget>

namespace figures_client_app {

  MainWindow::MainWindow(QWidget* parent/*=nullptr*/) noexcept :
    QMainWindow{ parent } {
    setupViews();
    setupItemsManger();
    setupMenu();

    setMinimumSize(MIN_WIDTH, MIN_HEIGHT);
  }

  MainWindow::~MainWindow() {
  }

  void MainWindow::setupViews() noexcept {
    setupScene();
    setupTable();

    central_wigets_ = new QStackedWidget{ this };
    central_wigets_->addWidget(table_);
    central_wigets_->addWidget(items_scene_view_);

    setCentralWidget(central_wigets_);
    central_wigets_->setCurrentWidget(table_);
  }

  void MainWindow::setupItemsManger() noexcept {
    items_manager_ = new ItemsManager{ this };
    items_manager_->addConsumer(table_);
    items_manager_->addConsumer(items_scene_);
  }

  void MainWindow::setupMenu() noexcept {
    QMenuBar* menu_bar = new QMenuBar{ this };

    QMenu* menu = new QMenu{ QString::fromUtf16(u"Меню"), menu_bar };

    QAction* render_action = new QAction{ QString::fromUtf16(u"Отрисовка"), menu };
    QObject::connect(render_action, &QAction::triggered, this, &MainWindow::showScenView);
    menu->addAction(render_action);

    QAction* information_action = new QAction{ QString::fromUtf16(u"Информация"), menu };
    QObject::connect(information_action, &QAction::triggered, this, &MainWindow::showTableView);
    menu->addAction(information_action);

    menu_bar->addMenu(menu);
    setMenuBar(menu_bar);
  }

  void MainWindow::showScenView() {
    central_wigets_->setCurrentWidget(items_scene_view_);
  }

  void MainWindow::showTableView() {
    central_wigets_->setCurrentWidget(table_);
  }

  void MainWindow::setupScene() noexcept {
    items_scene_ = new ItemsScene{ this };

    items_scene_view_ = new QGraphicsView{ items_scene_, this };
    items_scene_view_->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    items_scene_view_->hide();
  }

  void MainWindow::setupTable() noexcept {
    table_ = new Table{ this };
  }

}