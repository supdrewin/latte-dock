/*
    SPDX-FileCopyrightText: 2021 Michail Vourlakos <mvourlakos@gmail.com>
    SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef ACTIONSHANDLER_H
#define ACTIONSHANDLER_H

// local
#include "../generic/generichandler.h"
#include "../../data/generictable.h"

// Qt
#include <QObject>

namespace Ui {
class ActionsDialog;
}

namespace Latte{
namespace Settings{
namespace Dialog{
class ActionsDialog;
}
}
}


namespace Latte {
namespace Settings {
namespace Handler {

//! Handlers are objects to handle the UI elements that semantically associate with specific
//! ui::tabs or different windows. They are responsible also to handle the user interaction
//! between controllers and views

class ActionsHandler : public Generic
{
    Q_OBJECT
public:
    ActionsHandler(Dialog::ActionsDialog *dialog, const QStringList &currentActions);
    ~ActionsHandler();

    bool hasChangedData() const override;
    bool inDefaultValues() const override;

    QStringList currentData() const;

public slots:
    void reset() override;
    void resetDefaults() override;
    void save() override;

private:
    void init();
    void initDefaults();

    Data::GenericTable<Data::Generic> table(const QStringList &ids);

private:
    Data::GenericTable<Data::Generic> def_alwaysActions;

    Data::GenericTable<Data::Generic> c_alwaysActions;
    Data::GenericTable<Data::Generic> o_alwaysActions;

    Dialog::ActionsDialog *m_dialog{nullptr};
    Ui::ActionsDialog *m_ui{nullptr};
};

}
}
}

#endif