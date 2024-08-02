#pragma once

#include <QObject>
#include <QSharedPointer>
#include <list>

#include "FiguresClient/FiguresClient.hpp"
#include "ItemsConsumer.hpp"

namespace figures_client_app {

  class ItemsManager : public QObject {
    Q_OBJECT

  public:
    explicit ItemsManager(QObject* parent = nullptr) noexcept;
    virtual ~ItemsManager();

    void addConsumer(ItemsConsumer* consumer);

  private:
    FiguresClient* figures_client_{ nullptr };

    std::list<ItemsConsumer*> consumers_;
  };

}