#pragma once

#include "Figures/Rect.hpp"
#include "Figures/Line.hpp"
#include "Figures/Elips.hpp"
#include "Figures/Triangle.hpp"

#include <QObject>
#include <QUdpSocket>
#include <QThread>
#include <QSharedPointer>
#include <vector>

namespace figures_client_app {

  class FiguresClient : public QObject {
    Q_OBJECT

  public:
    explicit FiguresClient(QObject* parent = nullptr) noexcept;
    virtual ~FiguresClient();

  signals:
    void rectReceived(QSharedPointer<Rect>);
    void triangleReceived(QSharedPointer<Triangle>);
    void elipsReceived(QSharedPointer<Elips>);
    void lineReceived(QSharedPointer<Line>);


  private slots:
    void processReceivedData();

  private:
    inline void receiverSetup() noexcept;
    void socketSetup() noexcept;

    void itemReceivedNotify(const char* data, qsizetype data_size);

    QUdpSocket client_socket_{};
    QThread receiver_{};

    static constexpr int CLIENT_PORT{ 10002 };
  };

}