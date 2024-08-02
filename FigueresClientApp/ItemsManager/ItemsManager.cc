#include "ItemsManager.hpp"

namespace figures_client_app {

  ItemsManager::ItemsManager(QObject* parent /*= nullptr*/) noexcept :
    QObject{ parent } {
    figures_client_ = new FiguresClient{ this };
  }

  ItemsManager::~ItemsManager() {
  }

  void ItemsManager::addConsumer(ItemsConsumer* consumer) {
    connect(figures_client_, &FiguresClient::rectReceived, consumer, &ItemsConsumer::addRect);
    connect(figures_client_, &FiguresClient::triangleReceived, consumer, &ItemsConsumer::addTriangle);
    connect(figures_client_, &FiguresClient::elipsReceived, consumer, &ItemsConsumer::addElips);
    connect(figures_client_, &FiguresClient::lineReceived, consumer, &ItemsConsumer::addLine);

    for (auto current_consumer : consumers_) {
      connect(current_consumer, &ItemsConsumer::itemRemoveSignal, consumer, &ItemsConsumer::removeItem);
      connect(consumer, &ItemsConsumer::itemRemoveSignal, current_consumer, &ItemsConsumer::removeItem);

      connect(current_consumer, &ItemsConsumer::itemHideSignal, consumer, &ItemsConsumer::hideItem);
      connect(consumer, &ItemsConsumer::itemHideSignal, current_consumer, &ItemsConsumer::hideItem);
    }

    connect(consumer, &ItemsConsumer::itemRemoveSignal, consumer, &ItemsConsumer::removeItem);
    connect(consumer, &ItemsConsumer::itemHideSignal, consumer, &ItemsConsumer::hideItem);

    consumers_.push_back(consumer);
  }

}