#pragma once

#include <QMainWindow>
#include <QGraphicsView>
#include <QStackedWidget>

#include "Table.hpp"
#include "ItemsScene.hpp"
#include "ItemsManager/ItemsManager.hpp"

namespace figures_client_app {

  class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    explicit MainWindow(QWidget* parent = nullptr) noexcept;
    virtual ~MainWindow();

  private slots:
    void showScenView();
    void showTableView();

  private:
    inline void setupViews() noexcept;
    inline void setupScene() noexcept;
    inline void setupTable() noexcept;
    inline void setupItemsManger() noexcept;
    inline void setupMenu() noexcept;

    Table* table_{ nullptr };

    ItemsScene* items_scene_{ nullptr };
    QGraphicsView* items_scene_view_{ nullptr };

    QStackedWidget* central_wigets_{ nullptr };

    ItemsManager* items_manager_{ nullptr };

    static constexpr std::size_t MIN_HEIGHT{ 400 };
    static constexpr std::size_t MIN_WIDTH{ 650 };
  };

}