#include "Table.hpp"

#include <QPushButton>
#include <QHeaderView>
#include <QGraphicsBlurEffect>

namespace figures_client_app {

  Table::Table(QWidget* parent /*= nullptr*/) noexcept :
    QTableWidget{ ROWS_COUNT, COLUMNS_COUNT, parent } {
    setHorizontalHeaderLabels(
      QStringList() << "ID" << "Type" << "Position" << "Region" << "" << "");
    verticalHeader()->setVisible(false);
    setSelectionMode(QAbstractItemView::NoSelection);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
  }

  Table::~Table() {
  }

  int Table::setBaseItem(QSharedPointer<FigureBase> figure) {
    const int new_row{ this->rowCount() };
    insertRow(new_row);

    QTableWidgetItem* id = new QTableWidgetItem{ figure->uuid_.toString() };
    setItem(new_row, ID_COL, id);

    QString pos = QString("%1px, %2px").arg(figure->x_).arg(figure->y_);
    QTableWidgetItem* pos_item = new QTableWidgetItem{ pos };
    pos_item->setTextAlignment(Qt::AlignCenter);
    setItem(new_row, POS_COL, pos_item);

    QPushButton* hide_button = new QPushButton{};
    hide_button->setIcon(QIcon{ HIDE_ICO_PATH });
    hide_button->setFocusPolicy(Qt::NoFocus);
    QTableWidget::connect(
      hide_button,
      &QPushButton::clicked,
      static_cast<QTableWidget*>(this),
      [this, id = figure->uuid_]() {
        emit itemHideSignal(id.toString());
      });
    setCellWidget(new_row, HIDE_COL, hide_button);

    QPushButton* delete_button = new QPushButton{};
    delete_button->setIcon(QIcon{ DELETE_ICO_PATH });
    QTableWidget::connect(
      delete_button,
      &QPushButton::clicked,
      static_cast<QTableWidget*>(this),
      [this, id = figure->uuid_]() {
        emit itemRemoveSignal(id.toString());
      });
    setCellWidget(new_row, DELETE_COL, delete_button);

    return new_row;
  }

  void Table::setCell(int row, int col, const QString& value) {
    QTableWidgetItem* item = new QTableWidgetItem{ value };
    item->setTextAlignment(Qt::AlignCenter);
    setItem(row, col, item);
  }

  void Table::addRectImpl(QSharedPointer<Rect> rect) {
    const int new_row = setBaseItem(rect);

    setCell(new_row, TYPE_COL, RECT_TYPE);

    QString region =
      QString("%1px, %2px").arg(rect->width_).arg(rect->height_);
    setCell(new_row, REGION_COL, region);
  }

  void Table::addTriangleImpl(QSharedPointer<Triangle> triangle) {
    const int new_row = setBaseItem(triangle);

    setCell(new_row, TYPE_COL, TRIANGLE_TYPE);

    const int left =
      std::min(std::min(triangle->x_, triangle->x2_), triangle->x3_);
    const int right =
      std::max(std::max(triangle->x_, triangle->x2_), triangle->x3_);
    const int bottom =
      std::min(std::min(triangle->y_, triangle->y2_), triangle->y3_);
    const int top =
      std::max(std::max(triangle->y_, triangle->y2_), triangle->y3_);
    QString region =
      QString("%1px, %2px").arg(right - left).arg(top - bottom);
    setCell(new_row, REGION_COL, region);
  }

  void Table::addElipsImpl(QSharedPointer<Elips> elips) {
    const int new_row = setBaseItem(elips);

    setCell(new_row, TYPE_COL, ELIPS_TYPE);

    QString region =
      QString("%1px, %2px").arg(2 * elips->r1_).arg(2 * elips->r2_);
    setCell(new_row, REGION_COL, region);
  }

  void Table::addLineImpl(QSharedPointer<Line> line) {
    const int new_row = setBaseItem(line);

    setCell(new_row, TYPE_COL, LINE_TYPE);

    const int width = std::abs(line->x2_ - line->x_);
    const int height = std::abs(line->y2_ - line->y_);
    QString region =
      QString("%1px, %2px").arg(width).arg(height);
    setCell(new_row, REGION_COL, region);
  }

  void Table::removeItemImpl(const QString item_id) {
    for (int row = 0; row < rowCount(); ++row) {
      QTableWidgetItem* id_item = item(row, ID_COL);
      if (id_item->text() == item_id) {
        removeRow(row);
        break;
      }
    }
  }

  inline void switchButtonStyle(QPushButton* hide_button) {
    QGraphicsEffect* effect = hide_button->graphicsEffect();
    if(!effect) {
      QGraphicsBlurEffect* blur_effect = new QGraphicsBlurEffect{ hide_button };
      static constexpr int HIDE_BLUR_RADIUS{ 2 };
      blur_effect->setBlurRadius(HIDE_BLUR_RADIUS);
      hide_button->setGraphicsEffect(blur_effect);
    } else {
      hide_button->setGraphicsEffect(nullptr);
    }
  }

  void Table::hideItemImpl(const QString item_id) {
    for (int row = 0; row < rowCount(); ++row) {
      QTableWidgetItem* id_item = item(row, ID_COL);
      if (id_item->text() == item_id) {
        QPushButton* hide_button = qobject_cast<QPushButton*>(cellWidget(row, HIDE_COL));
        switchButtonStyle(hide_button);
        break;
      }
    }
  }


}