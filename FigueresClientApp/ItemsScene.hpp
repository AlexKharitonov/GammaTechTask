#pragma once

#include <QGraphicsScene>
#include <QSharedPointer>
#include <QAbstractGraphicsShapeItem>

#include "ItemsConsumer.hpp"

namespace figures_client_app {

  class ItemsScene : public QGraphicsScene, public ItemsConsumer {
    Q_OBJECT

  public:
    explicit ItemsScene(QObject* parent = nullptr) noexcept;
    virtual ~ItemsScene();

  protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

  private:
    void addRectImpl(QSharedPointer<Rect> rect) override;
    void addTriangleImpl(QSharedPointer<Triangle> triangle) override;
    void addElipsImpl(QSharedPointer<Elips> elips) override;
    void addLineImpl(QSharedPointer<Line> line) override;
    void removeItemImpl(QString item_id) override;
    void hideItemImpl(QString item_id) override;

    void setupBaseShapeItem(
      QAbstractGraphicsShapeItem* scene_item, QSharedPointer<FigureBase> item);
    void setupBaseItem(
      QGraphicsItem* scene_item, QSharedPointer<FigureBase> item);

    static constexpr int ID_INDEX{ 0 };
  };

}