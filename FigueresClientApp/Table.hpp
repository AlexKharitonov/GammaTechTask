#pragma once

#include <QTableWidget>

#include "ItemsConsumer.hpp"

namespace figures_client_app {

  class Table : public QTableWidget, public ItemsConsumer {
    Q_OBJECT

  public:
    explicit Table( QWidget* parent = nullptr) noexcept;
    virtual ~Table();

  private:
    int setBaseItem(QSharedPointer<FigureBase> figure);

    void addRectImpl(QSharedPointer<Rect> rect) override;
    void addTriangleImpl(QSharedPointer<Triangle> triangle) override;
    void addElipsImpl(QSharedPointer<Elips> elips) override;
    void addLineImpl(QSharedPointer<Line> line) override;
    void removeItemImpl(QString item_id) override;
    void hideItemImpl(QString item_id) override;

    void setCell(int row, int col, const QString& value);

    static constexpr std::size_t ROWS_COUNT{ 0 };
    static constexpr std::size_t COLUMNS_COUNT{ 6 };

    static constexpr int ID_COL{ 0 };
    static constexpr int TYPE_COL{ 1 };
    static constexpr int POS_COL{ 2 };
    static constexpr int REGION_COL{ 3 };
    static constexpr int HIDE_COL{ 4 };
    static constexpr int DELETE_COL{ 5 };

    static constexpr char HIDE_ICO_PATH[] = ":/table/images/hide.png";
    static constexpr char DELETE_ICO_PATH[] = ":/table/images/delete.png";

    static constexpr char RECT_TYPE[] = "Rect";
    static constexpr char TRIANGLE_TYPE[] = "Trinangle";
    static constexpr char ELIPS_TYPE[] = "Ellips";
    static constexpr char LINE_TYPE[] = "Line";
  };

}