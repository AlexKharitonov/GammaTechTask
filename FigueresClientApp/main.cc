#include "MainWindow.hpp"

#include <QApplication>

int main(int argc, char* argv[]) {
  QApplication app{ argc, argv };

  figures_client_app::MainWindow main_window{};
  main_window.show();

  return app.exec();
}