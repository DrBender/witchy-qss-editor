#pragma once
#ifndef SETTINGS_H
#define SETTINGS_H
#include <QString>

class Settings
{

private:
    Settings();
    Settings(const Settings &) = delete;
    Settings &operator=(const Settings &) = delete;
    Settings(Settings &&) = delete;
    Settings &operator=(Settings &&) = delete;

public:
    static Settings &instance()
    {
        static Settings p_instance;
        return p_instance;
    }
    QString settingsFile;
    int win_width, win_height;
    QString lastFile;

    void loadSettings();
    void saveSettings();
};

#endif /* SETTINGS_H */
