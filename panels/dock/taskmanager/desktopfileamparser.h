// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "dsglobal.h"
#include "applicationinterface.h"
#include "desktopfileparserfactory.h"
#include "desktopfileabstractparser.h"

#include <QObject>

DS_BEGIN_NAMESPACE

namespace dock {
class AbstractWindow;

class DesktopFileAMParser : public DesktopfileAbstractParser
{
    Q_OBJECT
public:
    ~DesktopFileAMParser();

    virtual void launch() override;
    virtual void launchWithAction(const QString& action) override;
    virtual void requestQuit() override;

    virtual QString id() override;
    virtual QString name() override;
    virtual QString desktopIcon() override;
    virtual QList<QPair<QString, QString>> actions() override;
    virtual QString genericName() override;
    virtual bool isDocked() override;
    virtual bool isValied() override;

    virtual void setDocked(bool docked) override;

    static QStringList loadDockedDesktopfile();
    static QString identifyWindow(QPointer<AbstractWindow> window);

private:
    friend class DesktopfileParserFactory<DesktopFileAMParser>;
    DesktopFileAMParser(QString id, QObject *parent = nullptr);

private:
    QString id2dbusPath(const QString& id);
    void connectToAmDBusSignal(const QString& propertyName, std::function<void(void)> handler);

private:
    QString m_id;
    QString m_name;
    QString m_icon;
    QString m_genericName;
    QList<QPair<QString, QString>>  m_actions;
    using Application = org::desktopspec::ApplicationManager1::Application;
    QScopedPointer<Application> m_applicationInterface;
};
}
DS_END_NAMESPACE
