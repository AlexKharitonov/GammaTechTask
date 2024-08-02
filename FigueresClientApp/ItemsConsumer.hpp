#pragma once

#include <QSharedPointer>

#include "Figures/Rect.hpp"
#include "Figures/Line.hpp"
#include "Figures/Elips.hpp"
#include "Figures/Triangle.hpp"

namespace figures_client_app {

  class ItemsConsumer : public QObject {
    Q_OBJECT

  signals:
    void itemRemoveSignal(QString item_id);
    void itemHideSignal(QString item_id);

  public slots:
    void addRect(QSharedPointer<Rect> rect) {
      this->addRectImpl(rect);
    }

    void addTriangle(QSharedPointer<Triangle> triangle) {
      this->addTriangleImpl(triangle);
    }

    void addElips(QSharedPointer<Elips> elips) {
      this->addElipsImpl(elips);
    }

    void addLine(QSharedPointer<Line> line) {
      this->addLineImpl(line);
    }

    void removeItem(QString item_id) {
      this->removeItemImpl(item_id);
    }

    void hideItem(QString item_id) {
      this->hideItemImpl(item_id);
    }

  private:
    virtual void addRectImpl(QSharedPointer<Rect> rect) = 0;
    virtual void addTriangleImpl(QSharedPointer<Triangle> triangle) = 0;
    virtual void addElipsImpl(QSharedPointer<Elips> elips) = 0;
    virtual void addLineImpl(QSharedPointer<Line> line) = 0;
    virtual void removeItemImpl(QString item_id) = 0;
    virtual void hideItemImpl(QString item_id) = 0;
  };

}