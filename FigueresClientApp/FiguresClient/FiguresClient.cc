#include "FiguresClient.hpp"
#include "api_generated.h"

#include <QByteArray>

namespace figures_client_app {

  FiguresClient::FiguresClient(QObject* parent /*= nullptr*/) noexcept :
    QObject{ parent } {
    receiverSetup();
  }

  FiguresClient::~FiguresClient() {
    receiver_.quit();
    receiver_.wait();
  }

  void FiguresClient::receiverSetup() noexcept {
    moveToThread(&receiver_);

    // Connect the started signal of the receiver_ thread to a lambda that creates and binds the socket
    connect(&receiver_, &QThread::started, this, &FiguresClient::socketSetup);

    // Start the receiver_ thread
    receiver_.start();
  }

  void FiguresClient::socketSetup() noexcept {
    client_socket_.bind(QHostAddress::LocalHost, CLIENT_PORT);
    connect(&client_socket_, &QUdpSocket::readyRead, this, &FiguresClient::processReceivedData);
  }

  void FiguresClient::processReceivedData() {
    while (client_socket_.hasPendingDatagrams()) {
      QByteArray datagram;
      datagram.resize(client_socket_.pendingDatagramSize());
      QHostAddress sender;
      quint16 sender_port;

      client_socket_.readDatagram(datagram.data(), datagram.size(), &sender, &sender_port);
      itemReceivedNotify(datagram.data(), datagram.size());
    }
  }

  static QSharedPointer<Rect> buildRect(const char* buff) {
    QSharedPointer<Rect> rect = QSharedPointer<Rect>::create();

    const RectData* rect_data = flatbuffers::GetRoot<RectData>(buff);
    rect->x_ = rect_data->x();
    rect->y_ = rect_data->y();
    rect->color_ = QString::fromStdString(rect_data->color_hex()->str());
    rect->width_ = rect_data->width();
    rect->height_ = rect_data->height();

    return rect;
  }

  static QSharedPointer<Triangle> buildTriangle(const char* buff) {
    QSharedPointer<Triangle> trinagle = QSharedPointer<Triangle>::create();

    const TriangleData* triangle_data = flatbuffers::GetRoot<TriangleData>(buff);
    trinagle->x_ = triangle_data->x1();
    trinagle->y_ = triangle_data->y1();
    trinagle->color_ = QString::fromStdString(triangle_data->color_hex()->str());
    trinagle->x2_ = triangle_data->x2();
    trinagle->y2_ = triangle_data->y2();
    trinagle->x3_ = triangle_data->x3();
    trinagle->y3_ = triangle_data->y3();

    return trinagle;
  }

  static QSharedPointer<Elips> buildElips(const char* buff) {
    QSharedPointer<Elips> elips = QSharedPointer<Elips>::create();

    const EllipseData* elips_data = flatbuffers::GetRoot<EllipseData>(buff);
    elips->x_ = elips_data->x();
    elips->y_ = elips_data->y();
    elips->color_ = QString::fromStdString(elips_data->color_hex()->str());
    elips->r1_ = elips_data->r1();
    elips->r2_ = elips_data->r2();

    return elips;
  }

  static QSharedPointer<Line> buildLine(const char* buff) {
    QSharedPointer<Line> line = QSharedPointer<Line>::create();

    const LineData* line_data = flatbuffers::GetRoot<LineData>(buff);
    line->x_ = line_data->x1();
    line->y_ = line_data->y1();
    line->color_ = QString::fromStdString(line_data->color_hex()->str());
    line->x2_ = line_data->x2();
    line->y2_ = line_data->y2();

    return line;
  }

  void FiguresClient::itemReceivedNotify( const char* data, qsizetype data_size) {
    // For the sake of simplicity it's expected that data is not corrupted and 
    // received in whole parts.

    const Figure* figure = flatbuffers::GetRoot<Figure>(data);
    FigureType type = figure->type();
    std::string payload = std::move(figure->payload()->str());

    switch (type) {
    case FigureType_Rect: 
      emit rectReceived(buildRect(payload.c_str()));
      break;
    case FigureType_Triangle:
      emit triangleReceived(buildTriangle(payload.c_str()));
      break;
    case FigureType_Ellipse:
      emit elipsReceived(buildElips(payload.c_str()));
      break;
    case FigureType_Line:
      emit lineReceived(buildLine(payload.c_str()));
      break;
    default:
      // Ignore error.
      break;
    }
  }

}