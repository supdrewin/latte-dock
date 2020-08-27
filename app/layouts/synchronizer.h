/*
*  Copyright 2019  Michail Vourlakos <mvourlakos@gmail.com>
*
*  This file is part of Latte-Dock
*
*  Latte-Dock is free software; you can redistribute it and/or
*  modify it under the terms of the GNU General Public License as
*  published by the Free Software Foundation; either version 2 of
*  the License, or (at your option) any later version.
*
*  Latte-Dock is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef LAYOUTSSYNCHRONIZER_H
#define LAYOUTSSYNCHRONIZER_H

// Qt
#include <QObject>
#include <QHash>
#include <QTimer>


namespace Latte {
class CentralLayout;
class View;
namespace Layout{
class GenericLayout;
}
namespace Layouts {
class Manager;
}
}

namespace Plasma {
class Containment;
}

namespace KActivities {
class Controller;
}

namespace Latte {
namespace Layouts {

//! This is a Layouts map in the following structure:
//! ACTIVITY ID -> Layout Names for that activity
typedef QHash<QString, QStringList> AssignedLayoutsHash;

//! Layouts::Synchronizer is a very IMPORTANT class which is responsible
//! for all ACTIVE layouts, meaning layouts that have been loaded
//! in memory.
//!
//! The main task of Synchronizer is to load/unload layouts based
//! on "user preferences"/"activities settings"/"application current
//! phase" (e.g. startup/closing)
//!

class Synchronizer : public QObject {
    Q_OBJECT

public:
    Synchronizer(QObject *parent);
    ~Synchronizer() override;

    void loadLayouts();
    void unloadLayouts();

    void hideAllViews();
    void pauseLayout(QString layoutName);
    void syncActiveLayoutsToOriginalFiles();
    void syncLatteViewsToScreens();
    void syncMultipleLayoutsToActivities();

    bool latteViewExists(Latte::View *view) const;
    bool layoutExists(QString layoutName) const;
    //! switch to specified layout, default previousMemoryUsage means that it didn't change
    bool switchToLayout(QString layoutName, int previousMemoryUsage = -1);

    int centralLayoutPos(QString id) const;

    QString currentLayoutName() const;

    QString currentLayoutNameInMultiEnvironment() const;
    void setCurrentLayoutNameInMultiEnvironment(const QString &name);

    QStringList centralLayoutsNames();
    QStringList layouts() const;
    QStringList menuLayouts() const;
    void setMenuLayouts(QStringList layouts);

    QStringList activities();
    QStringList freeActivities();
    QStringList runningActivities();
    QStringList freeRunningActivities(); //! These are activities that haven't been assigned to specific layout

    Latte::View *viewForContainment(Plasma::Containment *containment);
    Latte::View *viewForContainment(uint id);

    QList<CentralLayout *> currentLayouts() const;
    QList<Latte::View *> currentViews() const;
    QList<Latte::View *> currentViewsWithPlasmaShortcuts() const;
    QList<Latte::View *> sortedCurrentViews() const;
    QList<Latte::View *> viewsBasedOnActivityId(const QString &id) const;

    CentralLayout *centralLayout(QString layoutname) const;
    Layout::GenericLayout *layout(QString layoutname) const;

    QList<CentralLayout *> centralLayoutsForActivity(const QString activityid) const;

    KActivities::Controller *activitiesController() const;

public slots:
    void updateKWinDisabledBorders();

signals:
    void centralLayoutsChanged();
    void currentLayoutNameChanged();
    void layoutsChanged();
    void menuLayoutsChanged();
    void runningActicitiesChanged();

    void currentLayoutIsSwitching(QString layoutName);

private slots:
    void updateCurrentLayoutNameInMultiEnvironment();

    void onCurrentActivityChanged(const QString &id);

    void onLayoutAdded(const QString &layoutpath);

private:
    void addLayout(CentralLayout *layout);
    void unloadCentralLayout(CentralLayout *layout);

    bool isAssigned(QString layoutName) const;

    QString layoutPath(QString layoutName);

private:
    bool m_multipleModeInitialized{false};
    bool m_isLoaded{false};

    QString m_currentLayoutNameInMultiEnvironment;

    QStringList m_layouts;
    QStringList m_menuLayouts;

    AssignedLayoutsHash m_assignedLayouts;

    QList<CentralLayout *> m_centralLayouts;

    Layouts::Manager *m_manager;
    KActivities::Controller *m_activitiesController;
};

}
}


#endif
