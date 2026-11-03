#include <QByteArray>
#include <QDir>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QStringList>

int main(int argc, char *argv[]) {
  qputenv("QT_QPA_PLATFORM", QByteArray("linuxfb"));
  QGuiApplication app(argc, argv);

  QQmlApplicationEngine engine;

  QDir dir(":/qt/qml/Cybit/assets");

  QStringList images;
  for (const QString &file : dir.entryList(
           {"*.png", "*.jpg", "*.jpeg", "*.webp"}, QDir::Files, QDir::Name)) {
    images.append("qrc:/qt/qml/Cybit/assets/" + file);
  }

  engine.rootContext()->setContextProperty("backgroundImages", images);

  engine.loadFromModule("Cybit", "Main");

  if (engine.rootObjects().isEmpty())
    return -1;

  return app.exec();
}
