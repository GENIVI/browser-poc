/**
 * Copyright (C) 2013, Pelagicore
 *
 * Author: Marcel Schuette <marcel.schuette@pelagicore.com>
 *
 * This file is part of the GENIVI project Browser Proof-Of-Concept
 * For further information, see http://genivi.org/
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <QApplication>
#include "qmlapplicationviewer.h"

#include "../common/browserdefs.h"
#include "browserhelper.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));

    QCoreApplication::setOrganizationName("Genivi");
    QCoreApplication::setOrganizationDomain("genivi.org");
    QCoreApplication::setApplicationName("Browser PoC");

    browserhelper bhelper;

    QmlApplicationViewer viewer;
    viewer.addImportPath(QLatin1String("modules"));
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer.setMainQmlFile(QLatin1String("qml/browser/main.qml"));
    viewer.showExpanded();

    QGraphicsObject *rootqmlobject = viewer.rootObject();

    bhelper.webitem = rootqmlobject;
    bhelper.wpw->webitem = rootqmlobject;

    QObject::connect(rootqmlobject, SIGNAL(pageLoadStarted()), &bhelper, SLOT(browserStartLoading()));
    QObject::connect(rootqmlobject, SIGNAL(pageLoadFinished(bool)), bhelper.wpw, SIGNAL(onLoadFinished(bool)));

    return app->exec();
}




