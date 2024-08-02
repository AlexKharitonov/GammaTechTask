#pragma once

#include <QString>
#include <QUuid>

namespace figures_client_app {

  struct FigureBase {
    int x_{ 0 };
    int y_{ 0 };
    QString color_{};
    QUuid uuid_{};

    FigureBase() noexcept : uuid_{ QUuid::createUuid() } {
    }
  };

}