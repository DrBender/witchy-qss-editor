#include "settings.h"
#include <QSettings>

Settings::Settings() { settingsFile = "config.ini"; }

void Settings::loadSettings()
{
    QSettings settings(settingsFile, QSettings::IniFormat);

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
    QSettings settings(settingsFile, QSettings::IniFormat);

    settings.beginGroup("Window");
    settings.setValue("width", win_width);
    settings.setValue("height", win_height);
    settings.endGroup();

    settings.beginGroup("session");
    settings.setValue("last_file", lastFile);
    settings.endGroup();
}
