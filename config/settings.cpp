#include "settings.h"
#include <QSettings>
#include <qsettings.h>

Settings::Settings() : settings("DrBender", "Witchy Qss Editor")
{
}

void Settings::loadSettings()
{
    settings.beginGroup("Window");
    win_width = settings.value("width", 960).toInt();
    win_height = settings.value("height", 560).toInt();
    settings.endGroup();

    settings.beginGroup("session");
    lastFile = settings.value("last_file", "").toString();
    settings.endGroup();
}

void Settings::saveSettings()
{
    settings.beginGroup("Window");
    settings.setValue("width", win_width);
    settings.setValue("height", win_height);
    settings.endGroup();

    settings.beginGroup("session");
    settings.setValue("last_file", lastFile);
    settings.endGroup();
}
