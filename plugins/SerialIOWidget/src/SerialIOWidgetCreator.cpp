#include "SerialIOWidgetCreator.h"

QString SerialIOWIdgetCreator::cid() const
{
    return QString("SerialIOWidgetCreator");
}

QString SerialIOWIdgetCreator::name() const
{
    return QString(QObject::tr("SerialIOWidget Creator"));
}

QString SerialIOWIdgetCreator::description() const
{
    return QString(QObject::tr("Creator for serial io widget"));
}

QString SerialIOWIdgetCreator::iconName() const {
    return QString();
}

IOWidget* SerialIOWIdgetCreator::create() const
{
    return new SerialIOWidget;
}

IOWidget* SerialIOWIdgetCreator::create(const nlohmann::json& json) const
{
    auto widget = new SerialIOWidget;
    // widget->fromJson(json);

    return widget;
}
