#include "ItemsScene.hpp"

#include <QGraphicsRectItem>
#include <QString>
#include <QColor>
#include <QGraphicsSceneMouseEvent>

namespace figures_client_app {

  ItemsScene::ItemsScene(QObject* parent /*= nullptr*/) noexcept :
    QGraphicsScene{ parent } {
  }

  ItemsScene::~ItemsScene() {
  }

  void ItemsScene::setupBaseShapeItem(
    QAbstractGraphicsShapeItem* scene_item, QSharedPointer<FigureBase> item) {
    QColor color{ item->color_ };
    scene_item->setBrush(QBrush(color));
  }

  void ItemsScene::setupBaseItem(
    QGraphicsItem* scene_item, QSharedPointer<FigureBase> item) {
    scene_item->setData(ID_INDEX, QVariant(item->uuid_.toString()));
  }

  void ItemsScene::addRectImpl(QSharedPointer<Rect> rect) {
    const QRect rect_shape{ rect->x_, rect->y_, rect->width_, rect->height_ };
    QGraphicsRectItem* scene_rect = new QGraphicsRectItem{ rect_shape }; // TODO: potential memory leak.

    setupBaseShapeItem(scene_rect, rect);
    setupBaseItem(scene_rect, rect);

    addItem(scene_rect);
  }

  void ItemsScene::addTriangleImpl(QSharedPointer<Triangle> triangle) {
    QPolygonF triangle_shape;
    triangle_shape 
      << QPoint{ triangle->x_, triangle->y_ } 
      << QPoint{ triangle->x2_, triangle->y2_ }
      << QPoint{ triangle->x3_, triangle->y3_ };

    QGraphicsPolygonItem* scene_triangle = new QGraphicsPolygonItem(triangle_shape);

    setupBaseShapeItem(scene_triangle, triangle);
    setupBaseItem(scene_triangle, triangle);

    addItem(scene_triangle);
  }

  void ItemsScene::addElipsImpl(QSharedPointer<Elips> elips) {
    const QRect elips_shape{ elips->x_, elips->y_, elips->r1_, elips->r2_ };
    QGraphicsEllipseItem* scene_ellipse = new QGraphicsEllipseItem(elips_shape);

    setupBaseShapeItem(scene_ellipse, elips);
    setupBaseItem(scene_ellipse, elips);

    addItem(scene_ellipse);
  }

  void ItemsScene::addLineImpl(QSharedPointer<Line> line) {
    const QLine line_shape{ line->x_, line->y_, line->x2_, line->y2_ };
    QGraphicsLineItem* scene_line = new QGraphicsLineItem(line_shape);

    scene_line->setPen(QColor{ line->color_ });

    setupBaseItem(scene_line, line);

    addItem(scene_line);
  }

  void ItemsScene::removeItemImpl(const QString item_id) {
    QList<QGraphicsItem*> scene_items = items();
    for (auto item : scene_items) {
      if (item_id == item->data(ID_INDEX).toString()) {
        QGraphicsScene::removeItem(item);
        delete item;
        break;
      }
    }
  }

  void ItemsScene::hideItemImpl(const QString item_id) {
    QList<QGraphicsItem*> scene_items = items();
    for (auto item : scene_items) {
      if (item_id == item->data(ID_INDEX).toString()) {
        item->setVisible(!item->isVisible());
        break;
      }
    }
  }

  void ItemsScene::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    QGraphicsItem* item = itemAt(event->scenePos(), QTransform());
    if (item) {
      QString id = item->data(ID_INDEX).toString();

      Qt::MouseButton button = event->button();
      switch (button) {
      case Qt::RightButton:
        emit itemHideSignal(id);
        break;
      case Qt::MiddleButton:
        emit itemRemoveSignal(id);
        break;
      }
    }

    QGraphicsScene::mousePressEvent(event);
  }

}